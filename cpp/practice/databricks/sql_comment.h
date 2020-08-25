#ifndef PNSEI_SQL_COMMENT_H
#define PNSEI_SQL_COMMENT_H

#include "henry.h"

namespace databricks::comments {

string remove_comment(const string &sql_statement) {
  string r;
  bool in_string = false;
  for (int i = 0; i < sql_statement.size(); i++) {
    if (sql_statement[i] == '"' and i > 1 and sql_statement[i - 1] != '\\') {
      in_string = !in_string;
    }
    if (!in_string and sql_statement[i] == '-' and
        (i + 1) < sql_statement.size() and sql_statement[i + 1] == '-') {
      while (!r.empty() && r.back() == 0x20) // whitespace
        r.pop_back();
      return r;
    }
    r += sql_statement[i];
  }
  return r;
}

} // namespace databricks::comments

#endif // PNSEI_SQL_COMMENT_H
