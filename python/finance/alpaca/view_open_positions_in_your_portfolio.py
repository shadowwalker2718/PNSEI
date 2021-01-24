import alpaca_trade_api as tradeapi

api = tradeapi.REST()

# Get a list of all of our positions.
portfolio = api.list_positions()



# Get our position in AAPL.
aapl_position = api.get_position('AAPL')



# Print the quantity of shares for each position.
for position in portfolio:
    print("{} shares of {}".format(position.qty, position.symbol))
