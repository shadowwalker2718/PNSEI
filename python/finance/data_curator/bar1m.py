from polygon import RESTClient
import pymysql
import requests
import os, sys
import sqlite3
import pandas as pd
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt
from sqlalchemy import create_engine, MetaData, Table, dialects
import time
import datetime, pytz
from sqlalchemy.types import DATETIME, FLOAT, INTEGER, VARCHAR, BIGINT
import re
import traceback


engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')


# Get dates of past 10 years
def get_dates(years=10):
    dates = []
    end_date = datetime.datetime.now().strftime('%Y-%m-%d')
    for i in range(30, 365 * years, 30):
        from_date = (datetime.datetime.now() - datetime.timedelta(days=i)).strftime('%Y-%m-%d')
        dates.append((from_date, end_date))
        end_date = from_date
    return dates

# get stocks with cap > 50M USD and trading volume>100K of last Friday
def get_symbols():
    res = engine_mysql.execute("SELECT symbol FROM sentosa.ticker_info where marketCap>2e8 and volume>2e5 order by symbol desc").fetchall()
    r = [i[0] for i in res]
    return r


symbols = get_symbols()
for index in ['SPY', 'QQQ']:
    if index not in symbols:
        symbols.insert(0, index)
#symbols=['QQQ']
dates = get_dates(3)

# Pre-market trading in stocks occurs from 4 a.m. to 9:30 a.m. EST, and after-hours trading on a day with a normal session takes place from 4 p.m. to 8 p.m.
offset = time.timezone if (time.localtime().tm_isdst == 0) else time.altzone
offset = offset - 18000


def ts_to_datetime(ts) -> str:
    return datetime.datetime.fromtimestamp(ts / 1000.0 + offset).strftime('%Y-%m-%d %H:%M:%S')

#symbols = ['UBER']

def main():
    key = "AK7ZO195L18ASY14JYGP"
    # RESTClient can be used as a context manager to facilitate closing the underlying http session
    # https://requests.readthedocs.io/en/master/user/advanced/#session-objects
    print(f"symbols number: {len(symbols)}")
    for symbol in symbols:
        print(symbol)
        for from_date, to_date in dates:
            sql = f"SELECT count(*) as cnt FROM sentosa.`bar1m_partitioned_symbol` where s='{symbol}' and dt>'{from_date}' and dt<='{to_date}'"
            res = engine_mysql.execute(sql).fetchall()
            print(res, from_date, to_date)
            if int(res[0][0]) > 0: #60*8*18:
                continue
                #break
            count = 0
            retry = 0
            with RESTClient(key) as client:
                try:
                    resp = client.stocks_equities_aggregates(symbol, 1, "minute", from_date, to_date, unadjusted=False, limit=50000)
                    if resp.resultsCount == 0:
                        print("Error: ", symbol, from_date, to_date)
                        break
                    values = []
                    for result in resp.results:
                        dt = ts_to_datetime(result["t"])
                        if 'vw' not in result:
                            result['vw'] = result['o']
                        values.append(f"('{symbol}',{result['o']},{result['h']},{result['l']},{result['c']},{result['v']},{result['vw']},-1,'{dt}')")
                        count += 1
                        if count % 5000 == 2:
                            write_bar1m(engine_mysql, values)
                            values = []
                            print(f"[{from_date},{to_date}]", end='')
                    write_bar1m(engine_mysql, values)
                    time.sleep(1)
                    print('')
                except (requests.HTTPError, Exception) as ve:
                    print(f"Error: symbol:{symbol}, from:{from_date}, to:{to_date}, error: {str(ve)}")
                    retry += 1
                    if retry > 5:
                        traceback.print_exc()
                        print("*"*120)
                        print("Failed after 5 retries...Exit!!!")
                        sys.exit(0)
                    time.sleep(10*60)


def write_bar1m(engine, values):
    if values:
        vs = ',\n'.join(values)
        sql_dt = f"insert ignore into sentosa.`bar1m_partitioned_date`(s,o,h,l,c,v,w,bc,dt)VALUES{vs}"
        sql_sy = f"insert ignore into sentosa.`bar1m_partitioned_symbol`(s,o,h,l,c,v,w,bc,dt)VALUES{vs}"
        #print(f"sql: {sql_dt}")
        engine.execute(sql_dt)
        engine.execute(sql_sy)


if __name__ == '__main__':
    main()
