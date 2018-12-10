//
// Created by Henry Wu on 12/5/18.
//

#ifndef PNSEI_ONSITE1_H
#define PNSEI_ONSITE1_H

/* https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=460470&highlight=linkedin%2B%BE%AD
2018(10-12月) 码农类General 硕士 全职@Linkedin - 猎头 - Onsite  | Other | 在职跳槽
1. 给一个字符串S ,看是否能够包括一列目标子串[s1, s2, ..., sn]并且子串在S中位置不重合
2. 给一列数[n1, n2, ...]可能有元素重复,返回所有可能的排列
3. 设计一个文本数据库,对于query 高效的返回某个key在数据库中出现的所有位置, 出现次数是否大于k
4. behavior question: 你在项目中遇到过最难的问题是什么,跟经理意见不一致怎么办,等等
5.设计一个传感器网络,有大量的传感器实时发送数据,access point 向这些传感器发送query,如何快速得到结果
*/

#include "henry.h"

namespace linkedin_onsite1 {

/*1. 给一个字符串S ,看是否能够包括一列目标子串[s1, s2, ..., sn]并且子串在S中位置不重合*/
bool _dfs(vector<set<int>> vs, set<int> visited, int head) {
  if (head == vs.size())
    return true;
  for (int i: vs[head]) {
    if (!visited.count(i)) {
      visited.insert(i);
      if (_dfs(vs, visited, head + 1))
        return true;
    }
  }
  return false;
}

// 比如 S="abcdefgab"     s1="bc", s2="ab"
// it just requires NO duplicate starting points
bool contain_nondup_children(string s, vector<string> v) {
  int L = v.size();
  vector<set<int>> vs;
  int pos = 0;
  for (string e: v) {
    set<int> si;
    int start = 0;
    while ((pos = s.find(e, start)) != s.npos) {
      si.insert(pos);
      start = pos + 1;
    }
    if (si.empty()) return false;
    vs.push_back(si);
  }
  // DFS
  set<int> vd;
  return _dfs(vs, vd, 0);
}

// could be improved with interval tree!!!!
bool has_overlap(set<PII > intervals, int start, int size) {
  for (PII pr: intervals) {
    if (!(pr.second < start || pr.first > start + size - 1)) {
      return true;
    }
  }
  return false;
}

bool _dfs_nonoverlap(vector<set<int>> vs, set<PII > intervals, vector<string> v, int head) {
  if (head == vs.size())
    return true;
  for (int i: vs[head]) {
    if (!has_overlap(intervals, i, v[head].size())) {
      set<PII > t = intervals;
      t.emplace(i, i + v[head].size() - 1); // index + size => end of the inclusive index
      if (_dfs_nonoverlap(vs, t, v, head + 1))
        return true;
    }
  }
  return false;
}

bool contain_nonoverlap_children(string s, vector<string> v) {
  int L = v.size();
  int sumL = 0;
  for (string e : v)
    sumL += e.size();
  if (s.size() < sumL)
    return false;

  vector<set<int>> vs;
  int pos = 0;
  for (string e: v) {
    set<int> si;
    int start = 0;
    while ((pos = s.find(e, start)) != s.npos) {
      si.insert(pos);
      start = pos + 1;
    }
    if (si.empty()) return false;
    vs.push_back(si);
  }
  // DFS
  set<PII > intervals;
  return _dfs_nonoverlap(vs, intervals, v, 0);
}

void test1() {
  bool b = contain_nonoverlap_children("abcdefgab", {"ab", "bc"});
  assert(b);
  b = contain_nonoverlap_children("abc", {"ab", "bc"});
  assert(!b);
  b = contain_nonoverlap_children("abcdefgab", {"abc", "cde"});
  assert(!b);
  assert(!contain_nonoverlap_children("", {"ab", "bc"}));
  assert(!contain_nonoverlap_children("ab", {"ab", "bc"}));
  assert(!contain_nonoverlap_children("ab", {"a", "ab"}));
}

/* 3. 设计一个文本数据库,对于query 高效的返回某个key在数据库中出现的所有位置, 出现次数是否大于k */
// Array is an index based `database`
//
// index:    [0]     [1]   [2]
// contents: `bla`   `ba`  `ba`
// but inverted index is reversed: `bla`: [0], `ba`: [1,2]
//
// http://sys.quant365.com/system-design.html#inverted-index


}

#endif //PNSEI_ONSITE1_H
