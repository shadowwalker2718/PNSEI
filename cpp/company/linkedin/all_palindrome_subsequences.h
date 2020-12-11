#pragma once

#include "pnsei.h"

namespace _allLPS {

/*发信人: jumpharder (我爱跳水), 信区: JobHunting
标  题: LinkedIn onsite一道题
发信站: BBS 未名空间站 (Tue Sep 15 13:54:34 2015, 美东)

给一个string, 可以删除任意字符,求所有可以得到的palidrome字串集

我就想了个递归, 还是没有区分掉一些重复的情况,worst case O(2^n)基本同暴力解
Map<Integer, Set<String>> allSubSet = new HashMap();
Set<String> getAllPalidrome(String s, int x, int y){
int ind = x * s.length() + y;
if(allSubSet.constainsKey(ind)) return allSubSet.get(ind);
Set<String> ret = new HashSet();
if (s == null || s.size() == 0) { ret.add(""); return ret;}
if (s.size() == 1) { ret.add(s); return ret;}
for(int i = x; i <= y; i++){
  for (int j = y; j >= i; j--){
    if (s.charAt(i) == s.charAt(j)){
       Set<String> subSet = getAllPalidrome(s, i + 1, j - 1);
       ret.addAll(subSet);
       for (String str : subSet) ret.add(s.charAt(i) + str + s.charAt(i));
    }
  }
}
allSubSet.put(ind, ret);
return ret;
}*/

// Not remove the duplicates
vector<string> get_all_palindrome_subsequences(const string &s) {
  int i = 0, j = 0, L = s.size();
  vector<pair<int, int>> u1;
  for (int i = 0; i < L; ++i) {
    for (int j = i + 1; j < L; ++j) {
      if (s[i] == s[j]) {
        u1.emplace_back(i, j);
      }
    }
  }

  unordered_map<int, vector<vector<pair<int, int>>>> uk;
  for (i = 0; i < u1.size(); ++i) {
    for (j = 0; j < u1.size(); ++j) {
      if (i == j)
        continue;
      if (u1[i].first < u1[j].first && u1[j].second < u1[i].second) {
        uk[2].push_back({u1[i], u1[j]} /*a vector*/);
      }
    }
  }

  for (int k = 3; k <= L / 2; ++k) {
    if (uk.count(k - 1) == 0)
      break;
    auto tmp = uk[k - 1];
    for (auto &e : tmp) {
      for (int i = 0; i < u1.size(); i++) {
        if (e.back().first < u1[i].first && u1[i].second < e.back().second) {
          auto ne = e;
          ne.push_back(u1[i]);
          uk[k].push_back(ne);
        }
      }
    }
  }

  vector<string> r;
  for (auto &pr : u1) {
    string tmp(2, s[pr.first]);
    r.push_back(tmp);
  }
  for (auto &t : uk) {
    for (auto &vpr : t.second) {
      string tmpstr;
      for (auto &pr : vpr)
        tmpstr += s[pr.first];
      string sbar(tmpstr);
      reverse(sbar.begin(), sbar.end());
      string ssbar = tmpstr + sbar;
      r.push_back(ssbar);
    }
  }
  return r;
}

// Function return the total palindromic subsequence
// http://sde.quant365.com/palindrome.html#number-of-all-palindromic-subsequence
int countPS(const string &str) {
  int N = str.length();
  // create a 2D array to store the count of palindromic
  // subsequence
  vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));
  for (int L = 2; L <= N; L++) {
    cout << "L=" << L << endl;
    cout << "\n";
    for (int i = 0; i < N; i++) {
      int j = L + i - 1;
      if (j > N)
        continue;
      cout << i << "-" << j << ", ";
      if (str[i] == str[j])
        dp[i][j] = dp[i][j - 1] + dp[i + 1][j] + 1;
      else
        dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1];
    }
  }
  return dp[0][N - 1];
}

int countPs(string s) {
  int r = 0;
  return r;
}

void test() {
  string s("ACGATGTAC");
  assert(countPS(s) == get_all_palindrome_subsequences(s).size());

  s = "aaaaaaaa";
  assert(countPS(s) == get_all_palindrome_subsequences(s).size());
}

} // namespace _allLPS
