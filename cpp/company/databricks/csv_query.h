#ifndef PNSEI_CSV_QUERY_H
#define PNSEI_CSV_QUERY_H

#include "henry.h"

// http://hbasefly.com/2017/03/19/sparksql-basic-join/
// https://cloud.tencent.com/developer/article/1180112
// https://blog.csdn.net/fz2543122681/article/details/76861713
// https://blog.csdn.net/weixin_33836223/article/details/86205172?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param

// Class - Camel, namespace - lower, function - lower snake, typename - Upper
namespace databricks::csv_query {

static const char* const DEL_SQL=" ";
static const char* const DEL_CSV=",";
static const char* const MISSING="-";
static const char* const INPUT_FOLDER = "/home/henry.wu/src/PNSEI/cpp/company/databricks/";

vector<string> split(string s, const string &del);

// In Java using LinkedHashMap would be easier!
class CSV {
  vector<string> columns;
  unordered_map<string, vector<string>> column_to_data;
  int take = INT_MAX;

public:
  CSV(){
    clear();
  }
  void clear() {
    columns.clear();
    column_to_data.clear();
    take = INT_MAX;
  }
  size_t col_size() const { return columns.size(); }
  size_t row_size() const {
    if (column_to_data.empty())
      return 0;
    return column_to_data.begin()->second.size();
  }
  void add_column(const string &c) { columns.push_back(c); }
  void set_take(int take_) { take = take_; }

  void set_columns(const vector<string> &c) { columns = c; }
  void set_rows(const unordered_map<string, vector<string>> &d) { column_to_data = d; }

public:
  void load_file_csv(const string& file_path) {
    clear();
    ifstream inputFile(INPUT_FOLDER + file_path);
    string line;
    if (inputFile.is_open() && !inputFile.eof()) {
      getline(inputFile, line);
      set_columns(split(line, DEL_CSV));
    }
    int row = 0;
    while (inputFile.is_open() && !inputFile.eof()) {
      getline(inputFile, line);
      const VS cols = split(line, DEL_CSV);
      for (int i = 0; i < col_size(); ++i) {
        if (i < cols.size()) {
          column_to_data[columns[i]].push_back(cols[i]);
        } else {
          column_to_data[columns[i]].push_back(MISSING);
        }
      }
      row++;
    }
    if (row<=1)
      throw invalid_argument("csv file path is wrong. no data in file.");
  }

  void show() {
    for (int i = 0; i < col_size(); ++i) {
      cout << columns[i];
      if (i != int(columns.size()) - 1)
        cout << ",";
    }
    cout << endl;
    for (int j = 0; j < row_size(); ++j) {
      if (j >= take)
        break;
      for (int k = 0; k < columns.size(); ++k) {
        cout << column_to_data[columns[k]][j];
        if (k != columns.size() - 1)
          cout << ",";
      }
      cout << endl;
    }
  }
  // T: O(C)
  void select(const vector<string> &cols) {
    unordered_map<string, vector<string>> tmp;
    for (const auto & col : cols) {
      tmp[col] = column_to_data[col];
    }
    columns = cols;
    column_to_data = tmp;
  }

  // Time: O(R*C)
  void order_by(const string& col) {
    vector<string> rows = column_to_data[col];
    vector<int> v;
    // O(R)
    for_each(rows.begin(), rows.end(),
             [&v](const string &s) { v.push_back(stoi(s)); });
    vector<pair<int, string>> o;
    // O(R)
    for (int i = 0; i < rows.size(); ++i) {
      o.emplace_back(v[i], get_row(i));
    }
    const auto greater_comp = greater<pair<int, string>>();
    sort(o.begin(), o.end(), greater_comp);
    unordered_map<string, vector<string>> new_data;
    // O(R * C)
    for (auto & j : o) {
      auto c = split(j.second, DEL_CSV);
      for (int i = 0; i < c.size(); ++i) {
        new_data[columns[i]].push_back(c[i]);
      }
    }
    set_rows(new_data);
  }

  // Hash Join
  // This is `Inner Join` implementation. Left join will be a little different.
  // O(R2+R1*(C1+C2))
  void join(CSV &new_csv, const string& column) {
    VS cols = new_csv.columns;
    cols.erase(std::remove(cols.begin(), cols.end(), column), cols.end());
    cols.insert(cols.begin(), columns.begin(), columns.end());

    unordered_map<string, vector<string>> new_data;
    vector<string> &old_rows = column_to_data[column];
    vector<string> &new_rows = new_csv.column_to_data[column];

    unordered_map<string, int> val_to_idx;
    // O(R2)
    for (int i = 0; i < new_csv.row_size(); ++i) {
      // stop when the first match is found, actually it can have >=1 matches
      if (val_to_idx.count(new_csv.column_to_data[column][i])==0)
        val_to_idx[new_csv.column_to_data[column][i]] = i;
    }
    // O(R1)
    for (int i = 0; i < row_size(); ++i) {
      string s = old_rows[i];
      if (val_to_idx.count(s)==0)
        continue;
      int idx = val_to_idx[s];
      // O(C1+C2)
      for (int j = 0; j < col_size(); ++j) {
        const string col_name = columns[j];
        const string v = column_to_data[col_name][i];
        new_data[col_name].push_back(v);
      }
      for (int j = 0; j < new_csv.col_size(); ++j) {
        const string col_name = new_csv.columns[j];
        if (col_name == column)
          continue;
        const string v = new_csv.column_to_data[col_name].at(idx);
        new_data[col_name].push_back(v);
      }
    }
    columns = cols;
    column_to_data = new_data;
  }

  void sort_merge_join(CSV &new_csv, const string& column) {
    //todo
  }

  void count_by(const string& column) {
    select({column});
    if (columns.back() != "count")
      columns.emplace_back("count");
    unordered_map<string, int> counter;
    for (auto & i : column_to_data[column]) {
      counter[i]++;
    }
    column_to_data[column].clear();
    for (const auto& pr : counter) {
      column_to_data[column].push_back(pr.first);
      column_to_data["count"].push_back(to_string(pr.second));
    }
  }

private:
  string get_row(int idx) {
    string s;
    for (int j = 0; j < columns.size(); ++j) {
      s += column_to_data[columns[j]][idx];
      if (j != columns.size() - 1)
        s += ",";
    }
    return s;
  }
};

template <typename T>
class QueryEngine {
  T backend;

public:
  QueryEngine()= default;
  const T& get_backend(){return backend;}
public:
  QueryEngine& from(string file_name) {
    backend.load_file_csv(file_name);
    return *this;
  }
  QueryEngine& select(vector<string> columns) {
    backend.select(columns);
    return *this;
  }
  QueryEngine& take(int limit) {
    backend.set_take(limit);
    return *this;
  }
  QueryEngine& order_by(string column) {
    backend.order_by(column);
    return *this;
  }
  QueryEngine& join(string file_name, string col) {
    T new_csv;
    new_csv.load_file_csv(file_name);
    backend.join(new_csv, col);
    return *this;
  }
  QueryEngine& count_by(string column) {
    backend.count_by(column);
    return *this;
  }
public:
  QueryEngine& execute(const string& sql) {
    backend.clear();
    if (sql.empty())
      return *this;
    auto commands = split(sql, DEL_SQL);
    for (int i = 0; i < commands.size(); i++) {
      if (commands[i] == "FROM") {
        from(commands[i + 1]);
        i++;
      } else if (commands[i] == "SELECT") {
        select(split(commands[i + 1], DEL_CSV));
        i++;
      } else if (commands[i] == "TAKE") {
        take(stoi(commands[i + 1]));
        i++;
      } else if (commands[i] == "ORDERBY") {
        order_by(commands[i + 1]);
        i++;
      } else if (commands[i] == "JOIN") {
        join(commands[i + 1], commands[i + 2]);
        ++++i;
      } else if (commands[i] == "COUNTBY") {
        count_by(commands[i + 1]);
        i++;
      } else {
        throw invalid_argument("wrong SQL statement");
      }
    }
    return *this;
  }

  QueryEngine& show() {
    backend.show();
    return *this;
  }
};

void test() {
  QueryEngine<CSV> qo;
  qo.from("city.csv")
      .join("country.csv", "CountryCode")
      .join("language.csv", "CountryCode")
      .take(10)
      .show();
  qo.from("city.csv")
      .join("country.csv", "CountryCode")
      .take(1)
      .show();
  qo.from("language.csv")
      .count_by("Language")
      .count_by("count")
      .take(7)
      .show();
  qo.from("city.csv").order_by("CityPop").take(10).show();
  qo.from("city.csv").select({"CityName"}).take(2).show();
  qo.from("country.csv")
      .select({"CountryCode", "Continent", "CountryPop"})
      .show();
  qo.from("city.csv").select({"CityName"}).show();
}

vector<string> split(string s, const string &del) {
  vector<string> r;
  std::size_t i = 0;
  while ((i = s.find(del)) != string::npos || !s.empty()) {
    if (i != string::npos) {
      r.push_back(s.substr(0, i));
      s.erase(0, i + del.size());
    } else {
      r.push_back(s);
      s.clear();
    }
  }
  return r;
}

} // namespace databricks

#endif // PNSEI_CSV_QUERY_H
