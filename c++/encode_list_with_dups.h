#pragma once

#include "henry.h"

namespace bbg_encode_list_with_dups{

  // http://www.1point3acres.com/bbs/thread-247535-1-1.html
  
  string encode_list_with_dups(const string& s) {
    string r;
    char last = 0;
    int count = 0;
    for (char c : s) {
      if (c == last) {
        count++;
      } else if(count>0){
        r += (count>1?to_string(count):string("")) + last;
        last = c, count = 1;
      } else {
        last = c, count++; 
      }
    }
    if(count>0) r += (count>1 ? to_string(count) : string("")) + last;
    return r;
  }

  void test() {
    string s = "abbbc";
    assert(encode_list_with_dups(s)=="a3bc");
  }

}