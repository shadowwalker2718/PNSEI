//
// Created by henry.wu on 10/1/20.
//
#include <gtest/gtest.h>
#include "meta1.h"

TEST(meta1, a){
  using namespace meta;
  print_types<All>{}();
}
