//
// Created by Henry Wu on 11/11/18.
//

#ifndef PNSEI_150_EVALUATE_REVERSE_POLISH_NOTATION_H
#define PNSEI_150_EVALUATE_REVERSE_POLISH_NOTATION_H

#include "henry.h"

namespace _150{
class Solution {
public:
  int evalRPN(vector<string>& tokens) {
    if (tokens.empty())
      return 0;
    stack<int> s;
    for (int i = 0; i < tokens.size(); i++)
    {
      if (tokens[i][0] >= '0' && tokens[i][0] <= '9' || tokens[i].size() > 1)
        s.push(stoi(tokens[i]));
      else
      {
        int right = s.top();
        s.pop();
        if (tokens[i] == "+")
          s.top() += right;
        else if (tokens[i] == "-")
          s.top() -= right;
        else if (tokens[i] == "*")
          s.top() *= right;
        else if (tokens[i] == "/")
          s.top() /= right;
      }
    }
    return s.top();
  }
};

void test(){
  Solution sln;
  vector<string> vs={"2", "1", "+", "3", "*"};
  assert(sln.evalRPN(vs) == 9);
}
}

#endif //PNSEI_150_EVALUATE_REVERSE_POLISH_NOTATION_H
