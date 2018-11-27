//
// Created by root on 11/22/18.
//

#ifndef PNSEI_RWLOCK_H
#define PNSEI_RWLOCK_H

// https://en.cppreference.com/w/cpp/thread/shared_mutex
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2406.html#shared_mutex
// https://en.cppreference.com/w/cpp/thread/shared_lock
// https://en.cppreference.com/w/cpp/thread/unique_lock
// https://stackoverflow.com/questions/12033188/how-would-you-implement-your-own-reader-writer-lock-in-c11

#include "henry.h"

// https://en.wikipedia.org/wiki/Readers%E2%80%93writer_lock#Priority_policies !!!

namespace _concurrent_shared_mutex {
// Not posix standard
// a read write lock with writer preference!!!
// i see other implementation count reader and

// Cannot write when reading is not finished!
class rwlock {
  mutex mu;
  condition_variable cv;
  atomic<int> reader;
  atomic<bool> writer;
public:
  rwlock() {
    writer.store(false, memory_order_seq_cst);
  }

  void read_lock() {
    unique_lock ul(mu);
    while (writer)
      cv.wait(ul);
    reader++;
  }

  void read_unlock() {
    unique_lock ul(mu);
    reader--;
    if (reader == 0) // if all readers are done, notify writer
      cv.notify_all();
  }

  void write_lock() {
    unique_lock ul(mu);
    while (writer || reader > 0) // if there are other writers, or readers are not done, WAIT!
      cv.wait(ul);
    writer.store(true, memory_order_seq_cst);
  }

  void write_unlock() {
    //if(!writer) return;
    unique_lock ul(mu);
    writer.store(false, memory_order_seq_cst);
    cv.notify_all();
  }
};


struct mymutex {
  void lock() {}

  void unlock() {}
};

struct condition {
  void wait(mymutex &) {}
};

void signal() {}

void broadcast() {}

class myRWLock {
  mymutex mu;
  condition cv;
  atomic<int> readers;
  atomic<bool> writer;

  myRWLock() {
    readers = 0, writer = false;
  }

  void acquire_read() {
    mu.lock();
    while (writer)
      cv.wait(mu);
    readers++;
    mu.unlock();
  }

  void release_read() {
    mu.lock();
    readers--;
    if (readers == 0)
      signal();
    mu.unlock();
  }

  void acquire_write() {
    mu.lock();
    while (readers > 0)
      cv.wait(mu);
    writer = true;
  }

  void release_write() {
    writer = false;
    mu.unlock();
    broadcast();
  }
};

/*class my_shared_mutex {
  mutex mut_;
  condition_variable gate1_;
  condition_variable gate2_;
  unsigned state_;

  static const unsigned write_entered_ = 1U << (sizeof(unsigned) * CHAR_BIT - 1);
  static const unsigned n_readers_ = ~write_entered_;

public:

  my_shared_mutex() : state_(0) {}

// Exclusive ownership

  void lock();

  bool try_lock();

  bool timed_lock(nanoseconds rel_time);

  void unlock();

// Shared ownership

  void lock_shared();

  bool try_lock_shared();

  bool timed_lock_shared(nanoseconds rel_time);

  void unlock_shared();
};

// Exclusive ownership

void my_shared_mutex::lock() {
  //std::this_thread::disable_interruption _;
  unique_lock<mutex> lk(mut_);
  while (state_ & write_entered_)
    gate1_.wait(lk);
  state_ |= write_entered_;
  while (state_ & n_readers_)
    gate2_.wait(lk);
}

bool my_shared_mutex::try_lock() {
  unique_lock<mutex> lk(mut_, try_to_lock);
  if (lk.owns_lock() && state_ == 0) {
    state_ = write_entered_;
    return true;
  }
  return false;
}

void my_shared_mutex::unlock() {
  {
    scoped_lock<mutex> _(mut_);
    state_ = 0;
  }
  gate1_.notify_all();
}

// Shared ownership

void my_shared_mutex::lock_shared() {
  //std::this_thread::disable_interruption _;
  unique_lock<mutex> lk(mut_);
  while ((state_ & write_entered_) || (state_ & n_readers_) == n_readers_)
    gate1_.wait(lk);
  unsigned num_readers = (state_ & n_readers_) + 1;
  state_ &= ~n_readers_;
  state_ |= num_readers;
}

bool my_shared_mutex::try_lock_shared() {
  unique_lock<mutex> lk(mut_, try_to_lock);
  unsigned num_readers = state_ & n_readers_;
  if (lk.owns_lock() && !(state_ & write_entered_) && num_readers != n_readers_) {
    ++num_readers;
    state_ &= ~n_readers_;
    state_ |= num_readers;
    return true;
  }
  return false;
}

void my_shared_mutex::unlock_shared() {
  scoped_lock<mutex> _(mut_);
  unsigned num_readers = (state_ & n_readers_) - 1;
  state_ &= ~n_readers_;
  state_ |= num_readers;
  if (state_ & write_entered_) {
    if (num_readers == 0)
      gate2_.notify_one();
  } else {
    if (num_readers == n_readers_ - 1)
      gate1_.notify_one();
  }
}*/

static rwlock my_global_rwlock_var;

int func_read() {
  my_global_rwlock_var.read_lock();
  //read
  my_global_rwlock_var.read_unlock();
  return 0;
}

int func_write() {
  my_global_rwlock_var.write_lock();
  //write
  my_global_rwlock_var.write_unlock();
  return 1;
}

void test() {
  //my_shared_mutex msm;
  //shared_lock<my_shared_mutex> sl(msm);
  auto handle = async(func_read);
  handle.get();
}

}


#endif //PNSEI_RWLOCK_H
