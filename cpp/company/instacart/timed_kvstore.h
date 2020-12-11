#ifndef PNSEI_TIMED_KVSTORE_H
#define PNSEI_TIMED_KVSTORE_H

#include "pnsei.h"

/*
2020(4-6月) 码农类General 硕士 全职@instacart - 猎头 - 技术电面  | Other | 在职跳槽
地里之前分享过：实现有时间戳功能的KV存储
第一题是最简单的KV实现，可以用builtin函数
第二题实现时间戳match的get函数，要O(1)复杂度
第三题实现时间戳fuzzy match的get，找最近的历史时间戳对应的值

面试定在早上十点 两边都困得不行 面试官直打瞌睡TT
*/
namespace instacart{
struct timed_kv_store{
  unordered_map<string, map<long, string>> m;

  void set(const string& k, const string& v){
    long t = time(0);
    m[k][t] = v;
  }

  // O(1)
  // https://en.cppreference.com/w/cpp/container/map/end
  string get(const string& k){
    if (m.count(k) && !m[k].empty()){ ///
      return (--m[k].end())->second;
    }
    return "";
  }

  // O(LogN)
  string get(const string& k, long ts){
    if (m.count(k) && m[k].count(ts))
      return m[k][ts];
    return "";
  }

  string get_fuzzy(const string& k, long ts){
    if (!m.count(k))
      return "";
    auto tree = m[k];
    if (tree.count(ts))
      return tree[ts];
    auto lb = tree.lower_bound(ts);
    if (lb!=tree.begin()){
      return (--lb)->second;
    } else {
      return "";
    }
  }

};
}

#endif // PNSEI_TIMED_KVSTORE_H
