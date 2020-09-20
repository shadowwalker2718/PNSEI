//
// Created by Henry Wu on 11/4/18.
//

#ifndef PNSEI_121_BEST_TIME_TO_BUY_AND_SELL_STOCK_H
#define PNSEI_121_BEST_TIME_TO_BUY_AND_SELL_STOCK_H

#include "henry.h"

namespace _121{

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
class Solution { // forward looking algo
  /*
Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
   * */
public:
    int maxProfit(vector<int>& prices) {
        int r=0, mi=INT_MAX;
        for(int c: prices)
            mi=min(c,mi), r=max(c-mi, r);
        return r;
    }
};

class Solution2 { // backward looking algo
public:
  int maxProfit(vector<int>& prices) {
    int r=0, mx=INT_MIN;
    for(int i=prices.size()-1;i>=0;i--){
      mx=max(prices[i],mx), r=max(mx-prices[i],r);
    }
    return r;
  }
};

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
class Solution3 { // two transactions
public:
  int maxProfit(vector<int> &prices) {// O(N)
    const int L = prices.size();
    if (L<=1)
      return 0;
    vector<int> v;
    int r=0, mi=INT_MAX, mx=INT_MIN;
    for(int c: prices)
      mi=min(c,mi), r=max(c-mi, r), v.push_back(r);

    r=0;
    for(int i=prices.size()-1;i>=0;i--){
      mx=max(prices[i],mx), r=max(mx-prices[i],r), v[i]+=r;
    }
    return *max_element(v.begin(), v.end());
  }
};

}

#endif //PNSEI_121_BEST_TIME_TO_BUY_AND_SELL_STOCK_H
