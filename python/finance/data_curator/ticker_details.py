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
from sqlalchemy.types import DATETIME, FLOAT, INTEGER, VARCHAR, BIGINT, DATE
import re
import traceback
from pandas_polygon_api import PPA

# How to update????

engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')


def get_no_country_symbols():
    #sql = 'select symbol from ticker_equity where country is NULL order by symbol;'
    sql = 'select distinct symbol from ticker_equity where lastsale >0'
    res = engine_mysql.execute(sql).fetchall()
    r = [i[0] for i in res]
    return r


symbols = get_no_country_symbols()
data_type = {'symbol': VARCHAR(9), 'listdate': DATE()}

pd.options.mode.chained_assignment = None

def create_method(meta):
    def method(table, conn, keys, data_iter):
        sql_table = Table(table.name, meta, autoload=True)
        insert_stmt = dialects.mysql.insert(sql_table).values([dict(zip(keys, data)) for data in data_iter])
        upsert_stmt = insert_stmt.on_duplicate_key_update({x.name: x for x in insert_stmt.inserted})
        conn.execute(upsert_stmt)
    return method

bad_file = os.path.expanduser("~/bad_ticker.txt")
def get_bad():
    if not os.path.exists(bad_file):
        return set()
    # define an empty list
    places = set()
    # open file and read the content in a list
    with open(bad_file, 'r') as filehandle:
        for line in filehandle:
            # remove linebreak which is the last character of the string
            currentPlace = line[:-1]
            # add item to the list
            places.add(currentPlace)
    return places

def write_bad(t):
    tmp = get_bad()
    with open(bad_file, 'a+') as filehandle:
        if t not in tmp:
            filehandle.write('%s\n' % t)

bad=get_bad()


def main():
    key = "AK7ZO195L18ASY14JYGP"
    # RESTClient can be used as a context manager to facilitate closing the underlying http session
    # https://requests.readthedocs.io/en/master/user/advanced/#session-objects
    print(f"symbols number: {len(symbols)}")

    ppa_client = PPA(api_key=key)

    existing_symbols = set()
    try:
        res = engine_mysql.execute("SELECT symbol FROM sentosa.ticker_details order by symbol").fetchall()
        if len(res) > 0:
            tmp = [i[0] for i in res]
            existing_symbols = set(tmp)
            print("finished symbols:", len(existing_symbols))
    except Exception:
        pass

    count = 0
    for symbol in symbols:
        if symbol in bad or symbol in existing_symbols:
            continue
        try:
            df = ppa_client.get_ticker_details(ticker=symbol)
            new_header = df.T.iloc[0]
            df = df.T[1:]
            df.columns = new_header
            df.drop(columns=['logo'], inplace=True)
            df['symbol'] = symbol
            df['source'] = 'poly'
            df = df.set_index('symbol')
            df['tags'] = df['tags'].str.join(',')
            df['similar'] = df['similar'].str.join(',')
            with engine_mysql.begin() as cx:
                meta = MetaData(cx)
                my_method = create_method(meta)
                df.to_sql('ticker_details', con=cx, dtype=data_type, index=True, if_exists='append', index_label='symbol', method=my_method)
            count += 1
            if count%500 == 2:
                print('count:', count, symbol, end='')
            time.sleep(1)
        except (requests.HTTPError, Exception) as ve:
            write_bad(symbol)
            #print(f"Error: symbol:{symbol}, error: {str(ve)}")
            time.sleep(1)

print("bad tickers:",bad)

if __name__ == '__main__':
    main()
