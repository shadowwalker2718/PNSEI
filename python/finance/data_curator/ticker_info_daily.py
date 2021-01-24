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


def clean_stock(df_us):
    df_us = df_us[~df_us["name"].str.contains('Acquistion')]
    df_us = df_us[~df_us["name"].str.contains('Acquisition')]
    df_us = df_us[~df_us["name"].str.contains('Warrants')]
    df_us = df_us[~df_us["name"].str.contains('Warrant')]
    df_us = df_us[~df_us["name"].str.contains('Merger')]
    df_us = df_us[~df_us["name"].str.contains('Notes')]
    df_us = df_us[~df_us["name"].str.contains('ETF')]
    df_us = df_us[~df_us["name"].str.contains('Exchange-Traded Fund')]
    df_us = df_us[~df_us["symbol"].str.contains('\.')]
    df_us = df_us[~df_us["symbol"].str.contains('\/')]
    return df_us


def get_us_stocks(df):
    df_us = df.loc[df['country'] == 'United States'].sort_values(by=['marketCap'], ascending=[False])
    df_us = df_us[~df_us["name"].str.contains('Acquistion')]
    df_us = df_us[~df_us["name"].str.contains('Acquisition')]
    df_us = df_us[~df_us["name"].str.contains('Warrants')]
    df_us = df_us[~df_us["name"].str.contains('Warrant')]
    df_us = df_us[~df_us["name"].str.contains('Merger')]
    df_us = df_us[~df_us["name"].str.contains('Notes')]
    df_us = df_us[~df_us["name"].str.contains('ETF')]
    df_us = df_us[~df_us["name"].str.contains('Exchange-Traded Fund')]
    df_us = df_us[~df_us["symbol"].str.contains('\.')]
    df_us = df_us[~df_us["symbol"].str.contains('\/')]
    return df_us


def get_china_stocks(df):
    df_china = df.loc[df['country'] == 'China'].sort_values(by=['marketCap'], ascending=[False])
    df_china = df_china[~df_china["name"].str.contains('Acquistion')]
    df_china = df_china[~df_china["name"].str.contains('Acquisition')]
    df_china = df_china[~df_china["name"].str.contains('Warrants')]
    df_china = df_china[~df_china["name"].str.contains('Warrant')]
    df_china = df_china[~df_china["name"].str.contains('Merger')]
    df_china = df_china[~df_china["name"].str.contains('Notes')]
    df_china = df_china[~df_china["name"].str.contains('ETF')]
    df_china = df_china[~df_china["name"].str.contains('Exchange-Traded Fund')]
    df_china = df_china[~df_china["symbol"].str.contains('\.')]
    df_china = df_china[~df_china["symbol"].str.contains('\/')]
    return df_china


engine_mysql = create_engine('mysql+mysqldb://root:Wufuheng1234!@localhost/sentosa')

def get_symbols():
    res = engine_mysql.execute("SELECT symbol FROM sentosa.ticker_equity where lastsale>0 and volume>1e4 order by marketCap desc;").fetchall()
    r = [i[0] for i in res]
    return r

universe = get_symbols()

def get_time():
    nyc_datetime = datetime.datetime.now(pytz.timezone('US/Eastern'))
    fmt = '%Y-%m-%d %H:%M:%S %Z%z'
    return nyc_datetime.strftime(fmt)


def get_time_obj():
    return datetime.datetime.now(pytz.timezone('US/Eastern'))


keys_company_info = ['symbol', 'open', 'previousClose', 'volume', 'dayLow', 'dayHigh', 'bid', 'bidSize', 'ask',
                     'askSize', 'regularMarketPrice',
                     'sector', 'industry', 'fullTimeEmployees', 'longBusinessSummary', 'city', 'state',
                     'country', 'companyOfficers',
                     'maxAge', 'address1', 'address2', 'zip', 'regularMarketOpen', 'twoHundredDayAverage',
                     'trailingAnnualDividendYield', 'payoutRatio', 'regularMarketDayHigh',
                     'averageDailyVolume10Day',
                     'regularMarketPreviousClose', 'fiftyDayAverage', 'trailingAnnualDividendRate',
                     'averageVolume10days', 'expireDate', 'yield', 'algorithm', 'dividendRate', 'exDividendDate',
                     'beta', 'circulatingSupply',
                     'startDate', 'regularMarketDayLow', 'priceHint', 'currency', 'trailingPE', 'regularMarketVolume',
                     'lastMarket',
                     'maxSupply', 'openInterest', 'marketCap', 'volumeAllCurrencies', 'strikePrice', 'averageVolume',
                     'priceToSalesTrailing12Months',
                     'fiftyTwoWeekHigh', 'forwardPE', 'fiveYearAvgDividendYield',
                     'fiftyTwoWeekLow', 'tradeable', 'dividendYield', 'exchange', 'shortName', 'longName',
                     'exchangeTimezoneName', 'exchangeTimezoneShortName', 'isEsgPopulated', 'gmtOffSetMilliseconds',
                     'quoteType',
                     'market', 'annualHoldingsTurnover', 'enterpriseToRevenue', 'beta3Year',
                     'profitMargins', 'enterpriseToEbitda',
                     '52WeekChange', 'forwardEps', 'revenueQuarterlyGrowth',
                     'sharesOutstanding', 'fundInceptionDate',
                     'annualReportExpenseRatio', 'bookValue', 'sharesShort', 'sharesPercentSharesOut', 'fundFamily',
                     'lastFiscalYearEnd',
                     'heldPercentInstitutions', 'netIncomeToCommon', 'trailingEps', 'lastDividendValue',
                     'SandP52WeekChange', 'priceToBook',
                     'heldPercentInsiders', 'nextFiscalYearEnd', 'mostRecentQuarter', 'shortRatio',
                     'sharesShortPreviousMonthDate', 'floatShares',
                     'enterpriseValue', 'threeYearAverageReturn', 'lastSplitDate', 'lastSplitFactor', 'legalType',
                     'lastDividendDate',
                     'earningsQuarterlyGrowth', 'dateShortInterest', 'pegRatio',
                     'lastCapGain', 'shortPercentOfFloat',
                     'sharesShortPriorMonth', 'impliedSharesOutstanding', 'category', 'fiveYearAverageReturn',
                     'fromCurrency',
                     'toCurrency', 'logo_url', 'ytdReturn', 'navPrice', 'volume24Hr', 'totalAssets', 'website',
                     'messageBoardId', 'morningStarOverallRating', 'morningStarRiskRating']

keys_company_info = sorted(keys_company_info)


def is_float(string):
    try:
        float(string)
        return True
    except Exception:
        return False


def is_int(string):
    try:
        int(string)
        return True
    except Exception:
        return False


columns_float = ['52WeekChange', 'forwardEps', 'bookValue', 'sharesPercentSharesOut', 'heldPercentInstitutions',
                 'trailingEps', 'lastDividendValue', 'SandP52WeekChange', 'priceToBook', 'heldPercentInsiders',
                 'earningsQuarterlyGrowth', 'pegRatio', 'shortPercentOfFloat', 'trailingPE', 'enterpriseToRevenue',
                 'enterpriseToEbitda', 'profitMargins', 'payoutRatio', 'dividendRate', 'dividendYield',
                 'threeYearAverageReturn', 'priceToSalesTrailing12Months', 'shortRatio']
columns_int = ['sharesOutstanding', 'forwardEps', 'netIncomeToCommon',
               'fullTimeEmployees', 'volume24Hr', 'sharesShort']

columns_bigint = ['enterpriseValue', 'floatShares', 'sharesShortPriorMonth']
columns_datetime = ['nextFiscalYearEnd', 'mostRecentQuarter', 'sharesShortPreviousMonthDate', 'fundInceptionDate',
                    'lastSplitDate', 'lastDividendDate', 'dateShortInterest', 'lastFiscalYearEnd', 'exDividendDate',
                    'startDate', 'expireDate']


def ts2dt(ts):
    if not ts:
        return None
    if not is_int(ts):
        import pdb
        pdb.set_trace()
    tz = pytz.timezone('America/New_York')
    return datetime.datetime.fromtimestamp(ts, tz)


def fix_missing_data(company_info):
    for f in columns_float:
        if 'Infinity' == company_info[f]:
            company_info[f] = float('nan')
            return
        if f not in company_info or not is_float(company_info[f]):
            company_info[f] = float('nan')
    for f in columns_int:
        if f not in company_info or not is_int(company_info[f]):
            company_info[f] = None
    for f in columns_bigint:
        if f not in company_info or not is_int(company_info[f]):
            company_info[f] = None
    for f in columns_datetime:
        if f in company_info or is_int(company_info[f]):
            company_info[f] = ts2dt(company_info[f])


def get_url(company_info):
    url = 'https://logo.clearbit.com/'
    if 'logo_url' in company_info:
        if len(company_info['logo_url']) > len(url):
            return "http://www." + company_info['logo_url'][len(url):]
    return ""



universe = set(map(lambda x: x.strip(), universe))
bad_file = os.path.expanduser("~/bad.txt")
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


bad = get_bad()
universe = list(universe - bad)
print(len(universe))

data_type = {"updated": DATETIME(), 'ytdReturn': FLOAT(), 'fullTimeEmployees': INTEGER(), 'symbol': VARCHAR(9),
             'navPrice': FLOAT(), 'totalAssets': FLOAT(), 'expireDate': DATETIME()}
for i in columns_float:
    data_type[i] = FLOAT()
for i in columns_int:
    data_type[i] = BIGINT()
for i in columns_bigint:
    data_type[i] = BIGINT()
for i in columns_datetime:
    data_type[i] = DATETIME()


# https://stackoverflow.com/questions/42461959/how-do-i-perform-an-update-of-existing-rows-of-a-db-table-using-a-pandas-datafra
def create_method(meta):
    def method(table, conn, keys, data_iter):
        sql_table = Table(table.name, meta, autoload=True)
        insert_stmt = dialects.mysql.insert(sql_table).values([dict(zip(keys, data)) for data in data_iter])
        upsert_stmt = insert_stmt.on_duplicate_key_update({x.name: x for x in insert_stmt.inserted})
        conn.execute(upsert_stmt)
    return method

# To fill up stock info
#universe = ['UBER']
universe = sorted(universe)
batch_number = 0
new_symbols = []
print(f"total symbol: {len(universe)}")
print(f"existing symbol: {len(new_symbols)}")
while batch_number < 500:
    new_symbols = []
    try:
        res = engine_mysql.execute("SELECT symbol FROM sentosa.ticker_info where updated > DATE_ADD(NOW(), INTERVAL -2 DAY) order by symbol").fetchall()
        if len(res) > 0:
            new_symbols = [i[0] for i in res]
        print("finished symbols:", len(new_symbols))
    except Exception:
        pass
    if len(universe) == len(new_symbols):
        break
    d = None
    new_symbols_set = set(new_symbols)
    with engine_mysql.begin() as cx:
        for idx, ticker in enumerate(universe):
            if ticker in new_symbols_set or ticker in bad:
                continue
            t = yf.Ticker(ticker)
            try:
                company_info = {k: t.info[k] if k in t.info else '' for k in keys_company_info}
                print(idx, company_info['symbol'], end=',')
                if idx % 20 == 1:
                    print('')
                company_info['updated'] = get_time_obj()
                company_info['source'] = 'yfin'
                for k, v in company_info.items():
                    try:
                        if v == 'Infinity':
                            company_info[k] = float('nan')
                        str(v).encode('ascii')
                    except Exception:
                        company_info[k] = re.sub(r'[^\x00-\x7F]+', ' ', v)
                if company_info['regularMarketPrice'] is None:
                    bad.add(ticker)
                    write_bad(ticker)
                    continue
                # fix missing data
                fix_missing_data(company_info)
                d = pd.json_normalize(company_info)
                d.drop(columns=['companyOfficers', 'logo_url', 'messageBoardId', 'morningStarOverallRating',
                                'morningStarRiskRating', 'algorithm', 'gmtOffSetMilliseconds'], inplace=True)
                # if 'companyOfficers' in d:
                #    d['companyOfficers'] = d['companyOfficers'].astype('str')
                d.set_index('symbol', inplace=True)
                # append the row the the table, replace will replace the entire table
                meta = MetaData(cx)
                my_method = create_method(meta)
                d.to_sql('ticker_info', con=cx, dtype=data_type, index=True, if_exists='append', index_label='symbol', method=my_method)
                time.sleep(1) # urllib.error.HTTPError: HTTP Error 503: Service Unavailable
                if idx % 10 == 5:
                    break
            except requests.HTTPError as ve:
                print(f"ticker1:{ticker}", ve)
                time.sleep(60*2)
            except ValueError as ve:
                bad.add(ticker)
                write_bad(ticker)
                universe.remove(ticker)
                print(f"ticker2:{ticker}", ve)
                traceback.print_exc()
                continue
            except Exception as ve:
                traceback.print_exc()
                bad.add(ticker)
                write_bad(ticker)
                print(f"ticker3:{ticker}", ve)
                universe.remove(ticker)
                time.sleep(60 * 2)
                continue
    batch_number += 1