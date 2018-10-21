//
// Created by henry on 10/21/18.
//
#include "henry.h"

#ifndef C_927_THREE_EQUAL_PARTS_H
#define C_927_THREE_EQUAL_PARTS_H

namespace _927 {
  class Solution {
  public:
    vector<int> threeEqualParts(vector<int> &A) {
      int i = 0, L = A.size();
      while (i < L - 1) {
        int j=L-1;
        while (j > 1) {
          if (f(A, i, j))
            return {i, j};
          j--;
        }
        i++;
      }
      return {-1, -1};
    }

    bool f(vector<int> &A, int i, int j) {
      string x, y, z;
      for (int m = 0; m <= i; m++)
        x += A[m] ? "1" : "0";
      f2(x);
      for (int k = j; k < A.size(); k++)
        z += A[k] ? "1" : "0";
      f2(z);
      if (x != z) return false;
      for (int m = i + 1; m < j; m++)
        y += A[m] ? "1" : "0";
      f2(y);
      return x == y;
    }

    void f2(string &s) {
      while (s[0] == '0') s.erase(s.begin());
    }
  };

  bool test() {
    Solution sln;
    vector<int> vi = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    auto r = sln.threeEqualParts(vi);
    assert(r == vector<int>({176, 338}));
    copy(r.begin(), r.end(), ostream_iterator<int>(cout, ", ")); cout << endl;
  };

}

#endif //C_927_THREE_EQUAL_PARTS_H
