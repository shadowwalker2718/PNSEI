# Import the quandl
import quandl
import matplotlib.pyplot as plt

# To get your API key, sign up for a free Quandl account.
# Then, you can find your API key on Quandl account settings page.
QUANDL_API_KEY = 'ssNrghoBkos6pPQfQhW2'
# Set the start and end date
start_date = '1990-01-01'
end_date = '2018-03-01'
# Set the ticker name
ticker = 'GD'
# Feth the data
data = quandl.get('WIKI/'+ticker, start_date=start_date, end_date=end_date, api_key=QUANDL_API_KEY)
# Print the first 5 rows of the dataframe
print(data.head())



# Define the figure size for the plot
plt.figure(figsize=(10, 7))
# Plot the adjusted close price
data['Adj. Close'].plot()
# Define the label for the title of the figure
plt.title("Adjusted Close Price of %s" % ticker, fontsize=16)
# Define the labels for x-axis and y-axis
plt.ylabel('Price', fontsize=14)
plt.xlabel('Year', fontsize=14)
# Plot the grid lines
plt.grid(which="major", color='k', linestyle='-.', linewidth=0.5)
plt.show()