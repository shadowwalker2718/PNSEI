//
// Created by root on 11/3/18.
//

#ifndef PNSEI_109_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H
#define PNSEI_109_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H

#include "henry.h"
#include "utils/binarytree.h"
/*
 *
 * Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5


 * */

namespace _109{
    TreeNode* sortedListToBST(ListNode* head, ListNode* e=NULL) { // [)
        if(head==e) return NULL;
        ListNode *s=head, *f=head;
        while(f!=e and f->next!=e and f->next->next!=e){
            s=s->next, f=f->next->next;
        }
        TreeNode* R=new TreeNode(s->val);
        R->left=sortedListToBST(head, s);
        R->right=sortedListToBST(s->next, e);
        return R;
    }
}

#endif //PNSEI_109_CONVERT_SORTED_LIST_TO_BINARY_SEARCH_TREE_H