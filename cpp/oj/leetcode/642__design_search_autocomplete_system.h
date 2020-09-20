#ifndef PNSEI_642__DESIGN_SEARCH_AUTOCOMPLETE_SYSTEM_H
#define PNSEI_642__DESIGN_SEARCH_AUTOCOMPLETE_SYSTEM_H

#include "henry.h"

namespace _642{
class AutocompleteSystem {
  unordered_map<string, int> m1; // s->freq
  unordered_map<string, unordered_set<string>> m2;
  string s;
public:
  AutocompleteSystem(vector<string> ss, vector<int> ts) {
    for(int i=0;i<ss.size();++i){
      string t=ss[i];
      m1[t]=ts[i];
      for(int i=0;i<t.size();++i)
        m2[t.substr(0,i+1)].insert(t);
    }
  }
  vector<string> input(char c) {
    if(c=='#'){
      m1[s]++;
      for(int i=0;i<s.size();++i)
        m2[s.substr(0,i+1)].insert(s);
      s="";
      return {};
    }
    s+=c;
    if(!m2.count(s)) return {};
    vector<string> v;//str, freq
    for(string e :m2[s])
      v.emplace_back(e);
    auto f=[&](string& s1, string& s2){
      return m1[s1] > m1[s2] || (m1[s1] == m1[s2] && s1<s2);};
    if(v.size()<3){
      sort(v.begin(), v.end(), f);
      return v;
    }
    nth_element(v.begin(), v.begin()+2, v.end(), f);
    sort(v.begin(),v.begin()+3,f);
    return vector<string>(v.begin(), v.begin()+3);
  }
};

}

namespace _642_2 {
class AutocompleteSystem { // 229 ms
  unordered_map<string, int> dict;
  string data;
public:
  AutocompleteSystem(vector<string> sentences, vector<int> times) {
    for (int i = 0; i < times.size(); i++)
      dict[sentences[i]] += times[i];
    data.clear();
  }
  vector<string> input(char c) {
    if (c == '#') {
      dict[data]++, data.clear();
      return {};
    }
    data.push_back(c);
    auto cmp = [](const pair<string, int> &a, const pair<string, int> &b) {
      return a.second > b.second || a.second == b.second && a.first < b.first;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
    for (auto &p : dict) { // O(N): N - length of historical records
      bool match = true;
      for (int i = 0; i < data.size(); i++) // O(M) M - Average length of records
        if (data[i] != p.first[i]) { match = false; break; }
      if (match) {
        pq.push(p); // O(Log3)
        if (pq.size() > 3) pq.pop(); // O(Log3)
      }
    }
    vector<string> res(pq.size());
    for (int i = pq.size() - 1; i >= 0; i--)
      res[i] = pq.top().first, pq.pop();
    return res;
  }
};
}

namespace _642_3 {
struct AutocompleteSystem { // 193ms
  AutocompleteSystem(const vector<string>& sentences, const vector<int>& times) {
    for (int i = 0, n = sentences.size(); i < n; ++i)
      m.emplace(sentences[i], times[i]);
  }
  vector<string> input(char c) { // O(LogN + M*LogM)
    if (c == '#') {
      ++m[data], data.clear();
      return vector<string>();
    }
    data.push_back(c);
    auto b = m.lower_bound(data), e = m.upper_bound(data + "~"); // O(LogN)
    map<int, set<string>, greater<int>> m2;
    for (; b != e; ++b) // O(M)
      m2[b->second].insert(b->first); // O(LogM)
    vector<string> r;
    for (auto& pr : m2)
      for (auto& s : pr.second) {
        r.push_back(s);
        if (r.size() >= 3) return r;
      }
    return r;
  }
  string data;
  map<string, int> m;
};
}

#endif // PNSEI_642__DESIGN_SEARCH_AUTOCOMPLETE_SYSTEM_H
