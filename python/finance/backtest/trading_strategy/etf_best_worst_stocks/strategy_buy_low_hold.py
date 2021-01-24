import sqlite3
import pandas as pd
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt
from sqlalchemy import create_engine, MetaData, Table, dialects
import time, os
import requests
import datetime, pytz
from sqlalchemy.types import DATETIME, FLOAT, INTEGER, VARCHAR, BIGINT
import re
import traceback
import pandas_market_calendars as mcal
import hvplot.pandas
from datetime import time
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from collections import defaultdict

# long the worst of QQQ and short the best of QQQ
pd.options.mode.chained_assignment = None
plt.rcParams["figure.figsize"] = [18, 9]

qqqs = ["AAPL", "MSFT", "AMZN", "TSLA", "FB", "GOOG", "GOOGL", "NVDA", "PYPL", "INTC", "CMCSA", "NFLX", "ADBE", "PEP",
        "CSCO", "AVGO",
        "QCOM", "COST", "TMUS", "TXN", "AMGN", "CHTR", "SBUX", "AMD", "INTU", "AMAT", "MELI", "ISRG", "MU", "BKNG",
        "MDLZ", "GILD",
        "LRCX", "JD", "ZM", "FISV", "CSX", "ATVI", "ADP", "ADSK", "BIDU", "VRTX", "ADI", "ILMN", "REGN", "MRNA", "MNST",
        "NXPI", "PDD",
        "KLAC", "DOCU", "KDP", "ALGN", "LULU", "CTSH", "BIIB", "WBA", "EXC", "IDXX", "ROST", "MAR", "PTON", "EA",
        "MTCH", "WDAY", "ASML",
        "AEP", "SNPS", "KHC", "MCHP", "EBAY", "CDNS", "NTES", "ALXN", "XEL", "CTAS", "MRVL", "DXCM", "ORLY", "SGEN",
        "XLNX", "PAYX",
        "ANSS", "VRSK", "PCAR", "OKTA", "TEAM", "FAST", "CPRT", "SPLK", "DLTR", "MXIM", "SWKS", "SIRI", "CERN", "VRSN",
        "INCY", "CDW",
        "CHKP", "TCOM", "FOXA", "FOX"]


class Account(object):
    def __init__(self):
        self.positions = defaultdict(int)  # AAPL ==> 12 shares, buy low strategy
        self.basis = 0.0
        self.benchmark_qqq_shares = 0.0  # average cost strategy
        self.pnl_main_strategy = defaultdict(float)  # date ==> pnl of buy low strategy
        self.pnl_dollar_averaging = defaultdict(float)


engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')
nyse = mcal.get_calendar('NYSE')

strategy_perf = defaultdict(list)

holding_period = 30
for i in range(holding_period * 1, holding_period * 12 * 8 + 1, holding_period):
    end_date = (datetime.datetime.now() - datetime.timedelta(days=i)).strftime('%Y-%m-%d')
    start_date = (datetime.datetime.now() - datetime.timedelta(days=i + holding_period)).strftime('%Y-%m-%d')
    print(start_date, end_date)
    trading_sessions = nyse.schedule(start_date=start_date, end_date=end_date, tz='America/New_York')
    symbol_to_timeseries = {}
    for symbol in qqqs:
        with engine_mysql.begin() as cx:
            sql = f"select w,c,dt FROM sentosa.`bar1d_poly` where s='{symbol}' and dt>='{start_date}' and dt<'{end_date}' order by dt"
            df = pd.read_sql(sql, cx, index_col='dt')
            if df.shape[0] <= 1:
                print(f"error: no data for {symbol} on date: {start_date} - {end_date}")
                continue
            df['r'] = np.log(df.w) - np.log(df.w.shift(1))
            df.drop(df.index[0], inplace=True)
            symbol_to_timeseries[symbol] = df
    if len(symbol_to_timeseries) == 0:
        continue

    qqq = None
    with engine_mysql.begin() as cx:
        sql = f"select w,c,dt FROM sentosa.`bar1d_poly` where s='QQQ' and dt>='{start_date}' and dt<'{end_date}' order by dt"
        qqq = pd.read_sql(sql, cx, index_col='dt')
        qqq['r'] = np.log(qqq.w) - np.log(qqq.w.shift(1))
        qqq.drop(qqq.index[0], inplace=True)

    ranks_low = defaultdict(list)
    ranks_high = defaultdict(list)

    # Buy the worst 5 stock and hold v.s. buy the ETF and hold
    for index, row in trading_sessions.iterrows():
        market_open, market_close = row['market_open'], row['market_close']
        trade_date = market_open.date()

        no_data_count = 0
        for s in symbol_to_timeseries:
            data = symbol_to_timeseries[s]
            if trade_date not in data.index:
                # print(f"warning: symbol {s} has no trading data on {trade_date}.")
                no_data_count += 1
                if no_data_count > len(symbol_to_timeseries) / 2:
                    break
            else:
                ranks_low[trade_date].append((data.loc[trade_date]['r'], s, data.loc[trade_date]['c']))
                ranks_high[trade_date].append((data.loc[trade_date]['r'], s, data.loc[trade_date]['c']))

        if trade_date in ranks_low and len(ranks_low[trade_date]) > 50:
            ranks_low[trade_date] = sorted(ranks_low[trade_date])[:10]

        if trade_date in ranks_high and len(ranks_high[trade_date]) > 50:
            ranks_high[trade_date] = sorted(ranks_high[trade_date])[-10:]

    acc_low = Account()
    first_qqq_price = None
    for k, v in ranks_low.items():
        if k in qqq.index:
            if first_qqq_price is None:
                first_qqq_price = float(qqq.loc[k].c)
            investment = 0.0
            for r, s, c in v:
                investment += c
                acc_low.positions[s] += 1
            acc_low.basis += investment
            acc_low.benchmark_qqq_shares += investment / float(qqq.loc[k].c)
            acc_low.pnl_dollar_averaging[k] = np.log(acc_low.benchmark_qqq_shares * qqq.loc[k].c) - np.log(
                acc_low.basis)

            market_value = -1e-10
            for sm in acc_low.positions:
                if k in symbol_to_timeseries[sm].index:
                    price = float(symbol_to_timeseries[sm].loc[k].c)
                    market_value += price * acc_low.positions[sm]

            if market_value > 0.0:
                acc_low.pnl_main_strategy[k] += np.log(market_value) - np.log(acc_low.basis)

    acc_high = Account()
    for k, v in ranks_high.items():
        if k in qqq.index:
            investment = 0.0
            for r, s, c in v:
                investment += c
                acc_high.positions[s] += 1
            acc_high.basis += investment

            market_value = -1e-10
            for sm in acc_high.positions:
                if k in symbol_to_timeseries[sm].index:
                    price = float(symbol_to_timeseries[sm].loc[k].c)
                    market_value += price * acc_high.positions[sm]

            if market_value > 0.0:
                acc_high.pnl_main_strategy[k] += np.log(market_value) - np.log(acc_high.basis)

    print("low basis:", acc_low.basis)
    print("high basis:", acc_high.basis)
    average_cost_value = acc_low.benchmark_qqq_shares * float(qqq.tail(1).c)
    print("averaging cost:", average_cost_value, "pnl: ", np.log(average_cost_value) - np.log(acc_low.basis))
    market_value = 0.0
    for k in acc_low.positions:
        price = float(symbol_to_timeseries[k].tail(1).c)
        market_value += price * acc_low.positions[k]
    print("buy_low_hold:", market_value, "pnl: ", np.log(market_value) - np.log(acc_low.basis))
    market_value = 0.0
    for k in acc_high.positions:
        price = float(symbol_to_timeseries[k].tail(1).c)
        market_value += price * acc_high.positions[k]
    print("buy_high_hold:", market_value, "pnl: ", np.log(market_value) - np.log(acc_high.basis))

    last_qqq_price = float(qqq.tail(1).c)
    print("buy_once_and_hold:", np.log(last_qqq_price) - np.log(first_qqq_price))

    t = pd.DataFrame(list(acc_low.pnl_main_strategy.items()), columns=['dt', 'buy_low_and_hold'])
    t.set_index('dt', inplace=True)
    # ax = t.plot(grid=True)

    t_high = pd.DataFrame(list(acc_high.pnl_main_strategy.items()), columns=['dt', 'buy_high_and_hold'])
    t_high.set_index('dt', inplace=True)

    t2 = pd.DataFrame(list(acc_low.pnl_dollar_averaging.items()), columns=['dt', 'pnl_dollar_cost_averaging'])
    t2.set_index('dt', inplace=True)

    start, end = t.index[0], t.index[-1]
    q3 = qqq[start:end]
    q3['buy_once_and_hold'] = np.log(q3.c) - np.log(float(q3.head(1).c))

    t = t.merge(q3.buy_once_and_hold, how='outer', left_index=True, right_index=True)
    t = t.merge(t2, how='outer', left_index=True, right_index=True)
    t = t.merge(t_high, how='outer', left_index=True, right_index=True)

    t['mixed'] = (t.buy_low_and_hold + t.buy_high_and_hold) / 2
    t.drop(columns=['buy_low_and_hold', 'buy_high_and_hold'], inplace=True)
    # q3.pct.plot(grid=True, ax=ax)
    t.rename(columns={'pct': 'buy_once_and_hold'}, inplace=True)
    if False:
        t.plot(grid=True, style='-o', title=f'{start_date} - {end_date}', alpha=0.85)  # ax=ax,
        plt.tight_layout()
        plt.show()
    strategy_perf['dt'].append(end_date)
    for strategy in t.columns:
        strategy_perf[strategy].append(float(t[strategy].tail(1)))
    # print(dict(sorted(acc_low.positions.items(), key=lambda item: item[1])))

print("*" * 120)
df_strategy_perf = pd.DataFrame(data=dict(strategy_perf))
df_strategy_perf.set_index('dt', inplace=True)
for c in df_strategy_perf.columns:
    print(c, ' -> ', end='')
    print(sum(df_strategy_perf[c]))
df_strategy_perf.to_csv("strategy_perf.csv", index=True)
df_strategy_perf.drop(columns=['buy_once_and_hold'], inplace=True)
df_strategy_perf.plot(grid=True, style='-o', title=f'monthly perf', alpha=0.85)  # ax=ax,
plt.show()
print(df_strategy_perf)
