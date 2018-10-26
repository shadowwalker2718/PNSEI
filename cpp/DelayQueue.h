#pragma once

#include "henry.h"

namespace _delayqueue {

struct event {
  int id;
  time_t due;
  void remind() {
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

void consumer() {
  unique_lock<mutex> ul(mu);
  while (1) {
    while (DelayQueue.empty()) {
      cv.wait(ul);
    }
    auto tmp = DelayQueue.top();
    auto now = time(NULL);
    if (tmp.due <= now) {
      tmp.remind();
      DelayQueue.pop();
    } else {
      cv.wait_for(ul, (tmp.due - now) * 1s);
    }
  }
}

void producer() {
  int i = 0;
  event t;
  while (1) {
    {
      lock_guard<mutex> ul(mu);
      t.id = i++;
      t.due = time(NULL) + rand() % 10;
      DelayQueue.push(t);
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

  thread tproducer(producer);
  thread tconsumer(consumer);
  tproducer.join();
  tconsumer.join();

  // for (int i = 0; i < NUMTASK; ++i) v[i].join();
  // cout << "joined single producer" << endl;

  // cout << "joined producer2" << endl;

  // cout << "joined consumer" << endl;
}

} // namespace _delayqueue