#ifndef PNSEI_STOCK_TRADING_H
#define PNSEI_STOCK_TRADING_H

/* https://www.1point3acres.com/bbs/thread-653048-1-1.html
 * https://www.1point3acres.com/bbs/thread-654361-1-1.html
 * 第一题是股票买卖，题目如下：

Take in a stream of orders (as lists of limit price, quantity, and side, like ["155", "3", "buy"]) and return the total number of executed shares.

Rules
- An incoming buy is compatible with a standing sell if the buy's price is >= the sell's price. Similarly, an incoming sell is compatible with a standing buy if the sell's price <= the buy's price.
- An incoming order will execute as many shares as possible against the best compatible order, if there is one (by "best" we mean most favorable to the incoming order).
- Any remaining shares will continue executing against the best compatible order, if there is one. If there are shares of the incoming order remaining and no compatible standing orders, the incoming order becomes a standing order.

Example input:
Stream of orders
("150", "10", "buy"), ("165", "7", "sell"), ("168", "3", "buy"), ("155", "5", "sell"), ("166", "8", "buy")


 |    |
 |____| seller order book

 |----| buyer order book
 |    |
*/
#include "henry.h"

struct order{
  int price;
  int quantity;
  bool is_long;
};

struct max_heap_comp {
  bool operator()(order& a, order& b){
    return a.price<b.price;
  }
};

struct min_heap_comp {
  bool operator()(order& a, order& b){
    return a.price>b.price;
  }
};

struct OrderBook{
  priority_queue<order, vector<order>, min_heap_comp> seller_orderbook;
  priority_queue<order, vector<order>, max_heap_comp> buyer_orderbook;

  void send(order o) {
    if (o.is_long){
      if (seller_orderbook.empty()){
        buyer_orderbook.push(o);
        return;
      }
      order t = seller_orderbook.top();
      if (t.price > o.price){
        buyer_orderbook.push(o);
      } else {
        consume_seller_book(o);
      }
    } else {
      if (buyer_orderbook.empty()){
        seller_orderbook.push(o);
        return;
      }
      order t = buyer_orderbook.top();
      if (t.price < o.price){
        seller_orderbook.push(o);
      } else { // deal
        consume_buyer_book(o);
      }
    }
  }

  void consume_seller_book(order buy_order){
    order sell_order = seller_orderbook.top();
    while(sell_order.price<= buy_order.price and buy_order.quantity>0){
      seller_orderbook.pop();
      if (sell_order.quantity >= buy_order.quantity){
        sell_order.quantity -= buy_order.quantity;
        buy_order.quantity = 0;
        if (sell_order.quantity)
          seller_orderbook.push(sell_order);
      } else {
        buy_order.quantity -= sell_order.quantity;
      }
      if (seller_orderbook.empty())
        break;
      sell_order = seller_orderbook.top();
    }
    if(buy_order.quantity>0){
      buyer_orderbook.push(buy_order);
    }
  }

  void consume_buyer_book(order sell_order){
    order buy_order = buyer_orderbook.top();
    while(buy_order.price>= sell_order.price and sell_order.quantity>0){
      buyer_orderbook.pop();
      if (buy_order.quantity >= sell_order.quantity){
        buy_order.quantity -= sell_order.quantity;
        sell_order.quantity = 0;
        if (buy_order.quantity>0)
          buyer_orderbook.push(buy_order);
      } else {
        sell_order.quantity -= buy_order.quantity;
      }
      if (buyer_orderbook.empty())
        break;
      buy_order = buyer_orderbook.top();
    }
    if(sell_order.quantity>0){
      seller_orderbook.push(sell_order);
    }
  }

};


#endif // PNSEI_STOCK_TRADING_H
