#include <gtest/gtest.h>
#include "sql_split.h"

TEST(sql_split, basic){
  using namespace databricks::sql_split;
  Solution sln;
  assert(
      sln.split(
          "select \"hello\\\\ \\\";\" as c; select \"hello\\\\ \\\";\" as d")
          .size() == 2);
  assert(
      sln.split("select \"hello\\\";\";\nselect \"world;\\next;\" ;").size() ==
      2);
  assert(sln.split("select 1; select 2;").size() == 2);
  assert(sln.split("select \"hello\";\nselect \"world;next;\" ;").size() == 2);
}