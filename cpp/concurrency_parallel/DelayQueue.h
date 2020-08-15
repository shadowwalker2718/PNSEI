#pragma once

#include "henry.h"

namespace _delayqueue {

struct event {
  int id;
  time_t due;
  void trigger() {
    cout << "\t\t\t | Trigger event " << id << " at " << due << endl;
  };
};

struct comp {
  bool operator()(const event &t1, const event &tconsumer) {
    return t1.due > tconsumer.due;
  };
};

priority_queue<event, vector<event>, comp> DelayQueue; // minheap
mutex mu;
condition_variable cv;

// C++: 1. cv.wait_for; 2. lock_guard and unique_lock

[[noreturn]] void consumer() {
  unique_lock<mutex> ul(mu);
  while (1) {
    while (DelayQueue.empty()) {
      cv.wait(ul);
    }
    auto tmp = DelayQueue.top();
    auto now = time(NULL);
    if (tmp.due <= now) {
      tmp.trigger();
      DelayQueue.pop();
    } else {
      cv.wait_for(ul, (tmp.due - now) * 1s); // cv.wait_for
    }
  }
}

[[noreturn]] void producer() {
  int i = 0;
  event t;
  while (1) {
    {
      lock_guard<mutex> ul(mu);
      t.id = i++;
      t.due = time(NULL) + rand() % 10; // a random timeout
      DelayQueue.push(t);
      if (DelayQueue.size() == 1)
        cv.notify_one();
      cout << "Add event " << t.id << "(" << t.due << ")\n";
    } // never hold lock when sleeping
    this_thread::sleep_for(3s);
  }
}

void producer2(const event &tsk) {
  lock_guard<mutex> ul(mu);
  DelayQueue.push(tsk);
  cv.notify_one();
}

void test() {

  cout << "producer\t\t |consumer\n";
  cout << string(60, '-') << endl;
  /*int NUMTASK = 10;
  vector<event> tsk(NUMTASK);
  for (int i = 0; i < NUMTASK; ++i) {
    tsk[i].due = time(0) + i * 3;
    tsk[i].id = i;
  }
  vector<thread> v;
  for (int i = 0; i < NUMTASK; ++i) {
    v.push_back(thread(put, ref(tsk[i])));
  }*/

  thread t_producer(producer);
  thread t_consumer(consumer);

  t_producer.join();
  t_consumer.join();

  // for (int i = 0; i < NUMTASK; ++i) v[i].join();
  // cout << "joined single producer" << endl;

  // cout << "joined producer2" << endl;

  // cout << "joined consumer" << endl;
}

} // namespace _delayqueue