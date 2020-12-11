#ifndef PNSEI_SQL_SPLIT_H
#define PNSEI_SQL_SPLIT_H

#include "pnsei.h"
// https://www.1point3acres.com/bbs/thread-295955-1-1.html

namespace databricks::sql_split {

struct Solution {
  static vector<string> split(const string&sql_statements) {
    vector<string> vs;
    bool in_string = false;
    string one_statment;
    for (int i = 0; i < sql_statements.size(); i++) {
      if (sql_statements[i] == '"' and i > 1 and
          sql_statements[i - 1] != '\\') {
        in_string = !in_string;
      }
      one_statment += sql_statements[i];
      if (!in_string and sql_statements[i] == ';') {
        vs.push_back(one_statment);
        one_statment.clear();
      }
    }
    if (!one_statment.empty())
      vs.push_back(one_statment);
    return vs;
  }
};

} // namespace databricks::sql_split

#endif // PNSEI_SQL_SPLIT_H
