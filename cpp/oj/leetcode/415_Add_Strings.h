//
// Created by Henry Wu on 12/1/18.
//

#ifndef PNSEI_415_ADD_STRINGS_H
#define PNSEI_415_ADD_STRINGS_H

#include "pnsei.h"

namespace _415{

struct Solution {
  string addStrings(string num1, string num2) {
    string r;
    for (int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
         i >= 0 || j >= 0 || carry; carry /= 10)
    {
      if (i >= 0) carry += num1[i--] - '0';
      if (j >= 0) carry += num2[j--] - '0';
      r += to_string(carry % 10);
    }
    reverse(r.begin(), r.end());
    return r;
  }
};

}

#endif //PNSEI_415_ADD_STRINGS_H
