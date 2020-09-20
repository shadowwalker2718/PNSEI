#include <gtest/gtest.h>
#include "162_Find_Peak_Element.h"

TEST(_162_Find_Peak_Element, a) {
  using namespace _162;
  VI v = {1, 2, 3, 1};
  assert(findPeakElement(v) == 2);
  v = {1, 2, 1, 3, 5, 6, 4};
  int r = findPeakElement(v);
  assert(r == 2 || r == 5);
}

TEST(_162_Find_Peak_Element, b) {
  using namespace _162;
  VI v = {3, 2, 1};
  cout << findPeakElement(v)  << endl;
}

TEST(_162_Find_Peak_Element, c) {
  using namespace _162;
  VI v = {1, 2, 3};
  cout << findPeakElement(v)  << endl;
}