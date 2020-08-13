#pragma once

#include "henry.h"

namespace concurrency_parallel {

struct account {
  double deposit = 0;
  mutex mu;
  bool locked = 0;
};

void transfer_money(account &from, account &to, double money) {
  lock_guard<mutex> lock1(from.mu);
  from.locked = true;
  while (!to.locked)
    this_thread::sleep_for(1s); ////
  lock_guard<mutex> lock2(to.mu);
  from.deposit -= money;
  to.deposit += money;
}

void deadlock() {
  account jack, simon;
  thread t1(transfer_money, ref(jack), ref(simon), 10.5);
  thread t2(transfer_money, ref(simon), ref(jack), 1.5);
  t1.join(), t2.join();
}

int global_int = 0;
mutex mu;
void rec() {
  if (global_int > 10)
    return;
  lock_guard<mutex> lk(mu);
  cout << "it it me: " << global_int++ << endl;
  rec();
}

void test() {
  try {
    rec();
  } catch (system_error &e) {
    cout << e.what() << endl;
  }
  deadlock();
}

} // namespace deadlock