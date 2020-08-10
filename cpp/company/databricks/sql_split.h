#ifndef PNSEI_SQL_SPLIT_H
#define PNSEI_SQL_SPLIT_H

#include "henry.h"
// https://www.1point3acres.com/bbs/thread-295955-1-1.html

namespace databricks {

namespace sql_split {

  struct Solution {
    vector<string> split(string s) {
      vector<string> vs;
      bool b=false;
      string q;
      for (int i=0;i<s.size();i++) {
        if (s[i]=='"' and i>1 and s[i-1]!='\\'){
          b=!b;
        }
        q+=s[i];
        if (!b and s[i]==';'){
          vs.push_back(q), q.clear();
        }
      }
      if (!q.empty())
        vs.push_back(q);
      return vs;
    }
  };

  void test() {
    Solution sln;
    assert(
        sln.split("select \"hello\\\\ \\\";\" as c; select \"hello\\\\ \\\";\" as d").size() == 2);
    assert(
        sln.split("select \"hello\\\";\";\nselect \"world;\\next;\" ;").size() ==
        2);
    assert(sln.split("select 1; select 2;").size() == 2);
    assert(sln.split("select \"hello\";\nselect \"world;next;\" ;").size() ==
           2);
  }
}
}



#endif // PNSEI_SQL_SPLIT_H
