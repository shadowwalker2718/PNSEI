#include <gtest/gtest.h>
#include "sql_comment.h"

TEST(sql_comment, basic){
using namespace databricks::comments;
  cout << remove_comment("SELECT 123") << endl;
  // SELECT "123\", \"hello" --world
  cout << remove_comment("SELECT \"123\\\", \\\"hello\" --world") << endl;
  // SELECT "123\\", "hello" --world
  cout << remove_comment("SELECT \"123\\\\\", \"hello\" --world") << endl;
  cout << remove_comment("SELECT * FROM users   --users table selected") << endl;
  cout << remove_comment("WHERE users.name=\"David\" --user name select") << endl;
  cout << remove_comment("WHERE users.name=\"--David\" --user name select") << endl;
}