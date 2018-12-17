//
// Created by Henry Wu on 11/22/18.
//

#ifndef PNSEI_432_ALL_OONE_DATA_STRUCTURE_LFU_VARIANT_H
#define PNSEI_432_ALL_OONE_DATA_STRUCTURE_LFU_VARIANT_H

// https://leetcode.com/problems/all-oone-data-structure/
/*
 * Implement a data structure supporting the following operations:

Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1.
 Key is guaranteed to be a non-empty string.
Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1.
 If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".
Challenge: Perform all these in O(1) time complexity.
 * */
#include "henry.h"

namespace _432{

// LFU variant ==> ordered list of set + map (key->iterator of list)
struct node{
  int f;
  // 如果上面的set用unordered_set代替,getMaxKey就会出错,因为unordered_set不支持反向loop.
  // 还有set可以保留插入顺序by key,替换之后不行.
  unordered_set<string> nset;
  node(string& s,int f_):f(f_){nset.insert(s);}
};

class AllOne {
  list<node> flist;
  map<string, list<node>::iterator> m;
public:
  AllOne() {}

  void inc(string key) {
    if(m.count(key)){
      auto it=m[key];
      it->nset.erase(key);
      int f=it->f+1;
      auto nx=next(it);
      if(it->nset.empty()) flist.erase(it);
      if(nx==flist.end() || f!=nx->f){
        m[key]=flist.insert(nx, node(key, f)); //
      }else{
        nx->nset.insert(key);
        m[key]=nx;
      }
    }else{
      auto it=flist.begin();
      if(flist.empty() || it->f!=1){
        flist.push_front(node(key, 1));
        m[key] = flist.begin();
      }else
        it->nset.insert(key), m[key]=it;
    }
  }

  void dec(string key) {
    if(!m.count(key)) return;
    list<node>::iterator i=m[key];
    if(i->f==1){
      i->nset.erase(key);
      if(i->nset.empty())
        flist.erase(i);
      m.erase(key);
    }else{
      int f=i->f;
      if(i==flist.begin()){
        i->nset.erase(key);
        if(i->nset.empty())
          flist.erase(i);
        flist.push_front(node(key, f-1));
        m[key]=flist.begin();
      }else{
        auto j=prev(i);
        if(j->f == f-1){
          i->nset.erase(key);
          if(i->nset.empty())
            flist.erase(i);
          j->nset.insert(key), m[key]=j;
        }else{
          if(i->nset.size()==1){
            i->f--;
          }else{
            i->nset.erase(key);
            m[key]=flist.insert(i, node(key, f-1));
          }
        }
      }
    }
  }

  // Returns **one** of the keys with maximal value. If no element exists, return an empty string "".
  string getMaxKey() {
    if(flist.empty()) return "";
    return * flist.back().nset.begin();
  }

  //  Returns **one** of the keys with minimal value. If no element exists, return an empty string "".
  string getMinKey() {
    if(flist.empty()) return "";
    return *flist.front().nset.begin();
  }
};

void test(){
  //["AllOne","inc","getMaxKey","getMinKey"]
  //[[],["hello"],[],[]]
  AllOne a;
  a.inc("hello");
  assert(a.getMaxKey()=="hello");
  assert(a.getMinKey()=="hello");
}
/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne obj = new AllOne();
 * obj.inc(key);
 * obj.dec(key);
 * string param_3 = obj.getMaxKey();
 * string param_4 = obj.getMinKey();
 */
}

#endif //PNSEI_432_ALL_OONE_DATA_STRUCTURE_LFU_VARIANT_H
