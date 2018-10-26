#pragma once
#include "henry.h"

namespace _230 {

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  int nn(TreeNode *root) {
    if (!root)
      return 0;
    return nn(root->left) + nn(root->right) + 1;
  }
  int kthSmallest_1(TreeNode *root, int k) {
    int l = nn(root->left);
    int r = nn(root->right);
    if (l + 1 == k)
      return root->val;
    else if (l + 1 < k) {
      return kthSmallest(root->right, k - l - 1);
    } else {
      return kthSmallest(root->left, k);
    }
  }

  // Have to modify tree
  int kthSmallest(TreeNode *c, int k) { // Morris Traversal
    if (!c || k <= 0)
      return 0;
    TreeNode *p, *t;
    while (c) {
      if (c->left) {
        t = p = c->left;
        while (p->right)
          p = p->right;
        c->left = 0, p->right = c, c = t;
      } else {
        if (k == 1)
          return c->val;
        k--, c = c->right;
      }
    }
    return 0;
  }
};
} // namespace _230
