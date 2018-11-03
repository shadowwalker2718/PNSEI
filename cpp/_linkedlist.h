#pragma once

#include "henry.h"

struct lnode {
  int val;
  lnode *next;
  lnode(int x) : val(x), next(0) {}
};

lnode *createLN(list<int> li = {17, 15, 8, 12, 10, 5, 4, 1, 7, 6}) {
  // 17->15->8->12->10->5->4->1->7->6->NULL
  // list<int> li({17,15,8,12,10,5,4,1,7,6});
  lnode h(0);
  lnode *c = &h;
  for (int i : li) {
    c->next = new lnode(i);
    c = c->next;
  }
  return h.next;
}
