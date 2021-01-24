import time, json, math

from polygon import WebSocketClient, STOCKS_CLUSTER

prev_quote = {}
prev_trade = None


def message_handler(message):
    global prev_quote, prev_trade
    try:
        m = json.loads(message)
        for i in m:
            if i['ev'] == 'status':
                #{'ev': 'status', 'status': 'connected', 'message': 'Connected Successfully'}
                pass
            """
            if i['ev'] == 'T':
                if prev_trade != i['p']:
                    print("\t\t", i['t'], 'T', i['sym'], i['p'])
                    prev_trade = i['p']
            """
            if i['ev'] == 'Q':
                sm = i['sym']
                if not math.isclose(prev_quote[sm][0], i['bp']) or \
                        not math.isclose(prev_quote[sm][1], i['ap']):
                    print(i['t'], 'Q', sm, i['bp'], i['ap'])
                    prev_quote[sm] = (i['bp'], i['ap'])
    except Exception as e:
        print('Error:', str(e))


def main():
    global prev_quote, prev_trade
    symbols = ["UBER", "LYFT"]
    q_symbols = ['Q.'+i for i in symbols]
    for s in symbols:
        prev_quote[s] = [0,0]
    my_client = WebSocketClient(STOCKS_CLUSTER, "AK7ZO195L18ASY14JYGP", message_handler)
    my_client.run_async()

    my_client.subscribe(*q_symbols)
    time.sleep(60)

    my_client.close_connection()


if __name__ == "__main__":
    main()