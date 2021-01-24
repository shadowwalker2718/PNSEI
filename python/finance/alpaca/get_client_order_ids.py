import alpaca_trade_api as tradeapi
import my_alpaca


api = tradeapi.REST()

# Submit a market order and assign it a Client Order ID.
api.submit_order(
    symbol='AAPL',
    qty=1,
    side='buy',
    type='limit',
    limit_price=20.50,
    time_in_force='gtc',
    client_order_id='my_first_order'
)

# Get our order using its Client Order ID.
my_order = api.get_order_by_client_order_id('my_first_order')
print('Got order #{}'.format(my_order.id))
print(my_order)