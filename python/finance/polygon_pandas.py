from pandas_polygon_api import PPA as ppa
from datetime import datetime

ppa_client = ppa(api_key='AK7ZO195L18ASY14JYGP')
f = ppa_client.get_financials('UBER')
#ppa_client.snap_shot_all()  # Snap Shot of whole market (minute aggregation)
h = ppa_client.get_historic_trades(ticker="SPY",
                               dates=[datetime(2020, 4, 21),
                                      datetime(2020, 4, 22)
                                      ])  # Gets all trades taken on SPY on  2020-04-21 and 2020-04-22
b = ppa_client.get_intraday_bar_agg(ticker="SPY",
                                start_date=datetime(2020, 1, 1),
                                end_date=datetime(2020, 2, 1),
                                agg_period=1,
                                unadjusted=False
                                )  # Gets intraday minute bars of SPY for the whole month of January 2020

