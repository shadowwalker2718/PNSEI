#pragma once

#include "henry.h"

namespace _kangaroos {
  
  bool istarget(const string& s) {
    //return s == string(s.size() / 2, '<') + "_" + string(s.size() / 2, '>');
    int L = s.size();
    if (s[L / 2] != '_') return false;
    for (int i = 0; i < L / 2; ++i) if (s[i] != '<') return false;
    for (int i = L / 2 + 1; i < L; ++i) if (s[i] != '>') return false;
    return true;
  }

  bool alive(const string& s, int i) {
    bool r;
    if (i > s.size() / 2)
      r = (i - 2 >= 0 && s[i - 2] == '>') || 
      (i - 1 >= 0 && s[i - 1] == '>');
    else if (i < s.size() / 2)
      r = (i + 1 < s.size() && s[i + 1] == '<') || 
      (i + 2 < s.size() && s[i + 2] == '<');
    else return true;
    //if (!r) cout << s << endl;
    return r;
  }

  bool dfs(vector<string>& r, const string& s, int i) {
    if (istarget(s)) {
      r.push_back(s);
      return true;
    }
    for (int j = i-2; j>=0 && j < i; ++j) {
      if (j>=0 && s[j] == '>') {
        string t = s;
        swap(t[i], t[j]);
        if (alive(t,j) && dfs(r, t, j)) {
          r.push_back(s);
          return true;
        }
      }
    }
    for (int j = i+2; j > i; --j) {
      if (j<s.size() && s[j] == '<') {
        string t = s;
        swap(t[i], t[j]);
        if (alive(t, j) && dfs(r, t, j)) {
          r.push_back(s);
          return true;
        }
      }
    }
    return false;
  }

  // ">_<" ==> "<_>"
  map<string, string> mm;
  void path(string& s) {
    int L = s.size();
    vector<string> r;
    if (dfs(r, s, L / 2)) {
      /*cout << "found path after " << r.size() << " steps moving." << endl;
      reverse(r.begin(), r.end());
      string f;
      for (auto e : r) {
        if (!f.empty()) {
          int i = 0, j = 5;
          i = f.find('_');
          if (i == 0) { j = 3; } else if (i == 1) {j = 4; }
          else if (i == L - 1) { j = 3; }
          else if (i == L - 2) { j = 4; }
          i = max(i-2,0);
          string k = f.substr(i, j);
          if (mm.count(k)){
            if (mm[k] != e.substr(i, j))
              cout << "OLD:" << k << " : " << mm[k] <<"\tNEW:" << e.substr(i, j)<<endl;
          } else
            mm[k] = e.substr(i, j);
          f = e;
        } else {
          f = e;
        }
      }*/
      /*if (L/2%2==1) {
        for (auto& row : r)
          reverse(row.begin(), row.end());
      }*/
    }

    /*for (auto pr : mm) {
      printf("{\"%s\" , \"%s\"},\n",pr.first.c_str(), pr.second.c_str());
    }*/
  }

  void test() {
    time_t s0 = time(0);
    int count = 300;
    while (count--) {
      for (int i = 3; i < 10; ++i) {
        string s = string(i, '>') + "_" + string(i, '<');
        path(s);
      }
    }
    cout << time(0) - s0 << endl; s0 = time(0);
  }

#include <math.h>

  void test2() {
    map<string, string> mp = {
      { "<<_<>" , "<<<_>" },
      { "<<_><" , "<<<>_" },
      { "<>_<<" , "<><_<" },
      { "<>_><" , "<><>_" },
      { "<>_>>" , "<_>>>" },
      { "><_<<" , "_<><<" },
      { "><_<>" , "_<><>" },
      { "><_>>" , "_<>>>" },
      { ">>_<<" , ">_><<" },
      { ">>_<>" , ">_><>" },
      { ">>_><" , ">><>_" },
      { ">_><" , "><>_" },
      { ">_<>" , "_><>" },
      { "<_><" , "<<>_" },
      { "<>_<" , "<><_" },
      { "<>_>" , "<_>>" },
      { "><_<" , "_<><" },
      { "<_<>" , "<<_>" },
      { "><_>" , "_<>>" },
      { "_><" , "<>_" },
      { "_<>" , "<_>" },
      { "<>_" , "<_>" },
      { "><_" , "_<>" }
    };

    map<char, int> u = { { '>',1 },{ '_',2 },{ '<',3 } };
    unordered_map<long long, pair<long long, int>> m;
    for (auto pr : mp) {
      int i = 0, j = 0;
      int i0, i1;
      for (char c : pr.first) i = i * 10 + u[c];
      i0 = pr.first.find('_');
      for (char c : pr.second) j = j * 10 + u[c];
      i1 = pr.second.find('_');
      m[i] = { j , i0>i1 ? pow(10,i0 - i1) : -pow(10,i1 - i0) };
    }
    for (auto pr : m) {
      cout << pr.first << "->" << pr.second.first << "," << pr.second.second << endl;
    }

    auto fp = [](long long i, long long j) {
      if (j >= 100)
        return i / (j / 100) % 100000;
      else
        return i % (j * 1000);
    };
    auto cv = [](long long i, long long j, long long g) {
      if (j >= 1000)
        return (i / (j * 1000) * 100000 + g) * (j / 100) + i % (j / 100);
      else
        return i / (j * 1000) *j * 1000 + g;
    };
    auto target = [](long long i) {
      long long t = i, r = 0;
      while (t--) r = 10 * r + 3;
      t = i, r = 10 * r + 2;
      while (t--) r = 10 * r + 1;
      return r;
    };

    
    time_t s0 = time(0);
    int count = 300;
    while (count--) {
      int kangroo = 3;
      while (kangroo < 10) {
        string s = string(kangroo, '>') + "_" + string(kangroo, '<');
        long long k = 0;
        for (char c : s) k = k * 10 + u[c];
        //cout << k << endl;
        long long j = pow(10, kangroo); // pow(10,3)
        long long T = target(kangroo);
        while (k != T) {
          int t = fp(k, j);
          if (m.count(t)) {
            long long v = m[t].first;
            //cout << k << ",";
            k = cv(k, j, v);
            //cout << k << endl;
            j = m[t].second>0 ? j*m[t].second : j / -m[t].second;
          } else {
            cout << "no path" << endl;
          }
        }
        //cout << "found path" << endl;
        kangroo++;
      }
    }
    cout << time(0) - s0 << endl;

    test2();
  }



}








