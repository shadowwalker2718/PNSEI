#ifndef PNSEI_STRETCHED_TREE_H
#define PNSEI_STRETCHED_TREE_H

#include "utils/todo_binarytree.h"

TreeNode* dfs(TreeNode* root, int stretchAmount, int leftist);

/*
 * Write a recursive algorithm that replaces each single binary tree node with
multiple nodes with smaller values. Your algorithm is called with two
parameters: a reference to a TreeNode pointer representing the root of a binary
tree, and an integer "stretching factor" K. Your function should replace each
node N with K nodes, each of which stores a data value that is 1/K of N's
original value, using integer division.

The new clones of node N should extend from their parent in the same direction
that N extends from its parent. For example, if N is its parent's left child,
the stretched clones of N should also be their parent's left child, and vice
versa if N was a right child. The root node is a special case because it has no
parent; we will handle this by saying that its stretched clones should extend to
the left.
https://imgur.com/a/mfholT9
Constraints: Do not modify the signature of the stretch interface

signature: void stretch(root *TreeNode, stretchAmount int)

You must use recursion in your solution to visit each tree node
*/
class Stretcher{
public:
  void stretch(TreeNode* root, int stretchAmount){
    if (!root or stretchAmount<2)
      return;
    dfs(root, stretchAmount, true);
  }

private:
  TreeNode* dfs(TreeNode* root, int stretchAmount, bool leftist){
    if (!root or stretchAmount<2)
      return nullptr;
    int stretched_val = root->val/stretchAmount;
    root->val = stretched_val;
    auto original_left = root->left, original_right = root->right;
    if (leftist)
      root->right = nullptr;
    else
      root->left = nullptr;
    TreeNode* t = root;
    for (int i = 0; i < stretchAmount-1; ++i) {
      if (leftist){
        t->left = new TreeNode(stretched_val);
        t = t->left;
      } else {
        t->right = new TreeNode(stretched_val);
        t = t->right;
      }
    }
    t->left = dfs(original_left, stretchAmount, true);
    t->right = dfs(original_right, stretchAmount, false);
    return root;
  }
};



#endif // PNSEI_STRETCHED_TREE_H
