#pragma once

#include "henry.h"

namespace _linkedin {

template <uint32_t MAXCOUNT, typename T> class bounded_blocking_queue {
  queue<T> Q;

  mutex mu;
  condition_variable cv;

public:
  // producer,consumer知道什么时候睡,但不知道什么时候醒

  void produce(const T &item) {
    unique_lock<mutex> lk(mu);
    while (Q.size() == MAXCOUNT) { // spurious wake
      cv.wait(lk);
    }
    Q.push(item);
    if (Q.size() == 1)
      cv.notify_all(); // cv.notify_one();
  }

  // consumer
  T consume() {
    unique_lock<mutex> lk(mu);
    while (Q.size() == 0) {
      cv.wait(lk);
    }
    T r = Q.front();
    Q.pop();
    if (Q.size() == MAXCOUNT - 1)
      cv.notify_all(); // cv.notify_one();
    return r;
  }
};

// https://stackoverflow.com/questions/8594591/why-does-pthread-cond-wait-have-spurious-wakeups

template <typename T> class BBQ {
  int32_t MAXCOUNT;
  queue<T> Q;
  mutex mu;
  condition_variable cv;

public:
  BBQ(const BBQ &) = delete;            // noncopyable
  BBQ &operator=(const BBQ &) = delete; // nonassignable

  BBQ(int cap=10) : MAXCOUNT(cap) {}

  void put(const T &item) { // producer
    unique_lock<mutex> lk(mu);
    while (Q.size() == MAXCOUNT) { // spurious wake
      cv.wait(lk);
    }
    Q.push(item);
    lk.unlock(); // unlock before notificiation to minimize mutex contention
    if (Q.size() == 1)
      cv.notify_one();
  }

  T get() { // consumer
    unique_lock<mutex> lk(mu);
    while (Q.size() == 0) {
      cv.wait(lk);
    }
    T r = Q.front();
    Q.pop();
    lk.unlock(); // unlock before notificiation to minimize mutex contention
    if (Q.size() == MAXCOUNT - 1)
      cv.notify_one();
    return r;
  }
};

void test() {
  vector<thread> vt;
  bounded_blocking_queue<100, int> bbq;
  for (int i = 100; i >= 0; i--) {
  }
}

} // namespace _linkedin
