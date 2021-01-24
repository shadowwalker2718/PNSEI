import pysnowball as ball

xq_a_token = 'ab607de29b9e07302ab114617b7f08b81d9e6df1'
xq_a_token = 'c1bacbbc6e2fbb15ae275f40b823f8ac8598feb8'

ball.set_token(f'xq_a_token={xq_a_token};')

result=ball.capital_flow('UBER')
print(result)

result = ball.quotec('LI')
print(result)

result = ball.report('LI')
print(result)

result = ball.earningforecast('SZ002027')
print(result)
