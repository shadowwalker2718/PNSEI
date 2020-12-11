#include "order_book.h"
#include <gtest/gtest.h>

TEST(rh, order_book){
  OrderBook ob;
  ob.send({10, 10, true});
  ob.send({10, 10, false});
  EXPECT_TRUE(ob.buyer_orderbook.empty());
  EXPECT_TRUE(ob.seller_orderbook.empty());

  // long: 0 , short: 9@10
  ob.send({10, 1, true});
  ob.send({10, 10, false});
  EXPECT_TRUE(ob.buyer_orderbook.empty());
  EXPECT_TRUE(ob.seller_orderbook.top().quantity==9);

  // long: 0 , short: 9@10, 10@30
  ob.send({30, 10, false});
  // long: 0 , short: 29@10, 10@30
  ob.send({10, 10, false});
  ob.send({10, 10, false});
  // long: 30@10 , short: 29@10, 10@30
  ob.send({10, 30, true});
  // long: 1@10 , short: 10@30
  EXPECT_TRUE(ob.buyer_orderbook.top().quantity==1);
  EXPECT_TRUE(ob.seller_orderbook.top().price==30);

}