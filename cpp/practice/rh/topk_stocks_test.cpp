#include "topk_stocks.h"
#include "gtest/gtest.h"

TEST(rh, pick_of_the_week) {
  vector<string> picks = {"123,AAPL", "456629,GOOG", "456629,AAPL","24231, TWLO"};
  auto r = rh::pick_of_the_week(picks);
  for (auto &s : r) {
    cout << s << endl;
  }
}

TEST(rh, pick_of_the_week_topk) {
  vector<string> picks = {"123,AAPL", "456629,GOOG", "456629,AAPL","24231, TWLO", "456629,MSFT"};
  auto r = rh::pick_of_the_week_topk(picks, 2);
  for (auto &s : r) {
    cout << s << endl;
  }
}