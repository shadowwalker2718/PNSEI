//
// Created by Henry Wu on 11/12/18.
//

#ifndef PNSEI_PAIRWISE_SWAP_ELEMENTS_OF_A_GIVEN_LINKED_LIST_H
#define PNSEI_PAIRWISE_SWAP_ELEMENTS_OF_A_GIVEN_LINKED_LIST_H

#include "pnsei.h"
#include "utils/todo_binarytree.h"

namespace _cruise_ll{
/*https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=456384&highlight=cruise
 *
 * 2018(10-12月) 码农类General 本科 实习@Cruise - 内推 - 技术电面  | Fail | fresh grad应届毕业生
发一个cruise电面跪经,不知道为啥跪的.-baidu 1point3acres
两个面试官,用coderpad.
第一道是linkedlist pairwise reverse.
第二道是array找最大element的index.Followup是有duplicate,randomly return 一个最大的element index.
很简单,可能是我用java写他们不要java的?无解.
希望攒个人品 这周能拿offer.
 * */
// https://www.geeksforgeeks.org/pairwise-swap-elements-of-a-given-linked-list/

// 1. Swap Data
/* Function to pairwise swap elements of a linked list */
void pairWiseSwap_algo1(struct ListNode *head){
  struct ListNode *temp = head;
  /* Traverse further only if there are at-least two nodes left */
  while (temp != NULL && temp->next != NULL){
    /* Swap data of node with its next node's data */
    swap(temp->val, temp->next->val);
    /* Move temp by 2 for the next pair */
    temp = temp->next->next;
  }
}

/* Recursive function to pairwise swap elements of a linked list */
void pairWiseSwap_rec(struct ListNode *head){
  /* There must be at-least two nodes in the list */
  if (head != NULL && head->next != NULL) {
    /* Swap the node's data with data of next node */
    swap(head->val, head->next->val);
    /* Call pairWiseSwap() for rest of the list */
    pairWiseSwap_rec(head->next->next);
  }
}

// 2. If data contains many fields, there will be many swap operations. So changing links is a better idea in general.
// https://www.geeksforgeeks.org/pairwise-swap-elements-of-a-given-linked-list-by-changing-links/
/* Function to pairwise swap elements of a linked list.
   It returns head of the modified list, so return value
   of this node must be assigned */
struct ListNode *pairWiseSwap_by_Link(struct ListNode* head){
  // Base Case: The list is empty or has only one node
  if (head == NULL || head->next == NULL)
    return head;
  // Store head of list after two nodes
  struct ListNode* tmp = head->next->next;
  // Change head
  struct ListNode* newhead = head->next;
  // Change next of second node
  head->next->next = head;
  // Recur for remaining list and change next of head
  head->next = pairWiseSwap_by_Link(tmp);
  // Return new head of modified list
  return newhead;
}
// head -> next1 - > next2 - > next3
//
//  ----------------
//  |              |
//  |              v
// head <- next1  next2 - > next3
};

#endif //PNSEI_PAIRWISE_SWAP_ELEMENTS_OF_A_GIVEN_LINKED_LIST_H
