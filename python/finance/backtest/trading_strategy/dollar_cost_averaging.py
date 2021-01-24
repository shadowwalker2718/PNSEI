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

# https://www.investopedia.com/investing/dollar-cost-averaging-pays/#:~:text=Dollar%2Dcost%20averaging%20is%20a,re%20already%20using%20this%20strategy.


nyse = mcal.get_calendar('NYSE')
start_date = (datetime.datetime.now() - datetime.timedelta(days=365*2)).strftime('%Y-%m-%d')
end_date = datetime.datetime.now().strftime('%Y-%m-%d')
trading_sessions = nyse.schedule(start_date=start_date, end_date=end_date, tz='America/New_York')

engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')
symbol_to_timeseries = {}


with engine_mysql.begin() as cx:
    sql = f"select w,c,dt FROM sentosa.`bar1d_poly` where s='QQQ' and dt>='{start_date}' and dt<'{end_date}' order by dt"
    qqq = pd.read_sql(sql, cx, index_col='dt')
    qqq['r'] = np.log(qqq.w) - np.log(qqq.w.shift(1))
    qqq.drop(qqq.index[0], inplace=True)
    qqq['cr'] = (1 + qqq.r).cumprod() - 1

ax = qqq.cr.plot(grid=True, alpha=0.5)



shares = 0
basis =.0
pnl = defaultdict(float)
for dt, row in qqq.iterrows():
    basis += row.c
    shares += 1
    pnl[dt] = (row.c*shares - basis) / basis

t = pd.DataFrame(list(pnl.items()), columns=['dt', 'pnl_dollar_cost_averaging'])
t.set_index('dt', inplace=True)
# ax = t.plot(grid=True, alpha=0.5, ax=ax)
t = t.merge(qqq.cr, how='outer', left_index=True, right_index=True)
t.rename(columns={"cr":"pnl_buy_once_and_hold"}, inplace=True)
t.plot(grid=True, alpha=0.5, ax=ax)
plt.show()
