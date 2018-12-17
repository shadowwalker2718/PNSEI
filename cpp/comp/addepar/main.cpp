#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
namespace fs = experimental::filesystem;

struct node {
  ifstream *infile;
  string val;
  string filename;
};

struct compNode {
  bool operator()(node *p, node *q) const { return p->val > q->val; }
};

int main(int argc, char **argv) {
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
  for (auto &p : fs::directory_iterator(argv[1])) {
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