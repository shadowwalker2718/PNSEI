#include <gtest/gtest.h>
#include "IndexMaxPQ.h"

TEST(IndexMaxPQ, basic){
  using namespace _indexheap;
  index_heap ih;
  vector<stock> data = {
      {"FB", 102},
      {"GOOG", 101},
      {"AMZ", 103},
      {"IBM", 100},
      {"UB", 105},
      {"LNKD", 104},
      {"BIDU", 106},
      {"BBG", 210},
      {"MSFT", 321},
      {"uber", 268},
      {"YHOO", 12},
      {"AAPL", 234},
      {"TWTR", 160},
      {"EBAY", 89}};
  for (auto &pr : data)
    ih.push(pr);
  auto r = ih.topK(5);
  for (const auto& s : r) {
    cout << s.ticker << "-" << s.volume << endl;
  }
  cout << "******************" << endl;
  ih.increase_volume("FB", 2500 - 102);
  r = ih.topK(3);
  for (auto s : r) {
    cout << s.ticker << "-" << s.volume << endl;
  }
  cout << "******************" << endl;
}