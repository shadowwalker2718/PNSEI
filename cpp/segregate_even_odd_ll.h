#pragma once

#include "_linkedlist.h"
#include "henry.h"

namespace segregate_even_odd_ll {
// http://www.geeksforgeeks.org/segregate-even-and-odd-elements-in-a-linked-list/

lnode *Segregate_even_and_odd_nodes(lnode *p) {
  lnode h1(0), h2(0);
  lnode *c1 = &h1, *c2 = &h2;
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
lnode *Segregate_even_and_odd_nodes2(lnode *p) {
  lnode h2(0); ////
  lnode *c1 = 0, *c2 = &h2;
  while (p) {
    if (p->val & 1) {
      lnode *t = p->next;
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
  lnode *p = createLN();
  auto r = Segregate_even_and_odd_nodes(p);
  while (r) {
    cout << r->val << endl;
    r = r->next;
  }

  lnode *p2 = createLN();
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