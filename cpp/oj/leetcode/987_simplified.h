#ifndef PNSEI_987_2_H
#define PNSEI_987_2_H

#include "utils/todo_binarytree.h"

namespace _987_2 {
// Given a binary tree, return the vertical order traversal of its nodes values.
//
//
// For each node at position (X, Y), its left and right children respectively wi
// ll be at positions (X-1, Y-1) and (X+1, Y-1).
//
// Running a vertical line from X = -infinity to X = +infinity, whenever the ver
// tical line touches some nodes, we report the values of the nodes in order
// from t op to bottom (decreasing Y coordinates).
//
// If two nodes have the same position, then the value of the node that is repor
// ted first is the value that is smaller.
//
// Return an list of non-empty reports in order of X coordinate. Every report wi
// ll have a list of values of nodes.
//
//
//
// Example 1:
//
//
//
//
//
// Input: [3,9,20,null,null,15,7]
// Output: [[9],[3,15],[20],[7]]
// Explanation:
// Without loss of generality, we can assume the root node is at position (0,
// 0):
//
// Then, the node with value 9 occurs at position (-1, -1);
// The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
// The node with value 20 occurs at position (1, -1);
// The node with value 7 occurs at position (2, -2).
//
//
//
// Example 2:
//
//
//
//
// Input: [1,2,3,4,5,6,7]
// Output: [[4],[2],[1,5,6],[3],[7]]
// Explanation:
// The node with value 5 and the node with value 6 have the same position
// accordi ng to the given scheme. However, in the report "[1,5,6]", the node
// value of 5 comes first since 5 is s maller than 6.
//
//
//
//
//
// Note:
//
//
// The tree will have between 1 and 1000 nodes.
// Each node's value will be between 0 and 1000.
//
//
//
//
//
//
// Related Topics Hash Table Tree
// 👍 632 👎 1434

// leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
// to generate a list that contains the 3-dimensional coordinates (i.e. <column,
// row, value>) of each node.
// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/solution/
class Solution {
public:
  vector<vector<int>> verticalTraversal(TreeNode *root) {
    if (!root)
      return vector<vector<int>>();
    // ml - max steps to the left from root
    // mr - max steps to the right from root
    int ml = 0, mr = 0;
    dfs(root, 0, 0, ml, mr);
    // L - size of the output vector
    int L = ml + mr + 1;
    return bfs(L, root, ml);
  }

  // l -> current steps to the left; r-> current steps to the right
  void dfs(TreeNode *n, int l, int r, int &ml, int &mr) {
    if (!n)
      return;
    dfs(n->left, l + 1, r, ml, mr);
    dfs(n->right, l, r + 1, ml, mr);
    ml = max(ml, l - r), mr = max(mr, r - l);
  }

  // idx is column index, root node's column index is ml!!!
  vector<vector<int>> bfs(int L, TreeNode *n, int idx) {
    queue<pair<TreeNode*, int>> q; // pair<node, column index>
    q.push({n, idx});
    // [col][values]
    vector<vector<int>> result(L, vector<int>());
    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        auto t = q.front();
        q.pop();
        result[t.second].push_back(t.first->val);
        if (t.first->left)
          q.push({t.first->left, t.second - 1});
        if (t.first->right)
          q.push({t.first->right, t.second + 1});
      }
    }
    return result;
  }
};

} // namespace _987_2

#endif // PNSEI_987_2_H
