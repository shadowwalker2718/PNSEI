"""
CREATE TABLE sentosa.`bar1d_poly` (
  `s` varchar(8) NOT NULL,
  `o` float DEFAULT NULL,
  `h` float DEFAULT NULL,
  `l` float DEFAULT NULL,
  `c` float DEFAULT NULL,
  `v` int(11) DEFAULT NULL,
  `w` float DEFAULT NULL,
  `dt` date DEFAULT NULL,
  UNIQUE KEY `s_dt_idx` (`s`,`dt`),
  KEY `idx_dt` (`dt`),
  KEY `idx_s` (`s`)
) ENGINE=MyISAM;

"""
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
import requests
import datetime, pytz
from sqlalchemy.types import DATETIME, FLOAT, INTEGER, VARCHAR, BIGINT
import re
import traceback


def get_dates():
    dates = []
    from_date = datetime.datetime.now().strftime('%Y-%m-01')
    end_date = datetime.datetime.now().strftime('%Y-%m-31')
    for i in range(365 * 5, 0, -30):
        tmp = (datetime.datetime.now() + datetime.timedelta(days=i))
        from_date = tmp.strftime('%Y-%m-01')
        end_date = tmp.strftime('%Y-%m-31')
        dates.append(from_date)

    for i in range(30, 365 * 10, 30):
        tmp = (datetime.datetime.now() - datetime.timedelta(days=i))
        from_date = tmp.strftime('%Y-%m-01')
        end_date = tmp.strftime('%Y-%m-31')
        dates.append(from_date)

    return dates


print("""
CREATE TABLE sentosa.`bar1m_bk` (
  `s` varchar(8) NOT NULL,
  `o` float DEFAULT NULL,
  `h` float DEFAULT NULL,
  `l` float DEFAULT NULL,
  `c` float DEFAULT NULL,
  `v` int(11) DEFAULT NULL,
  `w` float DEFAULT NULL,
  `bc` mediumint(9) DEFAULT NULL,
  `dt` datetime DEFAULT NULL,
  UNIQUE KEY `bar1m_pk` (`s`,`dt`),
  KEY `idx_dt` (`dt`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1
PARTITION BY RANGE COLUMNS(dt) (""")

dates = get_dates()
dates = sorted(list(set(dates)))
for dt in dates:
    pname = dt.replace('-','')
    print(f"PARTITION p{pname} VALUES LESS THAN( '{dt} 00:00:00' ),")

print('PARTITION rxother VALUES LESS THAN MAXVALUE);')


print("*"*80)


print("""
CREATE TABLE sentosa.`bar1m_partitioned_symbol` (
  `s` varchar(8) NOT NULL,
  `o` float DEFAULT NULL,
  `h` float DEFAULT NULL,
  `l` float DEFAULT NULL,
  `c` float DEFAULT NULL,
  `v` int(11) DEFAULT NULL,
  `w` float DEFAULT NULL,
  `bc` mediumint(9) DEFAULT NULL,
  `dt` datetime DEFAULT NULL,
  UNIQUE KEY `bar1m_pk` (`s`,`dt`),
  KEY `idx_dt` (`dt`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1
PARTITION BY RANGE COLUMNS(s) (
""")

from string import ascii_lowercase
for i in ascii_lowercase:
    for j in ascii_lowercase:
        pname = f'{i}{j}'
        print(f"PARTITION p{pname} VALUES LESS THAN( '{pname}' ),")

print('PARTITION pother VALUES LESS THAN MAXVALUE);')
