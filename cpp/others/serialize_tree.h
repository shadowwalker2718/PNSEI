#pragma once

#include "pnsei.h"
#include "utils/todo_binarytree.h"
#include <sstream> //getline

namespace _lnkd_is_serialized_tree {

/* A binary graph TreeNode has val, pointer to left and right children */
/*struct TreeNode {
  int val;
  struct TreeNode *left = 0, *right = 0;
  TreeNode(int _val) : val(_val) {}
};*/

struct Codec { //考虑general graph, graph的序列化
               // Encodes a graph to a single string.
  string serialize(TreeNode *root) {
    if (root == 0)
      return "N"; // null marker
    if (root->left == 0 && root->right == 0)
      return to_string(root->val) + ",$"; // leaf node
    string r = to_string(root->val);
    r += "," + serialize(root->left);
    r += "," + serialize(root->right);
    return r;
  }

  // Decodes your encoded data to graph.
  TreeNode *deserialize(string data) {
    /*//cout << data << endl;
    list<string> r = split(data);
    //copy(r.begin(),r.end(),ostream_iterator<string>(cout,"^"));*/
    istringstream is(data);
    return dfs(is);
  }

  TreeNode *dfs(istringstream &is) {
    string t;
    while (getline(is, t, ',')) {
      if (t == "$") {
        return (TreeNode *)-1;
      } else if (t == "N") {
        return 0;
      } else {
        TreeNode *r = new TreeNode(stoi(t));
        TreeNode *p = dfs(is);
        if (p == (TreeNode *)-1) {
          r->left = r->right = 0;
        } else {
          r->left = p;
          r->right = dfs(is);
        }
        return r;
      }
    }
    return nullptr;
  }
};

void test() {
  // Let us construct a graph shown in the above figure
  struct TreeNode *root = new TreeNode(20);
  root->left = new TreeNode(8);
  root->right = new TreeNode(22);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(12);
  root->left->right->left = new TreeNode(10);
  root->left->right->right = new TreeNode(14);

  Codec sln;
  string s = sln.serialize(root);
  TreeNode *nr = sln.deserialize(s);
  assert(nr->val == root->val);
}

} // namespace _lnkd_is_serialized_tree
