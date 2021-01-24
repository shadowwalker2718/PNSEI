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
import json

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

sectors = """
{
            "filtertitle":"Sector",
            "filtertype":"dropdown",
            "filterid":"sector",
            "options":[
               {
                  "name":"Agriculture",
                  "value":"agriculture"
               },
               {
                  "name":"Alternative Investments",
                  "value":"alternative-investments"
               },
               {
                  "name":"Asia",
                  "value":"asia"
               },
               {
                  "name":"Biotech",
                  "value":"biotech"
               },
               {
                  "name":"Bonds",
                  "value":"bonds"
               },
               {
                  "name":"Commodities",
                  "value":"commodities"
               },
               {
                  "name":"Construction",
                  "value":"construction"
               },
               {
                  "name":"Consumer Discretionary",
                  "value":"consumer-discretionary"
               },
               {
                  "name":"Consumer Non-Cyclical",
                  "value":"consumer-non-cyclical"
               },
               {
                  "name":"Consumer Services",
                  "value":"consumer-services"
               },
               {
                  "name":"Consumer Staples",
                  "value":"consumer-staples"
               },
               {
                  "name":"Currency",
                  "value":"currency"
               },
               {
                  "name":"Defense",
                  "value":"defense"
               },
               {
                  "name":"Emerging Markets",
                  "value":"emerging-markets"
               },
               {
                  "name":"Energy",
                  "value":"energy"
               },
               {
                  "name":"Environmental",
                  "value":"environmental"
               },
               {
                  "name":"Europe",
                  "value":"europe"
               },
               {
                  "name":"Financial Services",
                  "value":"financial-services"
               },
               {
                  "name":"Grains",
                  "value":"grains"
               },
               {
                  "name":"Healthcare",
                  "value":"healthcare"
               },
               {
                  "name":"Hotels & Gambling",
                  "value":"hotels-gambling"
               },
               {
                  "name":"Income",
                  "value":"income"
               },
               {
                  "name":"Industrial",
                  "value":"Industrial"
               },
               {
                  "name":"International",
                  "value":"international"
               },
               {
                  "name":"Large Cap",
                  "value":"large-cap"
               },
               {
                  "name":"Managed ETFs",
                  "value":"managed-etfs"
               },
               {
                  "name":"Materials",
                  "value":"materials"
               },
               {
                  "name":"Meats",
                  "value":"meats"
               },
               {
                  "name":"Metals",
                  "value":"metals"
               },
               {
                  "name":"Mid Cap",
                  "value":"mid-cap"
               },
               {
                  "name":"Mixed Asset",
                  "value":"mixed-asset"
               },
               {
                  "name":"Multi Cap",
                  "value":"multi-cap"
               },
               {
                  "name":"Natural Resources",
                  "value":"natural-resources"
               },
               {
                  "name":"Non-Taxable",
                  "value":"non-taxable"
               },
               {
                  "name":"Power",
                  "value":"power"
               },
               {
                  "name":"Precious Metals",
                  "value":"precious-metals"
               },
               {
                  "name":"Real Estate",
                  "value":"real-estate"
               },
               {
                  "name":"Small Cap",
                  "value":"small-cap"
               },
               {
                  "name":"Taxable Bonds",
                  "value":"taxable-bonds"
               },
               {
                  "name":"Technology",
                  "value":"technology"
               },
               {
                  "name":"Telecommunications",
                  "value":"telecommunications"
               },
               {
                  "name":"Transportation",
                  "value":"transportation"
               },
               {
                  "name":"Utilities",
                  "value":"utilities"
               }
            ]
         }
"""

asset_class = """
{
            "filtertitle":"Asset Class",
            "filtertype":"dropdown",
            "filterid":"assetclass",
            "options":[
               {
                  "name":"Bond",
                  "value":"bond"
               },
               {
                  "name":"Commodity",
                  "value":"commodity"
               },
               {
                  "name":"Currency",
                  "value":"currency"
               },
               {
                  "name":"Equity",
                  "value":"equity"
               },
               {
                  "name":"Fixed Income",
                  "value":"fixed"
               },
               {
                  "name":"Liquidated Fund",
                  "value":"liquidated"
               },
               {
                  "name":"Multi-Asset",
                  "value":"multi-asset"
               },
               {
                  "name":"Volatility",
                  "value":"volatility"
               }
            ]
         }
"""

region = """
{
            "filtertitle":"Geography",
            "filtertype":"dropdown",
            "filterid":"region",
            "options":[
               {
                  "name":"Africa",
                  "value":"africa"
               },
               {
                  "name":"Asia-Pacific",
                  "value":"asia-pacific"
               },
               {
                  "name":" Europe-Australia and Far East",
                  "value":"EAFE"
               },
               {
                  "name":"Europe",
                  "value":"europe"
               },
               {
                  "name":"Global",
                  "value":"global"
               },
               {
                  "name":"Latin America",
                  "value":"latin-america"
               },
               {
                  "name":"Middle East",
                  "value":"middle-east"
               },
               {
                  "name":"North America",
                  "value":"north-america"
               }
            ]
         }
"""

engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')

data = json.loads(sectors)
for row in data['options']:
    url = 'https://api.nasdaq.com/api/screener/etf?sector=' + row['value']
    response = requests.get(url, headers=headers)
    if response.status_code != 200:
        print(f"response.status_code: {response.status_code}")
        sys.exit(0)
    resp = response.json()
    if resp['data']['records']['totalrecords'] > 0:
        rs = resp['data']['records']['data']['rows']
        for r in rs:
            symbol = r['symbol']
            sql = f"update ticker_etf set sector='{row['value']}' where symbol='{symbol}'"
            engine_mysql.execute(sql)

data = json.loads(asset_class)
for row in data['options']:
    url = 'https://api.nasdaq.com/api/screener/etf?assetclass=' + row['value']
    response = requests.get(url, headers=headers)
    if response.status_code != 200:
        print(f"response.status_code: {response.status_code}")
        sys.exit(0)
    resp = response.json()
    if resp['data']['records']['totalrecords'] > 0:
        rs = resp['data']['records']['data']['rows']
        for r in rs:
            symbol = r['symbol']
            sql = f"update ticker_etf set assetclass='{row['value']}' where symbol='{symbol}'"
            engine_mysql.execute(sql)

data = json.loads(region)
for row in data['options']:
    url = 'https://api.nasdaq.com/api/screener/etf?region=' + row['value']
    response = requests.get(url, headers=headers)
    if response.status_code != 200:
        print(f"response.status_code: {response.status_code}")
        sys.exit(0)
    resp = response.json()
    if resp['data']['records']['totalrecords'] > 0:
        rs = resp['data']['records']['data']['rows']
        for r in rs:
            symbol = r['symbol']
            sql = f"update ticker_etf set region='{row['value']}' where symbol='{symbol}'"
            engine_mysql.execute(sql)

url = 'https://api.nasdaq.com/api/screener/etf?dividends=true'
response = requests.get(url, headers=headers)
if response.status_code != 200:
    print(f"response.status_code: {response.status_code}")
    sys.exit(0)
resp = response.json()
if resp['data']['records']['totalrecords'] > 0:
    rs = resp['data']['records']['data']['rows']
    for r in rs:
        symbol = r['symbol']
        sql = f"update ticker_etf set pay_dividend=1 where symbol='{symbol}'"
        engine_mysql.execute(sql)

url = 'https://api.nasdaq.com/api/screener/etf?options=true'
response = requests.get(url, headers=headers)
if response.status_code != 200:
    print(f"response.status_code: {response.status_code}")
    sys.exit(0)
resp = response.json()
if resp['data']['records']['totalrecords'] > 0:
    rs = resp['data']['records']['data']['rows']
    for r in rs:
        symbol = r['symbol']
        sql = f"update ticker_etf set has_option=1 where symbol='{symbol}'"
        engine_mysql.execute(sql)
