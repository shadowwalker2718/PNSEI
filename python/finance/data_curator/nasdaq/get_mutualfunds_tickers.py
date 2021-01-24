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
def process_row_text(row, k):
    if row[k] is None or row[k] == 'None':
        row[k] = ''
def process_row_float(row, k):
    if row[k] is not None:
        row[k] = row[k].replace(',', '')
        row[k] = row[k].replace('$', '')
    if k in row.keys():
        try:
            row[k] = float(row[k])
        except Exception:
            row[k] = float('nan')
def process_row_percent(row, k):
    if k in row.keys():
        if row[k] is not None:
            row[k] = row[k].replace('%', '')
        try:
            row[k] = float(row[k]) * 0.01
        except Exception:
            row[k] = float('nan')

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
url = 'https://api.nasdaq.com/api/screener/mutualfunds?tableonly=true&limit=100000&offset=0&download=true'

mutual_funds_summary_file_name = os.path.expanduser(f"~/mutual_funds_summary_{ymd}.csv")
if os.path.exists(mutual_funds_summary_file_name):
    print(f"file {mutual_funds_summary_file_name} exists already")

else:

    response = requests.get(url, headers=headers)
    if response.status_code != 200:
        print(f"response.status_code: {response.status_code}")
        sys.exit(0)
    resp = response.json()

    headers = resp['data']['records']['data']['headers']
    rows = resp['data']['records']['data']['rows']

    with open(os.path.expanduser(f"~/mutual_funds_tickers_{ymd}.csv"), '+w') as mutual_funds_ticker_file:
        for row in rows:
            line = row['symbol'] + "\n"
            mutual_funds_ticker_file.write(line)

    with open(mutual_funds_summary_file_name, '+w') as mutual_funds_summary_file:
        line = '"' + '","'.join(rows[0].keys()) + '"\n'
        mutual_funds_summary_file.write(line)
        for row in rows:
            process_row_text(row, 'companyName')
            process_row_text(row, 'fundType')
            process_row_text(row, 'deltaIndicator')
            process_row_float(row, 'lastSalePrice')
            process_row_float(row, 'netChange')
            process_row_percent(row, 'percentageChange')
            if row['deltaIndicator'] == 'down':
                row['netChange'] = row['netChange'] * -1
                row['percentageChange'] = row['percentageChange'] * -1
            line = '"' + '","'.join(str(item) for item in row.values()) + '"\n'
            mutual_funds_summary_file.write(line)

    print(f"Wrote {len(rows)} lines into file {mutual_funds_summary_file_name}")


##############################################################################################3
df = pd.read_csv(mutual_funds_summary_file_name, dtype = {'percentageChange': float, 'netChange': float})

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
    df.drop(columns=['deltaIndicator'], inplace=True)
    df.rename(columns={'netChange': 'priceChange'}, inplace=True)
    meta = MetaData(cx)
    my_method = create_method(meta)
    df.to_sql('ticker_fund', con=cx, dtype=data_type, index=True,
              if_exists='append', index_label='symbol', method=my_method, chunksize=10240)


