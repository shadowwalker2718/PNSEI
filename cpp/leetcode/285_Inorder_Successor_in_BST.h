//
// Created by root on 11/23/18.
//

#ifndef PNSEI_285_INORDER_SUCCESSOR_IN_BST_H
#define PNSEI_285_INORDER_SUCCESSOR_IN_BST_H

#include "henry.h"
#include "utils/binarytree.h"

namespace _285 {

/* https://leetcode.com/problems/inorder-successor-in-bst/

  Given a binary search tree and a node in it, find the in-order successor of that node in the BST.
  Note: If the given node has no in-order successor in the tree, return null.

  Example 1:
  Input: root = [2,1,3], p = 1
    2
   / \
  1   3
  Output: 2

  Example 2:
  Input: root = [5,3,6,2,4,null,null,1], p = 6
        5
       / \
      3   6
     / \
    2   4
   /
  1
  Output: null
 * */
struct Solution {
  TreeNode *inorderSuccessor(TreeNode *R, TreeNode *p) {
    if (p->right) {
      p = p->right;
      while (p->left) p = p->left; // leftmost
      return p;
    }
    TreeNode *suc = NULL;
    while (R){
      if (R->val > p->val)
        suc = R, R = R->left;//注意suc只在这里更新
      else if (R->val < p->val)
        R = R->right;
      else // R->val == p->val
        break;
    }
    return suc;
  }
};
}
#endif //PNSEI_285_INORDER_SUCCESSOR_IN_BST_H
