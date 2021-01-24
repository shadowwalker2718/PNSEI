# Import the quandl
import quandl
import matplotlib.pyplot as plt

# To get your API key, sign up for a free Quandl account.
# Then, you can find your API key on Quandl account settings page.
QUANDL_API_KEY = 'ssNrghoBkos6pPQfQhW2'

# Define the ticker list
import pandas as pd

# Set the start and end date
start_date = '2015-01-01'
end_date = '2020-12-10'

tickers_list = ['AAPL', 'IBM', 'MSFT', 'WMT']
# Import pandas
data = pd.DataFrame(columns=tickers_list)
# Feth the data
for ticker in tickers_list:
    data[ticker] = quandl.get('WIKI/' + ticker, start_date=start_date,
                              end_date=end_date, api_key=QUANDL_API_KEY)['Adj. Close']
# Print first 5 rows of the data
data.head()

# Plot all the close prices
data.plot(figsize=(10, 7))
# Show the legend
plt.legend()
# Define the label for the title of the figure
plt.title("Adjusted Close Price", fontsize=16)
# Define the labels for x-axis and y-axis
plt.ylabel('Price', fontsize=14)
plt.xlabel('Year', fontsize=14)
# Plot the grid lines
plt.grid(which="major", color='k', linestyle='-.', linewidth=0.5)
plt.show()
