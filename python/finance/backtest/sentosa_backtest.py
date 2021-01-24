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


def get_ts(s):
    with engine_mysql.begin() as cx:
        df = pd.read_sql(f"select dt,o,h,l,c,v,w from bar1m_partitioned_symbol where s='{s}' order by dt",
                         cx, index_col='dt')
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


symbol = 'UBER'
df_details = get_details(symbol)
df_ts = get_ts(symbol)
df_ts_tz = df_ts.tz_localize('America/New_York', level=0)

# nyse = mcal.get_calendar('NYSE')
nyse = mcal.get_calendar('NYSE', open_time=time(2, 0), close_time=time(20, 0))
start_date = df_ts.head(1).index[0].date().strftime('%Y-%m-%d')
end_date = datetime.datetime.now().strftime('%Y-%m-%d')
trading_sessions = nyse.schedule(start_date=start_date, end_date=end_date, tz='America/New_York')
df = None
count = 0
BASE = 500
initial = 500
shares = 0
buy_next_day = False
pnl = pd.DataFrame(columns=['pnl', 'price'])
for index, row in trading_sessions.iterrows():
    mopen, mclose = row['market_open'], row['market_close']
    # print(mopen, mclose)
    df = df_ts_tz.loc[mopen: mclose]
    o_dt = df.head(1).index[0].date().strftime('%Y-%m-%d 09:30:00')
    o_dt = datetime.datetime.strptime(o_dt, "%Y-%m-%d %H:%M:%S")
    c_dt = df.head(1).index[0].date().strftime('%Y-%m-%d 16:00:00')
    c_dt = datetime.datetime.strptime(c_dt, "%Y-%m-%d %H:%M:%S")
    open_price, early_price, late_price, close_price = 0, 0, 0, 0

    for index_day, row_day in df.iterrows():
        cur = index_day.replace(tzinfo=None)
        cur = cur.strftime('%H:%M:%S')
        if cur == '09:30:00':
            open_price = row_day['w']
            if buy_next_day:
                shares += 1
                initial -= open_price
                buy_next_day = False
        if cur == '10:30:00':
            early_price = row_day['w']
            if open_price > 0 and (early_price - open_price) / open_price > 0.02:
                if shares > 0:
                    shares -= 1
                    initial += early_price
            # buy when price falls big in the morning
            if open_price > 0 and (early_price - open_price) / open_price < -0.02:
                shares += 1
                initial -= early_price
        if cur == '15:55:00':
            late_price = row_day['w']
            if open_price > 0 and (late_price - open_price) / open_price > 0.02:
                if shares > 0:
                    shares -= 1
                    initial += late_price
            if open_price > 0 and (late_price - open_price) / open_price < -0.02:
                buy_next_day = True
        if cur == '15:59:00':
            close_price = row_day['w']

    if close_price > 0:
        daily_pnl = initial + shares * close_price - BASE
        # print(mopen, initial, shares, daily_pnl)
        pnl = pnl.append({'pnl': daily_pnl, 'price': close_price}, ignore_index=True)
    else:
        print('data error')

pnl.plot(grid=True)
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
