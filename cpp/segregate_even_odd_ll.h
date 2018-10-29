#pragma once

#include "henry.h"
#include "_linkedlist.h"

namespace segregate_even_odd_ll {
// http://www.geeksforgeeks.org/segregate-even-and-odd-elements-in-a-linked-list/

ListNode *Segregate_even_and_odd_nodes(ListNode *p) {
  ListNode h1(0), h2(0);
  ListNode *c1 = &h1, *c2 = &h2;
  while (p) {
    if (p->val & 1)
      c1->next = p, c1 = p;
    else
      c2->next = p, c2 = p;
    p = p->next;
  }
  c2->next = h1.next;
  c1->next = 0; ////
  return h2.next;
}

// odd is in reversed order
ListNode *Segregate_even_and_odd_nodes2(ListNode *p) {
  ListNode h2(0); ////
  ListNode *c1 = 0, *c2 = &h2;
  while (p) {
    if (p->val & 1) {
      ListNode *t = p->next;
      p->next = c1, c1 = p;
      p = t;
    } else {
      c2->next = p, c2 = p;
      p = p->next;
    }
  }
  c2->next = c1;
  // c1->next = 0;////
  return h2.next;
}

void test() {
  ListNode *p = createLN();
  auto r = Segregate_even_and_odd_nodes(p);
  while (r) {
    cout << r->val << endl;
    r = r->next;
  }

  ListNode *p2 = createLN();
  r = Segregate_even_and_odd_nodes2(p2);
  while (r) {
    cout << r->val << endl;
    r = r->next;
  }

  p = createLN({1});
  r = Segregate_even_and_odd_nodes(p);
  while (r) {
    cout << r->val << endl;
    r = r->next;
  }

  p = createLN({2});
  r = Segregate_even_and_odd_nodes(p);
  while (r) {
    cout << r->val << endl;
    r = r->next;
  }
}

} // namespace segregate_even_odd_ll