# LinearRegression is a machine learning library for linear regression
from sklearn.linear_model import LinearRegression
# pandas and numpy are used for data manipulation
import pandas as pd
import numpy as np
# matplotlib and seaborn are used for plotting graphs
import matplotlib.pyplot as plt
import seaborn
# fix_yahoo_finance is used to fetch data
import yfinance as yf

# Read data
Df = yf.download('GLD','2008-01-01','2017-12-31')
# Only keep close columns
Df=Df[['Close']]
# Drop rows with missing values
Df= Df.dropna()
# Plot the closing price of GLD
Df.Close.plot(figsize=(10,5))
plt.ylabel("Gold ETF Prices")
plt.show()