#ifndef PNSEI_SET_TIMEOUT_H
#define PNSEI_SET_TIMEOUT_H
#include "henry.h"
#include <sys/time.h>

namespace js_timeout {

struct event {
  int id;
  time_t due;
  function<void ()> f;
  bool operator<(const event& b) const {
    return due < b.due;
  }
  bool operator<(const event* b) const {
    return due < b->due;
  }
  event(int id_, time_t t_, const function<void ()>& f_){
    id = id_;
    due = t_;
    f = f_;
  }
  event(){}
};

struct comp{
  bool operator()(const event& a, const event& b){
    return a.due < b.due;
  }
};

struct DelayQueue{
  mutex mu;
  condition_variable cv;

  set<event> rbTree; // RED BLACK TREE
  map<int, event> m;
  int id = 0;

  time_t now(){
    struct timeval tp{};
    gettimeofday(&tp, nullptr);
    return tp.tv_sec * 1000 + tp.tv_usec / 1000;
  }

  // O(logN)
  int set_timeout(time_t due_, const function<void()>& f_){
    event e= {id, now() + due_, f_};
    lock_guard<mutex> ug(mu);
    //pick up lock when daemon is sleeping, or not running
    rbTree.insert(e);
    m[id] = e;
    cv.notify_one();
    return id++;
  }

  // O(logN)
  void clear(int id_){
    lock_guard<mutex> ul(mu);
    rbTree.erase(m[id_]);
    m.erase(id_);
  }

  [[noreturn]] //hidden from user
  void daemon(){
    unique_lock<mutex> ul(mu);
    while(true){
      while(rbTree.empty()){
        cv.wait(ul); // get lock after wake up, release lock when sleeping
      }
      auto tmp = *rbTree.begin();
      auto now_ = now();
      if(tmp.due <= now_){
        tmp.f(); // execute the function
        rbTree.erase(tmp);
        m.erase(tmp.id);
      } else {
        cv.wait_for(ul, (tmp.due - now_) * 1ms);
      }
    }
  }
};




}


#endif // PNSEI_SET_TIMEOUT_H
