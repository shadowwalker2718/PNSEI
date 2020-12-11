//
// Created by Henry Wu on 12/5/18.
//

#ifndef PNSEI_98_VALIDATE_BINARY_SEARCH_TREE_H
#define PNSEI_98_VALIDATE_BINARY_SEARCH_TREE_H

/* https://leetcode.com/problems/validate-binary-search-tree/

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:

Input:
    2
   / \
  1   3
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.
*/

#include "pnsei.h"
#include "utils/todo_binarytree.h"

namespace _98 {

class Solution {
public:
  bool isValidBST(TreeNode *root) {
    return rec(root, INT_MIN - 1LL, INT_MAX + 1LL); // BUG?
  }

  bool rec(TreeNode *root, long long mi, long long mx) {
    if (!root) return true;
    if (mi >= root->val || root->val >= mx) // BUG?
      return false;
    if (root->left) {
      if (!rec(root->left, mi, root->val))
        return false;
    }
    if (root->right) {
      if (!rec(root->right, root->val, mx))
        return false;
    }
    return true;
  }
};


void test(){
  auto R = create_A_BST();
  assert(Solution().isValidBST(R));
}

}
#endif //PNSEI_98_VALIDATE_BINARY_SEARCH_TREE_H
