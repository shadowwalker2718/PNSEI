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

qqq = ["AAPL","MSFT","AMZN","TSLA","FB","GOOG","GOOGL","NVDA","PYPL","INTC","CMCSA","NFLX","ADBE","PEP","CSCO","AVGO",
       "QCOM","COST","TMUS","TXN","AMGN","CHTR","SBUX","AMD","INTU","AMAT","MELI","ISRG","MU","BKNG","MDLZ","GILD",
       "LRCX","JD","ZM","FISV","CSX","ATVI","ADP","ADSK","BIDU","VRTX","ADI","ILMN","REGN","MRNA","MNST","NXPI","PDD",
       "KLAC","DOCU","KDP","ALGN","LULU","CTSH","BIIB","WBA","EXC","IDXX","ROST","MAR","PTON","EA","MTCH","WDAY","ASML",
       "AEP","SNPS","KHC","MCHP","EBAY","CDNS","NTES","ALXN","XEL","CTAS","MRVL","DXCM","ORLY","SGEN","XLNX","PAYX",
       "ANSS","VRSK","PCAR","OKTA","TEAM","FAST","CPRT","SPLK","DLTR","MXIM","SWKS","SIRI","CERN","VRSN","INCY","CDW",
       "CHKP","TCOM","FOXA","FOX"]

nyse = mcal.get_calendar('NYSE')
start_date = (datetime.datetime.now() - datetime.timedelta(days=365*2)).strftime('%Y-%m-%d')
end_date = datetime.datetime.now().strftime('%Y-%m-%d')
trading_sessions = nyse.schedule(start_date=start_date, end_date=end_date, tz='America/New_York')

engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')

symbol_to_timeseries = {}

for symbol in qqq:
    with engine_mysql.begin() as cx:
        sql = f"select w,c,dt FROM sentosa.`bar1d_poly` where s='{symbol}' and dt>='{start_date}' and dt<'{end_date}' order by dt"
        df = pd.read_sql(sql, cx, index_col='dt')
        #if df.shape[0] != 504:
        #    print(f"{symbol}, {df.shape[0]}")
        df['r'] = np.log(df.w) - np.log(df.w.shift(1))
        df.drop(df.index[0], inplace=True)
        symbol_to_timeseries[symbol] = df


with engine_mysql.begin() as cx:
    sql = f"select w,c,dt FROM sentosa.`bar1d_poly` where s='QQQ' and dt>='{start_date}' and dt<'{end_date}' order by dt"
    qqq = pd.read_sql(sql, cx, index_col='dt')
    qqq['r'] = np.log(qqq.w) - np.log(qqq.w.shift(1))
    qqq.drop(qqq.index[0], inplace=True)

qqq.r.plot()
#plt.show()
#print(qqq.shape)

ranks = defaultdict(list)

# Buy the worst 5 stock and hold v.s. buy the ETF and hold
for index, row in trading_sessions.iterrows():
    market_open, market_close = row['market_open'], row['market_close']
    trade_date = market_open.date()

    for s in symbol_to_timeseries:
        data = symbol_to_timeseries[s]
        if trade_date not in data.index:
            break
        else:
            ranks[trade_date].append((data.loc[trade_date]['r'], s, data.loc[trade_date]['c']))

    if trade_date in ranks:
        ranks[trade_date] = sorted(ranks[trade_date])[-2:]


class Account(object):
    def __init__(self):
        self.positions = defaultdict(int)  # AAPL ==> 12 shares, buy low strategy
        self.basis = 0.0
        self.benchmark_qqq_shares = 0.0  # average cost strategy
        self.pnl = defaultdict(float)  # date ==> pnl of buy low strategy


acc = Account()
first_qqq_price = None
for k, v in ranks.items():
    if k in qqq.index:
        if first_qqq_price is None:
            first_qqq_price = float(qqq.loc[k].c)
        investment = 0.0
        for r, s, c in v:
            investment += c
            acc.positions[s] += 1
        acc.basis += investment
        acc.benchmark_qqq_shares += investment/float(qqq.loc[k].c)

        market_value = -1e-10
        for sm in acc.positions:
            if k in symbol_to_timeseries[sm].index:
                price = float(symbol_to_timeseries[sm].loc[k].c)
                market_value += price * acc.positions[sm]

        if market_value > 0.0:
            acc.pnl[k] += (market_value - acc.basis)/acc.basis


print("basis:", acc.basis)
qqq_final_price = float(qqq.tail(1).c)
average_cost_value = acc.benchmark_qqq_shares * qqq_final_price
print("averaging cost:", average_cost_value, "pnl: ", (average_cost_value-acc.basis)/acc.basis)
market_value = 0.0
for k in acc.positions:
    price = float(symbol_to_timeseries[k].tail(1).c)
    market_value += price * acc.positions[k]

print("buy-high-hold:", market_value, "pnl: ", (market_value-acc.basis)/acc.basis)

last_qqq_price = float(qqq.tail(1).c)
print("qqq:",  (last_qqq_price - first_qqq_price)/first_qqq_price)

t = pd.DataFrame(list(acc.pnl.items()), columns=['dt', 'pnl'])
t.set_index('dt', inplace=True)
ax = t.plot(grid=True, alpha=0.5)


start, end = t.index[0], t.index[-1]
q3 = qqq[start:end]
q3['pct'] = (q3.c-float(q3.head(1).c))/float(q3.head(1).c)
q3.pct.plot(grid=True, ax=ax, alpha=0.5)
plt.show()

print(dict(sorted(acc.positions.items(), key=lambda item: item[1])))
