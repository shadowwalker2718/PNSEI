//
// Created by root on 11/22/18.
//

#ifndef PNSEI_CONCURRENT_LINKEDLIST_H
#define PNSEI_CONCURRENT_LINKEDLIST_H

#include "henry.h"
#include "scopedlock.h"

namespace _concurrent_ll {


// Algo is from https://www.cse.wustl.edu/~angelee/archive/cse539/spr15/lectures/lists.pdf
/*
Deadlock-free:	some	thread	trying	to	acquire	the	lock	eventually	succeeds.
Starvation-free:	every	thread	trying	to	acquire	the	lock	eventually	succeeds.
Lock-free:	some	thread	calling	a	method	eventually	returns.
Wait-free:	every	thread	calling	a	method	eventually	returns.
*/

// intrusive list node
struct list_node {
  mutex mu;
  int val;
  shared_ptr<list_node> next;
  list_node(int i=INT_MIN, shared_ptr<list_node> next_ = nullptr) : val(i), next(next_) {}
};

class concurrent_linkedlist {
public:
  shared_ptr<list_node> head;
  atomic<int> z;

  concurrent_linkedlist(const concurrent_linkedlist &) = delete;

  concurrent_linkedlist operator=(const concurrent_linkedlist &) = delete;


  concurrent_linkedlist() : head(nullptr) {
    z.store(0, memory_order_seq_cst); // z=0;
  }

  ~concurrent_linkedlist() {}

  // if insert inside, we also only need to lock prev and cur, the cur->next should be valid coz if it is deleted,
  // the previous one aka current one should be locked up, so it should wait
  void push_back(int i) {
    if (!head) {
      head = make_shared<list_node>(i);
      z++;
      return;
    }
    auto c = head;
    while (c->next)
      c = c->next;
    lock_guard<mutex> lg(c->mu); //RAII
    c->next = make_shared<list_node>(i);
    z++;
  }

  // to erase, you have to lock previous node, see the PDF above
  void erase(int i) {
    auto c = head;
    shared_ptr<list_node> dummy = make_shared<list_node>(INT_MIN, head);// list_node dummy; prev=&dummy; (X)
    shared_ptr<list_node> prev = dummy; // copy, not move
    while (c) {
      scoped_lock lock(prev->mu, c->mu); // c++17, fine grained lock, do we need it?
      //myscoped_lock slk(prev->mu, c->mu);
      if (c->val == i) {
        prev->next = c->next; // remove current node
        z--;
        break;
      }
      prev = c, c = c->next;
    }
    head = dummy->next; //////
  }

  void promote(int i) {
    auto c = head;
    shared_ptr<list_node> prev=make_shared<list_node>(), target=make_shared<list_node>();
    while (c) {
      //scoped_lock lock(prev->mu, c->mu); // fine grained lock, do we need it?
      myscoped_lock slk(prev->mu, c->mu);
      if (c->val == i) {
        target = c;
        prev->next = c->next; // erased target already
        break;
      }
      prev = c, c = c->next;
    }
    if (target == nullptr)
      return;
    myscoped_lock msl(head->mu, target->mu);// head->...xyz       target->  ...->tail
    target->next = head;
    head = target;
  }

  bool contain(int i) {
    auto c = head;
    while (c) {
      lock_guard<mutex> lg(c->mu); // fine grained lock
      if (c->val == i)
        return true;
      c = c->next;
    }
    return false;
  }
};


void test() {
  concurrent_linkedlist cl;
  REP(i, 0, 100) {
    cl.push_back(i);
  }
  cl.erase(0);
  cl.erase(99);
  cl.promote(50);
  assert(cl.contain(51));
  assert(cl.z == 98);
  assert(cl.head->val == 50);
}


}


#endif //PNSEI_CURRENT_LINKEDLIST_H
