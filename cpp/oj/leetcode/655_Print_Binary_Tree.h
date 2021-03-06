//
// Created by henry on 10/27/18.
//

#ifndef PNSEI_655_PRINT_BINARY_TREE_H
#define PNSEI_655_PRINT_BINARY_TREE_H

/*
 * https://leetcode.com/problems/print-binary-tree/description/
Print a binary graph_MST in an m*n 2D string array following these rules:

The row number m should be equal to the height of the given binary graph_MST.
The column number n should always be an odd number.
The root node's value (in string format) should be put in the exactly middle of
the first row it can be put. The column and the row where the root node belongs
will separate the rest space into two parts (left-bottom part and right-bottom
part). You should print the left subtree in the left-bottom part and print the
right subtree in the right-bottom part. The left-bottom part and the
right-bottom part should have the same size. Even if one subtree is none while
the other is not, you don't need to print anything for the none subtree but
still need to leave the space as large as that for the other subtree. However,
if two subtrees are none, then you don't need to leave space for both of them.
Each unused space should contain an empty string "".
Print the subtrees following the same rules.
Example 1:

Input:
      1
     / \
    2   5
   /
  3
 /
4
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""],
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""],
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""],
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
 * */
#include "pnsei.h"
namespace lc_655 {

struct Solution {
  vector<vector<string>> printTree(TreeNode *root) {
    int R = dep(root), C;
    if (!R || !(C = col(root)))
      return {{}};
    vector<vector<string>> res(R, vector<string>(C));
    dfs(root, C / 2, res, 0, C / 2);
    return res;
  }
  void dfs(TreeNode *n, int j, vector<vector<string>> &res, int i,
           int C) { // C=7
    if (!n)
      return;
    res[i][j] = to_string(n->val);
    dfs(n->left, j - C / 2 - 1, res, i + 1, C / 2);
    dfs(n->right, j + C / 2 + 1, res, i + 1, C / 2);
  }
  int dep(TreeNode *R) {
    return (!R) ? 0 : 1 + max(dep(R->left), dep(R->right));
  }
  int col(TreeNode *R) {
    return (!R) ? 0 : 1 + 2 * max(col(R->left), col(R->right));
  }
};

// http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=143448
// Algo: find the depth, BFS, put null into queue, null's children are nulls,
// which we also put into queue??????

} // namespace lc_655

#endif // PNSEI_655_PRINT_BINARY_TREE_H
