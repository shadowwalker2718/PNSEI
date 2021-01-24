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

engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')

pd.options.mode.chained_assignment = None

# df.loc['2019-05-13 09:30:00':'2019-05-14 00:00:00']
# Update multiple rows:
# INSERT INTO table (id,Col1,Col2) VALUES (1,1,1),(2,2,3),(3,9,3),(4,10,12)
# ON DUPLICATE KEY UPDATE Col1=VALUES(Col1),Col2=VALUES(Col2);
def get_ts(s):
    with engine_mysql.begin() as cx:
        df = pd.read_sql(f"select dt,o,h,l,c,v,w,bc from bar1m_partitioned_symbol where s='{s}' order by dt", cx, index_col='dt')
        cur_day = None
        for dt, row in df.iterrows():
            day = dt.strftime('%Y-%m-%d')
            if cur_day != day:
                market_open = day + ' 09:30:00'
                market_close = day + ' 16:00:00'

                df_pre_market = df.loc[day+' 00:00:00': market_open]
                df_regular_market = df.loc[market_open: market_close]
                df_after_market = df.loc[market_close: day + ' 23:59:00']

                basis = None
                if df_pre_market.shape[0] > 0:
                    basis = float(df_pre_market.head(1).w)
                for dt_, row_ in df_pre_market.iterrows():
                    df.at[dt_, 'bc'] = (row_.w - basis) / basis

                if df_regular_market.shape[0] > 0:
                    basis = float(df_regular_market.head(1).w)
                for dt_, row_ in df_regular_market.iterrows():
                    df.at[dt_, 'bc'] = (row_.w - basis) / basis

                if df_after_market.shape[0] > 0:
                    basis = float(df_after_market.head(1).w)
                for dt_, row_ in df_after_market.iterrows():
                    df.at[dt_, 'bc'] = (row_.w - basis) / basis
                cur_day = day
    return df



def get_ts_daily(s):
    with engine_mysql.begin() as cx:
        df = pd.read_sql(f"SELECT * FROM sentosa.`bar1d_poly` where s='{s}' order by dt", cx, index_col='dt')
        df['volatility'] = (df.h - df.l) / df.w
    return df

def get_details(s):
    with engine_mysql.begin() as cx:
        df1 = pd.read_sql(f"SELECT * FROM sentosa.ticker_info where symbol='{s}'", cx, index_col='symbol')
    with engine_mysql.begin() as cx:
        df2 = pd.read_sql(f"SELECT * FROM sentosa.ticker_equity where symbol='{s}'", cx, index_col='symbol')
    with engine_mysql.begin() as cx:
        df3 = pd.read_sql(f"SELECT * FROM sentosa.ticker_details where symbol='{s}'", cx, index_col='symbol')
    df = pd.concat([df1, df2, df3], axis=1)
    return df


symbol = 'GM'
df_details = get_details(symbol)
df_ts = get_ts(symbol)
df_ts_daily = get_ts_daily(symbol)

df_ts_tz = df_ts.tz_localize('America/New_York', level=0)

threshold = float(df_details['beta']/40) if (df_details['beta'].item() is not None) else 0.06

# nyse = mcal.get_calendar('NYSE')
nyse = mcal.get_calendar('NYSE', open_time=time(2, 0), close_time=time(20, 0))
start_date = df_ts.head(1).index[0].date().strftime('%Y-%m-%d')
end_date = datetime.datetime.now().strftime('%Y-%m-%d')
trading_sessions = nyse.schedule(start_date=start_date, end_date=end_date, tz='America/New_York')
df = None
count = 0
BASE = 50000
BASE_PRICE = None
initial = 50000
shares = 0
buy_next_day = False
pnl = pd.DataFrame(columns=['date', 'pnl', 'price'])
investment = 0
portion= 3
buy_count, sell_count = 0, 0
for index, row in trading_sessions.iterrows():
    mopen, mclose = row['market_open'], row['market_close']
    # print(mopen, mclose)
    df = df_ts_tz.loc[mopen: mclose]
    if len(df.head(1).index) ==0:
        continue
    """
    o_dt = df.head(1).index[0].date().strftime('%Y-%m-%d 09:30:00')
    o_dt = datetime.datetime.strptime(o_dt, "%Y-%m-%d %H:%M:%S")
    c_dt = df.head(1).index[0].date().strftime('%Y-%m-%d 16:00:00')
    c_dt = datetime.datetime.strptime(c_dt, "%Y-%m-%d %H:%M:%S")
    """
    open_price, early_price, late_price, close_price = 0, 0, 0, 0

    for index_day, row_day in df.iterrows():
        cur = index_day.replace(tzinfo=None)
        cur = cur.strftime('%H:%M:%S')
        current_price = row_day['w']
        if cur == '09:30:00':
            open_price = row_day['w']
            if BASE_PRICE is None:
                BASE_PRICE = open_price
            if buy_next_day:
                share_to_buy = int(initial/open_price/portion)
                shares += share_to_buy
                initial -= open_price*share_to_buy
                investment += open_price*share_to_buy
                buy_count += 1
                buy_next_day = False
        if cur == '10:30:00':
            early_price = row_day['w']
            # sell when price jumps big in the morning
            if open_price > 0 and (early_price - open_price) / open_price > threshold:
                if shares > 0:
                    if investment > shares*current_price:
                        continue
                    share_to_sell = shares
                    shares -= share_to_sell
                    sell_count += 1
                    initial += early_price * share_to_sell
                    investment -= 0
            # buy when price falls big in the morning
            if open_price > 0 and (early_price - open_price) / open_price < -threshold*1.5:
                share_to_buy = int(initial/early_price/portion)
                shares += share_to_buy
                buy_count += 1
                initial -= early_price * share_to_buy
                investment += early_price*share_to_buy
        if cur == '15:55:00':
            late_price = row_day['w']
            if open_price > 0 and (late_price - open_price) / open_price > threshold:
                if shares > 0:
                    if investment > shares*current_price:
                        continue
                    share_to_sell = shares
                    shares -= share_to_sell
                    sell_count += 1
                    initial += late_price*share_to_sell
                    investment = 0
            if open_price > 0 and (late_price - open_price) / open_price < -threshold:
                buy_next_day = True
        if cur == '15:59:00':
            close_price = row_day['w']

    if close_price > 0 and BASE_PRICE is not None:
        daily_pnl = (initial + shares * close_price - BASE) / BASE
        price_pct = (close_price - BASE_PRICE) / BASE_PRICE
        #print(mopen, initial, shares, daily_pnl, price_pct)
        pnl = pnl.append({'date': df.head(1).index[0].date(), 'pnl': daily_pnl, 'price': price_pct}, ignore_index=True)
    else:
        print('data error')

pnl.set_index('date', inplace=True)
pnl.plot(grid=True, title=f"{symbol} {threshold} {buy_count} {sell_count} {portion}")
plt.show()


def draw(df):
    # Create figure with secondary y-axis
    fig = make_subplots(specs=[[{"secondary_y": True}]])
    # include candlestick with rangeselector
    fig.add_trace(go.Candlestick(x=df.index, open=df['o'], high=df['h'], low=df['l'], close=df['c']), secondary_y=True)
    # include a go.Bar trace for volumes
    fig.add_trace(go.Bar(x=df.index, y=df['v']), secondary_y=False)
    fig.layout.yaxis2.showgrid = False
    fig.show()

# draw(df)
