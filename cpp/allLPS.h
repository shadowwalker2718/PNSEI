#pragma once

#include "henry.h"

namespace _allLPS {

// Not remove the duplicates
vector<string> allLPS(const string &s) {
  int i = 0, j = 0, L = s.size();
  vector<pair<int, int>> u1;
  for (int i = 0; i < L; ++i) {
    for (int j = i + 1; j < L; ++j) {
      if (s[i] == s[j]) {
        u1.emplace_back(i, j);
      }
    }
  }

  map<int, vector<vector<pair<int, int>>>> uk;
  for (i = 0; i < u1.size(); ++i) {
    for (j = 0; j < u1.size(); ++j) {
      if (i == j)
        continue;
      if (u1[i].first < u1[j].first && u1[j].second < u1[i].second)
        uk[2].push_back({u1[i], u1[j]});
    }
  }

  for (int k = 3; k <= L / 2; ++k) {
    if (uk.count(k - 1) == 0)
      break;
    auto tmp = uk[k - 1];
    for (auto e : tmp) {
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
  for (auto pr : u1) {
    string tmp(2, s[pr.first]);
    r.push_back(tmp);
  }
  for (auto t : uk) {
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
int countPS(string str) {
  int N = str.length();

  // create a 2D array to store the count of palindromic
  // subsequence
  // int cps[N + 1][N + 1];
  // memset(cps, 0, sizeof(cps));
  vector<vector<int>> cps(N + 1, vector<int>(N + 1, 0));
  // palindromic subsequence of length 1
  // for (int i = 0; i<N; i++)
  //  cps[i][i] = 1;

  // check subsequence of length L is palindrome or not
  for (int L = 2; L <= N; L++) {
    cout << "L=" << L << endl;
    cout << "\n";
    for (int i = 0; i < N; i++) {
      int j = L + i - 1;
      if (j > N)
        continue;
      cout << i << "-" << j << ",";
      if (str[i] == str[j])
        cps[i][j] = cps[i][j - 1] + cps[i + 1][j] + 1;
      else
        cps[i][j] = cps[i][j - 1] + cps[i + 1][j] - cps[i + 1][j - 1];
    }
  }

  // return total palindromic subsequence
  return cps[0][N - 1];
}

int countPs(string s) {
  int r = 0;
  return r;
}

void test() {
  string s("ACGATGTAC");
  assert(countPS(s) == allLPS(s).size());
}

} // namespace _allLPS
