//
// Created by henry on 10/24/18.
//

#include "addepar.h"

/* My environment is Ubuntu 18 and g++ version 7.3.0.

Compile and run:
$g++ main.cpp -o main -std=c++17 -lstdc++fs && ./main test ooo.txt

Result:
$cat ooo.txt
familiarity breeds contempt
no peace for the wicked
slow and steady wins the race
the pen is mightier
the truth will set you free
to err is human

*/

int addepar::run(int argc, vector<string> argv) {
  if (argc < 3) {
    cout << "Usage:\n./merge input_dir output_file\n";
    return 0;
  }
  vector<node *> nodes;
  auto clear_memory = [](vector<node *> nodes) {
    for (node *p : nodes) { // clear memory
      delete p->infile;
      delete p;
    }
  };
  for (auto &p : fs::recursive_directory_iterator(argv[1])) {
    if (fs::is_directory(p))
      continue;
    node *n = new node();
    n->infile = new ifstream;
    n->filename = p.path().string();
    n->infile->open(n->filename, ifstream::in);

    while (getline(*n->infile, n->val)) {
      if (n->val.size() > 0)
        break;
    }
    if (n->val.size() > 0)
      nodes.push_back(n);
  }

  priority_queue<node *, vector<node *>, compNode> pq(nodes.begin(),
                                                      nodes.end());
  string result, prev;
  while (pq.size() > 0) {
    node *n = pq.top();
    pq.pop();
    if (n->val > prev) {
      result += n->val + "\n";
      prev = n->val;
    }
    n->val = "";
    while (getline(*n->infile, n->val)) {
      if (n->val.size() > 0) {
        if (n->val < prev) {
          cout << "ERROR: file(" << n->filename << ") is not sorted!" << endl;
          cout << prev << "\nis ahead of:\n" << n->val << endl;
          clear_memory(nodes);
          return 1;
        }
        if (n->val > prev) {
          pq.push(n);
          break;
        }
      }
    }
  }
  result.pop_back();
  ofstream myfile(argv[2]);
  myfile << result;
  myfile.close();
  clear_memory(nodes);
  return 0;
}

void addepar::test() { addepar::run(3, {"", "../addepar/data", "output.txt"}); }
