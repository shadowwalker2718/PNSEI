import yfinance as yf
from pprint import pprint as pp

msft = yf.Ticker("TSLA")

# get stock info
pp(msft.info)

# get historical market data
hist = msft.history(period="3d")
print(hist)


