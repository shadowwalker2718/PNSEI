//
// Created by root on 11/22/18.
//

#ifndef PNSEI_CONCURRENT_LINKEDLIST_H
#define PNSEI_CONCURRENT_LINKEDLIST_H

#include "henry.h"

namespace _concurrent {


// Algo is from https://www.cse.wustl.edu/~angelee/archive/cse539/spr15/lectures/lists.pdf
/*
Deadlock-free:	some	thread	trying	to	acquire	the	lock	eventually	succeeds.
Starvation-free:	every	thread	trying	to	acquire	the	lock	eventually	succeeds.
Lock-free:	some	thread	calling	a	method	eventually	returns.
Wait-free:	every	thread	calling	a	method	eventually	returns.
*/

struct list_node {
  mutex mu;
  int val;
  shared_ptr<list_node> next;

  list_node(int i, shared_ptr<list_node> next_ = nullptr) : val(i), next(next_) {}
};


// https://stackoverflow.com/questions/20516773/stdunique-lockstdmutex-or-stdlock-guardstdmutex
// std::unique_lock has other features that allow it to e.g.: be constructed without locking
// the mutex immediately but to build the RAII wrapper (see here).
struct scoped_lock_base {
  unique_lock<mutex> ul;

  scoped_lock_base(mutex &a) {
    unique_lock<mutex> t(a);
    //ul.swap(t);
    ul = move(t); // method 1
  }
};

struct myscoped_lock : public scoped_lock_base {
  unique_lock<mutex> ul2;

  myscoped_lock(mutex &a_, mutex &b_) : scoped_lock_base(a_) { // cannot use ref-to-const for mutex
    unique_lock<mutex> t(b_);
    ul2.swap(t); // method 2
  }
};

class concurrent_linkedlist {
public:
  shared_ptr<list_node> head;
  atomic<int> z;

  concurrent_linkedlist(const concurrent_linkedlist &) = delete;

  concurrent_linkedlist operator=(const concurrent_linkedlist &) = delete;


  concurrent_linkedlist() : head(nullptr) {
    z.store(0, memory_order_seq_cst);
  }

  ~concurrent_linkedlist() {}

  void insert(int i) {
    if (!head) {
      head = make_shared<list_node>(i);
      z++;
      return;
    }
    auto c = head;
    while (c->next)
      c = c->next;
    lock_guard<mutex> lg(c->mu);
    c->next = make_shared<list_node>(i);
    z++;
  }

  // to erase, you have to lock previous node, see the PDF above
  void erase(int i) {
    auto c = head;
    //shared_ptr<list_node> prev;
    shared_ptr<list_node> dummy = make_shared<list_node>(INT_MIN, head);
    shared_ptr<list_node> prev = dummy;
    while (c) {
      //scoped_lock lock(prev->mu, c->mu); // fine grained lock, do we need it?
      myscoped_lock slk(prev->mu, c->mu);
      if (c->val == i) {
        prev->next = c->next;
        z--;
        break;
      }
      prev = c, c = c->next;
    }
    head = dummy->next;
  }

  void promote(int i) {
    auto c = head;
    shared_ptr<list_node> prev, target;
    while (c) {
      //scoped_lock lock(prev->mu, c->mu); // fine grained lock, do we need it?
      myscoped_lock slk(prev->mu, c->mu);
      if (c->val == i) {
        target = c;
        prev->next = c->next;
        break;
      }
      prev = c, c = c->next;
    }
    if (target == nullptr)
      return;
    myscoped_lock msl(head->mu, target->mu);
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
    cl.insert(i);
  }
  cl.erase(0);
  cl.erase(99);
  cout << cl.head->val << ",size:" << cl.z << endl;
}


}


#endif //PNSEI_CURRENT_LINKEDLIST_H
