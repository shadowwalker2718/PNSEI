//
// Created by Henry Wu on 11/3/18.
//

#ifndef PNSEI_109_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H
#define PNSEI_109_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H

#include "pnsei.h"
#include "utils/todo_binarytree.h"
/*
Given a singly linked list where elements are sorted in ascending order,
convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary
tree in which the depth of the two subtrees of every node never differ
by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following
height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5


 * */

namespace _109 {
// A half-open range is one which includes the first element, but excludes the
// last one. which is easier than all inclusive range
// T: O(NLogN), S: O(LogN)
TreeNode *sortedListToBST(ListNode *head, ListNode *_end = NULL) { // [)
  if (head == _end)
    return NULL;
  ListNode *slow = head, *fast = head;
  while (fast != _end && fast->next != _end)
    slow = slow->next, fast = fast->next->next;
  // s becomes lower median
  TreeNode *R = new TreeNode(slow->val);
  R->left = sortedListToBST(head, slow);
  R->right = sortedListToBST(slow->next, _end);
  return R;
}
} // namespace _109

#endif // PNSEI_109_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H
