//
// Created by henry on 12/16/18.
//

#ifndef PNSEI_MY_SEMAPHORE_H
#define PNSEI_MY_SEMAPHORE_H

#include "pnsei.h"

namespace _concurrency{
class my_semaphore
{
private:
  mutex mutex_;
  condition_variable condition_;
  unsigned long count_ = 0; // Initialized as locked.

public:
  void notify() {
    lock_guard<decltype(mutex_)> lock(mutex_);
    ++count_;
    condition_.notify_one();
  }

  void wait() {
    unique_lock<decltype(mutex_)> lock(mutex_);
    while(!count_) // Handle spurious wake-ups.
      condition_.wait(lock);
    --count_;
  }

  bool try_wait() {
    lock_guard<decltype(mutex_)> lock(mutex_);
    if(count_) {
      --count_;
      return true;
    }
    return false;
  }
};

namespace _semaphore_example{

// https://austingwalters.com/multithreading-semaphores/

mutex mtx;              // mutex for critical section
condition_variable cv;  // condition variable for critical section
bool ready = false;     // Tell threads to run
int current = 0;        // current count

/* Prints the thread id / max number of threads */
void print_num(int num, int max) {
  unique_lock<mutex> lck(mtx);
  while(num != current || !ready){ cv.wait(lck); }
  current++;
  cout << "Thread: ";
  cout << num + 1 << " / " << max;
  cout << " current count is: ";
  cout << current << endl;
  /* Notify next threads to check if it is their turn */
  cv.notify_all();
}

/* Changes ready to true, and begins the threads printing */
void run(){
  unique_lock<mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

int test (){
  int thread_num = 15;
  thread threads[15];
  /* spawn thread_num threads */
  for (int id = 0; id < thread_num; id++)
    threads[id] = thread(print_num, id, thread_num);
  cout << "\nRunning " << thread_num;
  cout << " in parallel: \n" << endl;
  run(); // Allows threads to run
  /* Merge all threads to the main thread */
  for(int id = 0; id < thread_num; id++)
    threads[id].join();
  cout << "\nCompleted semaphore example!\n";
  cout << endl;
  return 0;
}
}

}


#endif //PNSEI_MY_SEMAPHORE_H
