import requests
import os, sys

import sqlite3
import pandas as pd
import numpy as np
import yfinance as yf
import matplotlib.pyplot as plt
from sqlalchemy import create_engine, MetaData, Table, dialects
import time
import requests
import datetime, pytz
from sqlalchemy.types import DATETIME, FLOAT, INTEGER, VARCHAR, BIGINT
import re
import traceback

ymd = datetime.datetime.today().strftime('%Y-%m-%d')

headers = {
    'authority': 'www.nasdaq.com',
    'upgrade-insecure-requests': '1',
    'user-agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.116 Safari/537.36',
    'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'sec-fetch-site': 'cross-site',
    'sec-fetch-mode': 'navigate',
    'sec-fetch-user': '?1',
    'sec-fetch-dest': 'document',
    'referer': 'https://github.com',
    'accept-language': 'en-US,en;q=0.9',
    'cookie': 'AKA_A2=A; NSC_W.TJUFEFGFOEFS.OBTEBR.443=ffffffffc3a0f70e45525d5f4f58455e445a4a42378b',
}
url = 'https://api.nasdaq.com/api/screener/stocks?tableonly=true&limit=2500&offset=0&download=true'

data_folder = os.path.expanduser("~/sentosa")

if not os.path.exists(data_folder):
    os.makedirs(data_folder)

stock_summary_file_name = f"{data_folder}/stock_summary_{ymd}.csv"
if os.path.exists(stock_summary_file_name):
    print(stock_summary_file_name, "is already there.")
else:
    response = requests.get(url, headers=headers)
    resp = response.json()

    headers = resp['data']['headers']
    rows = resp['data']['rows']

    with open(stock_summary_file_name, '+w') as stock_summary_file:
        line = '"' + '","'.join(rows[0].keys()) + '"\n'
        stock_summary_file.write(line)
        for row in rows:
            if 'lastsale' in row.keys():
                row['lastsale'] = row['lastsale'].replace(',', '')
                row['lastsale'] = row['lastsale'].replace('$', '')
                row['lastsale'] = row['lastsale'].replace('NA', 'NaN')
            if 'url' in row.keys():
                row['url'] = 'http://www.nasdaq.com' + row['url']
            if 'ipoyear' in row.keys():
                if row['ipoyear'] == '':
                    row['ipoyear'] = 1000
            if 'pctchange' in row.keys():
                if row['pctchange'] == '':
                    row['ipoyear'] = '0'
                else:
                    row['pctchange'] = float(row['pctchange'].strip('%')) / 100
            line = '"' + '","'.join(str(item) for item in row.values()) + '"\n'
            stock_summary_file.write(line)

    print(f"Wrote {len(rows)} lines into file {stock_summary_file_name}")

##############################################################################################3
df = pd.read_csv(stock_summary_file_name, dtype = {'ipoyear': int, 'pctchange': float})

def get_time_obj():
    return datetime.datetime.now(pytz.timezone('US/Eastern'))
# https://stackoverflow.com/questions/42461959/how-do-i-perform-an-update-of-existing-rows-of-a-db-table-using-a-pandas-datafra
def create_method(meta):
    def method(table, conn, keys, data_iter):
        sql_table = Table(table.name, meta, autoload=True)
        insert_stmt = dialects.mysql.insert(sql_table).values([dict(zip(keys, data)) for data in data_iter])
        upsert_stmt = insert_stmt.on_duplicate_key_update({x.name: x for x in insert_stmt.inserted})
        conn.execute(upsert_stmt)
    return method

data_type = {'symbol': VARCHAR(9)}

engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')
with engine_mysql.begin() as cx:
    df['updated'] = get_time_obj()
    df['source'] = 'nasdaq'
    df.set_index('symbol', inplace=True)
    meta = MetaData(cx)
    my_method = create_method(meta)
    df.to_sql('ticker_equity', con=cx, dtype=data_type, index=True,
              if_exists='append', index_label='symbol', method=my_method)


