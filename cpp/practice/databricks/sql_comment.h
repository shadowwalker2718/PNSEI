#ifndef PNSEI_SQL_COMMENT_H
#define PNSEI_SQL_COMMENT_H

namespace databricks::comments {
string remove_comment(const string& s){
  string r;
  bool in_string = false;
  for(int i=0;i<s.size();i++){
    if (s[i]=='"' and i > 1 and s[i-1]!='\\'){
      in_string = !in_string;
    }
    if (!in_string and s[i]=='-' and (i+1)<s.size() and s[i+1]=='-'){
      while (!r.empty() && r.back()==0x20)
        r.pop_back();
      return r;
    }
    r+=s[i];
  }
}
void test(){
  cout << remove_comment("SELECT * FROM users   --users table selected") << endl;
  cout << remove_comment("WHERE users.name=\"David\" --user name select") << endl;
  cout << remove_comment("WHERE users.name=\"--David\" --user name select") << endl;
}
}


#endif // PNSEI_SQL_COMMENT_H
