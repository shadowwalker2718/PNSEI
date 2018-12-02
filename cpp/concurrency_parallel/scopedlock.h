//
// Created by Henry Wu on 11/22/18.
//

#ifndef PNSEI_SCOPEDLOCK_H
#define PNSEI_SCOPEDLOCK_H

#include "henry.h"

// https://stackoverflow.com/questions/20516773/stdunique-lockstdmutex-or-stdlock-guardstdmutex
// std::unique_lock has other features that allow it to e.g.: be constructed without locking
// the mutex immediately but to build the RAII wrapper (see here).
struct scoped_lock_base {
  unique_lock<mutex> ul_base; // no associated mutex

  scoped_lock_base(mutex &a) {
    unique_lock<mutex> t(a);
    //ul.swap(t);
    ul_base = move(t); // method 1
  }
};

struct myscoped_lock : public scoped_lock_base {
  unique_lock<mutex> ul;

  myscoped_lock(mutex &a_, mutex &b_) : scoped_lock_base(a_) { // cannot use ref-to-const for mutex
    unique_lock<mutex> t(b_);
    ul.swap(t); // method 2
  }
};

#endif //PNSEI_SCOPEDLOCK_H
