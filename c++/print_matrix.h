#pragma once
#include "henry.h"

namespace _print_matrix {

  void NW2SE(vector<vector<int>> v) {
    int ROW = v.size(), COL = v[0].size();

    int i = ROW - 1;
    while (i>=0) {
      int k = i, j=0;
      while(k<ROW && j<COL) cout << v[k++][j++] << " ";
      i--;
      cout << endl;
    }

    int j = 1;
    while (j < COL) {
      int k = j, i = 0;
      while (k<COL && i<ROW) cout << v[i++][k++] << " ";
      j++;
      cout << endl;
    }
  }

  void test() {
    vector<vector<int>> v = {
      { 1,2,3,4 },
      { 5,6,7,8 },
      { 9,10,11,12 },
    };

    NW2SE(v);
  }

}



