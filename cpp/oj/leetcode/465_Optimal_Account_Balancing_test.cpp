#include "465_Optimal_Account_Balancing.h"
#include <gtest/gtest.h>

TEST(_465_Optimal_Account_Balancing, a){
  using namespace _465_account_balancing;

  Solution_Recursive sln;
  vector<vector<int>> vi = {{0, 1, 10},
                            {1, 0, 1},
                            {1, 2, 5},
                            {2, 0, 5}};
  assert(sln.minTransfers(vi) == 1);

  vi = {{1, 8, 1},
        {1, 13, 21},
        {2, 8, 10},
        {3, 9, 20},
        {4, 10, 61},
        {5, 11, 61},
        {6, 12, 59},
        {7, 13, 60}};
  Solution_Ksum sln2;
  assert(sln2.minTransfers(vi) == 8);

  vi={{2,0,5},{3,4,4}};
  assert(sln2.minTransfers(vi) == 2);
}