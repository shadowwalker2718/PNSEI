#pragma once

#include "henry.h"

namespace _lnkd_is_intersected {

  // define the node struct of links
  typedef struct Node {
    int data = 0;
    struct Node* next = NULL;
  } Node;

  Node* has_circle(Node* head) {
    Node *h = head, *t = head;
    while (h && t && t->next) {
      h = h->next, t = t->next->next;
      if (h == t) return h;
    }
    return NULL;
  }

  int is_intersected(Node* p1, Node* p2) {
    Node* has_circle_1 = has_circle(p1);
    Node* has_circle_2 = has_circle(p2);

    if (has_circle_1) {
      if (has_circle_2) {
        Node* pp1 = has_circle_1;
        Node* pp2 = has_circle_2;
        if (pp1 == pp2 || pp1->next == pp2)
          return 1;
        while (pp1->next != has_circle_1) {
          pp1 = pp1->next;
          pp2 = pp2->next->next;
          if (pp1 == pp2)
            return 1;
        }
        return 0;
      } else {
        return 0;
      }
    } else {
      if (has_circle_2) {
        return 0;
      } else {
        while (p1->next)
          p1 = p1->next;
        while (p2->next)
          p2 = p2->next;
        return p1 == p2;
      }
    }
    return 0;
  }

  int test() {
    // no cycle
    {
      vector<Node> vn1(10);
      vector<Node> vn2(3);
      for (int i = 0; i < vn1.size() - 1; i++)
        vn1[i].next = &vn1[i + 1];
      for (int i = 0; i < vn2.size() - 1; i++)
        vn2[i].next = &vn2[i + 1];
      vn2.back().next = &vn1[7];

      assert(is_intersected(&vn1.front(), &vn2.front()));
    }

    {
      vector<Node> vn1(10);
      vector<Node> vn2(8);
      for (int i = 0; i < vn1.size() - 1; i++)
        vn1[i].next = &vn1[i + 1];
      for (int i = 0; i < vn2.size() - 1; i++)
        vn2[i].next = &vn2[i + 1];
      assert(!is_intersected(&vn1.front(), &vn2.front()));
    }


    // with cycle
    {// intersect at tail
      vector<Node> vn1(20);
      for (int i = 0; i < vn1.size() - 1; i++)
        vn1[i].next = &vn1[i + 1];
      vn1.back().next = &vn1[15];

      vector<Node> vn2(3);
      for (int i = 0; i < vn2.size() - 1; i++)
        vn2[i].next = &vn2[i + 1];
      vn2.back().next = &vn1[7];
      assert(is_intersected(&vn1.front(), &vn2.front()));
    }

    {// intersect at cycle
      vector<Node> vn1(20);
      for (int i = 0; i < vn1.size() - 1; i++)
        vn1[i].next = &vn1[i + 1];
      vn1.back().next = &vn1[8];

      vector<Node> vn2(3);
      for (int i = 0; i < vn2.size() - 1; i++)
        vn2[i].next = &vn2[i + 1];
      vn2.back().next = &vn1[17];
      assert(is_intersected(&vn1.front(), &vn2.front()));
    }

    {// no intersection
      vector<Node> vn1(20);
      for (int i = 0; i < vn1.size() - 1; i++)
        vn1[i].next = &vn1[i + 1];
      vn1.back().next = &vn1[15];

      vector<Node> vn2(10);
      for (int i = 0; i < vn2.size() - 1; i++)
        vn2[i].next = &vn2[i + 1];
      vn2.back().next = &vn2[7];
      assert(!is_intersected(&vn1.front(), &vn2.front()));
    }

    {// no intersection
      vector<Node> vn1(20);
      for (int i = 0; i < vn1.size() - 1; i++)
        vn1[i].next = &vn1[i + 1];
      vn1.back().next = &vn1[15];

      vector<Node> vn2(10);
      for (int i = 0; i < vn2.size() - 1; i++)
        vn2[i].next = &vn2[i + 1];
      assert(!is_intersected(&vn1.front(), &vn2.front()));
    }
    return 0;
  }

}




