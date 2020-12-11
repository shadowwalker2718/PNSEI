#include "gtest/gtest.h"
#include "csv_query.h"

TEST(db_check, test_csv_query){
  using namespace databricks::csv_query;
  QueryEngine<CSV> qe;
  const VS sql = {
      "FROM city.csv",
      "FROM country.csv",
      "FROM language.csv",
      "FROM city.csv SELECT CityName",
      "FROM country.csv SELECT CountryCode,Continent,CountryPop",
      "FROM city.csv TAKE 2",
      "FROM city.csv TAKE 5",
      "FROM city.csv TAKE 10",
      "FROM city.csv ORDERBY CityPop TAKE 10",
      "FROM city.csv JOIN country.csv CountryCode",
      "FROM city.csv JOIN country.csv CountryCode JOIN language.csv CountryCode",
      "FROM language.csv COUNTBY Language ORDERBY count TAKE 7"
  };
  const vector<pair<int,int>> expected={
      {4079,4},
      {239,5},
      {984,2},
      {4079,1},
      {239,3},
      {4079,4},
      {4079,4},
      {4079,4},
      {4079,4},
      {4079,8},
      {4079,9},
      {457,2}
  };
  for (int i = 0; i < sql.size(); ++i) {
    qe.execute(sql[i]);
    EXPECT_EQ(expected[i].first, qe.get_backend().row_size());
    EXPECT_EQ(expected[i].second, qe.get_backend().col_size());
  }

  EXPECT_EQ(qe.execute("").get_backend().col_size(), 0);
  EXPECT_THROW(qe.execute("abc"), invalid_argument);
  qe.execute("FROM city.csv TAKE 2").show();
  qe.execute("FROM city.csv JOIN country.csv CountryCode JOIN language.csv CountryCode TAKE 2").show();
}