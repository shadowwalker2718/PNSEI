#pragma once

#include "henry.h"
#include "utils/binarytree.h"

ListNode *createLN(list<int> li = {17, 15, 8, 12, 10, 5, 4, 1, 7, 6}) {
  // 17->15->8->12->10->5->4->1->7->6->NULL
  // list<int> li({17,15,8,12,10,5,4,1,7,6});
  ListNode h(0);
  ListNode *c = &h;
  for (int i : li) {
    c->next = new ListNode(i);
    c = c->next;
  }
  return h.next;
}
