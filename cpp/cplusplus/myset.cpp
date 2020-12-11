#include "pnsei.h"
#include <gtest/gtest.h>

namespace cplusplus{

struct abc{
  int i;
  explicit abc(int i_):i(i_){}
};

// https://stackoverflow.com/questions/31562548/set-of-pointers-with-custom-comparator
struct comp{
  bool operator()(const shared_ptr<abc>& a, const shared_ptr<abc>& b) const{
    return a->i < b->i;
  }
};


TEST(myset, abc){
  set<shared_ptr<abc>, comp> s;
  int k=3, cap=k;
  while(k--){
    s.insert(make_shared<abc>(k));
  }
  vector<int> result;
  result.reserve(s.size());
for(const auto& it : s)
    result.push_back(it->i);
  vector<int> expected(cap);
  iota(expected.begin(), expected.end(), 0);
  EXPECT_EQ(expected, result);
}

}

