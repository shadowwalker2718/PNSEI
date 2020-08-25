#include "deadlock_guaranteed.h"
#include <gtest/gtest.h>

int global_int = 0;
mutex mu;
void rec() {
  if (global_int > 10)
    return;
  lock_guard<mutex> lk(mu);
  cout << " " << global_int++;
  rec();
}

/*TEST(deadlock, transfer_money){
  concurrency_parallel::dl::deadlock();
}*/

int test_me() {
  lock_guard<mutex> g(mu);
  lock_guard<mutex> g2(mu);
  rec();
  cout << endl;
  return 0;
}
