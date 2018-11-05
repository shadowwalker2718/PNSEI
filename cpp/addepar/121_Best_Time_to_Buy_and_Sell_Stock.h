//
// Created by root on 11/4/18.
//

#ifndef PNSEI_121_BEST_TIME_TO_BUY_AND_SELL_STOCK_H
#define PNSEI_121_BEST_TIME_TO_BUY_AND_SELL_STOCK_H

#include "henry.h"

namespace _121{

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
class Solution { // forward looking algo
public:
    int maxProfit(vector<int>& prices) {
        int r=0, mi=INT_MAX;
        for(int i: prices)
            mi=min(i,mi), r=max(i-mi, r);
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
    if (L<=1) return 0;
    vector<int> v;
    int r=0, mi=INT_MAX, mx=INT_MIN;
    for(int i: prices)
      mi=min(i,mi), r=max(i-mi, r), v.push_back(r);

    r=0;
    for(int i=prices.size()-1;i>=0;i--){
      mx=max(prices[i],mx), r=max(mx-prices[i],r), v[i]+=r;
    }
    return *max_element(v.begin(), v.end());
  }
};

}

#endif //PNSEI_121_BEST_TIME_TO_BUY_AND_SELL_STOCK_H
