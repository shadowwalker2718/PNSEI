//
// Created by henry on 10/24/18.
//

#ifndef C_ADDEPAR_H
#define C_ADDEPAR_H

#include "henry.h"

namespace addepar {
struct node {
  ifstream *infile;
  string val;
  string filename;
};

struct compNode {
  bool operator()(node *p, node *q) const { return p->val > q->val; }
};

int run(int argc, vector<string> argv);
void test();
}; // namespace addepar

#endif // C_ADDEPAR_H
