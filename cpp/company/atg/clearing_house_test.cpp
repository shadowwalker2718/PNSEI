#include <gtest/gtest.h>
#include "clearing_house.h"

TEST(ch, a){
  using namespace atg;
  financial_clearing_house();
}

TEST(ch, b){
  using namespace atg;
  financial_clearing_house_v2();
}