#include <gtest/gtest.h>
#include "721__accounts_merge.h"

TEST(_721__accounts_merge, basic){
  VVS accounts = {{"John", "johnsmith@mail.com", "john00@mail.com"},
                   {"John", "johnnybravo@mail.com"},
                   {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
                   {"Mary", "mary@mail.com"}};
  _721::Solution sln;
  auto r =sln.accountsMerge(accounts);
  EXPECT_EQ(r.size(), 3);
}

TEST(_721__accounts_merge, basic2){
  VVS accounts = {{"David","David0@m.co","David4@m.co","David3@m.co"},
                  {"David","David5@m.co","David5@m.co","David0@m.co"},
                  {"David","David1@m.co","David4@m.co","David0@m.co"},
                  {"David","David0@m.co","David1@m.co","David3@m.co"},
                  {"David","David4@m.co","David1@m.co","David3@m.co"}};
  _721::Solution sln;
  auto r =sln.accountsMerge(accounts);
  EXPECT_EQ(r.size(), 1);
}

TEST(_721__accounts_merge, union_find_merge){
  VVS accounts = {{"David","David0@m.co","David1@m.co"},
                  {"David","David3@m.co","David4@m.co"},
                  {"David","David4@m.co","David5@m.co"},
                  {"David","David2@m.co","David3@m.co"},
                  {"David","David1@m.co","David2@m.co"}};
  _721::Solution sln;
  auto r =sln.accountsMerge(accounts);
  EXPECT_EQ(r.size(), 1);
}

