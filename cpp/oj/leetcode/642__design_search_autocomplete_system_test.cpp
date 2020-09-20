#include <gtest/gtest.h>
#include "642__design_search_autocomplete_system.h"

TEST(_642_design_search_autocomplete_system, basic){
  using namespace _642;
  AutocompleteSystem  as(
    {"i love you", "island", "ironman", "i love leetcode"},
    {5,3,2,2});

  auto r = as.input('i');
  for (auto &s: r){
    cout << s << endl;
  }

  r = as.input(' ');
  for (auto &s: r){
    cout << s << endl;
  }

  r = as.input('a');
  for (auto &s: r){
    cout << s << endl;
  }

  r = as.input('#');
  for (auto &s: r){
    cout << s << endl;
  }
}