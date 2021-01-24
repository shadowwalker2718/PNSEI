import matplotlib.pyplot as plt

# Import TimeSeries class
from alpha_vantage.timeseries import TimeSeries

KEY = 'E73RR09H0K7NRUK7'

ALPHA_VANTAGE_API_KEY = KEY

# Initialize the TimeSeries class with key and output format
ts = TimeSeries(key=ALPHA_VANTAGE_API_KEY, output_format='pandas')

# Get pandas dataframe with the intraday data and information of the data
intraday_data, data_info = ts.get_intraday('GOOGL', outputsize='full', interval='1min')

# Print the information of the data
print(data_info)
print(intraday_data.head())

intraday_data['4. close'].plot(figsize=(20, 14))
# Define the label for the title of the figure
plt.title("Close Price", fontsize=16)
# Define the labels for x-axis and y-axis
plt.ylabel('Price', fontsize=14)
plt.xlabel('Time', fontsize=14)
# Plot the grid lines
plt.grid(which="major", color='k', linestyle='-.', linewidth=0.5)
plt.show()
