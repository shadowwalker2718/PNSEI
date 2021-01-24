import time


from polygon import WebSocketClient, STOCKS_CLUSTER


def my_customer_process_message(message):
    print("msg:", message)


def main():
    key = 'K0Rpn6mkCYUP8QSPUuLTPnzJVqpfLeR_'
    my_client = WebSocketClient(STOCKS_CLUSTER, key, my_customer_process_message)
    my_client.run_async()

    my_client.subscribe("T.MSFT", "T.AAPL", "T.AMD", "T.NVDA")
    time.sleep(20)

    my_client.close_connection()


if __name__ == "__main__":
    main()