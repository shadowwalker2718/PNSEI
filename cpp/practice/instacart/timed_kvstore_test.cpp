#include <gtest/gtest.h>
#include "timed_kvstore.h"
#include "timed_kvstore_v2.h"

using namespace instacart;

TEST(timed_kvstore, basic){
  timed_kv_store kv;
  EXPECT_TRUE(kv.get("hello").empty());

  long t1 = time(0);
  kv.set("henry", "woo1");
  sleep(1);
  kv.set("henry", "woo2");
  sleep(1);
  long t2 = time(0);
  sleep(1);
  kv.set("henry", "woo3");

  cout << kv.get("henry") << endl;
  cout << kv.get("henry", t2) << endl;
  cout << kv.get_fuzzy("henry", t2) << endl;
}

TEST(timed_kvstore_v2, basic){
  timed_kv_store_v2 kv;
  EXPECT_TRUE(kv.get("hello").empty());

  long t1 = time(0);
  kv.set("henry", "woo1");
  sleep(1);
  kv.set("henry", "woo2");
  sleep(1);
  long t2 = time(0);
  sleep(1);
  kv.set("henry", "woo3");

  cout << kv.get("henry") << endl;
  cout << kv.get("henry", t2) << endl;
  cout << kv.get_fuzzy("henry", t2) << endl;
}