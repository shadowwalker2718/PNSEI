#ifndef PNSEI_987_H
#define PNSEI_987_H

#include "utils/todo_binarytree.h"

namespace _987{
//Given a binary tree, return the vertical order traversal of its nodes values.
//
//
// For each node at position (X, Y), its left and right children respectively wi
//ll be at positions (X-1, Y-1) and (X+1, Y-1).
//
// Running a vertical line from X = -infinity to X = +infinity, whenever the ver
//tical line touches some nodes, we report the values of the nodes in order from t
//op to bottom (decreasing Y coordinates).
//
// If two nodes have the same position, then the value of the node that is repor
//ted first is the value that is smaller.
//
// Return an list of non-empty reports in order of X coordinate. Every report wi
//ll have a list of values of nodes.
//
//
//
// Example 1:
//
//
//
//
//
//Input: [3,9,20,null,null,15,7]
//Output: [[9],[3,15],[20],[7]]
//Explanation:
//Without loss of generality, we can assume the root node is at position (0, 0):
//
//Then, the node with value 9 occurs at position (-1, -1);
//The nodes with values 3 and 15 occur at positions (0, 0) and (0, -2);
//The node with value 20 occurs at position (1, -1);
//The node with value 7 occurs at position (2, -2).
//
//
//
// Example 2:
//
//
//
//
//Input: [1,2,3,4,5,6,7]
//Output: [[4],[2],[1,5,6],[3],[7]]
//Explanation:
//The node with value 5 and the node with value 6 have the same position accordi
//ng to the given scheme.
//However, in the report "[1,5,6]", the node value of 5 comes first since 5 is s
//maller than 6.
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


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
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
    // dep - depth/row/layer of the tree
    int ml = 0, mr = 0, dep = 0;
    dfs(root, 0, 0, ml, mr, dep);
    // L - size of the output vector
    int L = ml + mr + 1;

    return bfs(L, dep, root, ml);
  }

  // l -> current steps to the left; r-> current steps to the right
  void dfs(TreeNode *n, int l, int r, int &ml, int &mr, int &dep) {
    if (!n)
      return;
    dep++;
    dfs(n->left, l + 1, r, ml, mr, dep);
    dfs(n->right, l, r + 1, ml, mr, dep);
    ml = max(ml, l - r), mr = max(mr, r - l);
  }

  // https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/solution/
  // return the vertical order of a binary tree, which implies three sub-orders (denoted as <column, row, value>)
  // idx is column index, root node's column index is ml!!!
  vector<vector<int>> bfs(int L, int dep, TreeNode *n, int idx) {
    queue<pair<TreeNode*, int>> q; // pair<node, column index>
    q.push({n, idx});

    // [col][row/layer][values]
    vector<vector<vector<int>>> tmp(
        L, vector<vector<int>>(dep + 1, vector<int>()));
    int layer = 0;
    while (!q.empty()) {
      int sz = q.size();
      while (sz--) {
        auto t = q.front();
        q.pop();

        tmp[t.second][layer].push_back(t.first->val);
        if (t.first->left)
          q.push({t.first->left, t.second - 1});
        if (t.first->right)
          q.push({t.first->right, t.second + 1});
      }
      layer++;
    }
    // post-processing
    // sort tmp[column][row]
    for_each(tmp.begin(), tmp.end(), [](vector<vector<int>> &v) {
      for_each(v.begin(), v.end(),
               [](vector<int> &vv) { sort(vv.begin(), vv.end()); });
    });
    // generate final result
    vector<vector<int>> result(L, vector<int>());
    for (int i = 0; i < tmp.size(); ++i) {
      for (int j = 0; j < tmp[i].size(); ++j) {
        for (int k = 0; k < tmp[i][j].size(); ++k) {
          result[i].push_back(tmp[i][j][k]);
        }
      }
    }
    return result;
  }



};

  void test(){
    TreeNode* tn = createTree2();

    print_binary_tree_horizontal(tn);
    Solution sln;
    auto r = sln.verticalTraversal(tn);
    for_each(r.begin(), r.end(), [](auto& vi){
      for_each(vi.begin(), vi.end(), [](int i){
        cout << i << ",";
      });
      cout << "@" << endl;
    });
  }

}

#endif // PNSEI_987_H
