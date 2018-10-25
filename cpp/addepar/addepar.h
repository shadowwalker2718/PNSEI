//
// Created by henry on 10/24/18.
//

#ifndef C_ADDEPAR_H
#define C_ADDEPAR_H

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
namespace fs = experimental::filesystem;

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
