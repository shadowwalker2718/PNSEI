//
// Created by root on 11/16/18.
//

#ifndef PNSEI_RATE_LIMITER_TOKEN_BUCKET_H
#define PNSEI_RATE_LIMITER_TOKEN_BUCKET_H

#include "henry.h"

namespace _uber_rate_limiter {
// Design and develop an implementation of a rate limiter.
// The only required configuration parameter is the allowed rate.
// The rate is defined as "allowed requests per second".
// The implementation should return true for any call that is within the given rate, and false otherwise.
//    boolean isPermitted();

// config: 2 rps
// 0.2s ... r.isPermitted() -> true
// 0.3s ... r.isPermitted() -> true
// 0.4s ... r.isPermitted() -> false
// ... -> false
// 1.1s ... r.isPermitted() -> false
// 1.2s ... r.isPermitted() -> true
// 1.21s... r.isPermitted() -> false

// bool isPermitted(callerId)
// bool isPermitted()

#define current_time() time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count()

class TokenBucket {
  int tokenPerSecond;
  long timestamp;

  double capacity;
  double tokens;
public:
  TokenBucket(int rps) {
    capacity = tokenPerSecond = rps;
    tokens = rps;
    timestamp = current_time();//time(NULL);

  }

  bool isPermitted() {
    long now = current_time();
    tokens += (now - timestamp) * tokenPerSecond;
    timestamp = now;
    if (tokens > capacity)
      tokens = capacity; // to avoid burst
    if (tokens < 1)
      return false;
    tokens--;
    return true;
  }
};

using callerId=int;

class TokenBucketForCaller {
  int tokenPerSecond;
  long timestamp;

  double tokens;
  double capacity;

  map<callerId, pair<double, long>> m;// map of caller to his tokenbuket info {token, timestamp}
public:
  TokenBucketForCaller(int rps) {
    capacity = tokenPerSecond = rps;
    tokens = rps; // give it some initial token, could be 0 too
    timestamp = current_time();
  }

  bool isPermitted(callerId id) {
    long now = current_time();
    m[id].first += (now - m[id].second) * tokenPerSecond;
    m[id].second = now;
    m[id].first = min(m[id].first, capacity);
    if (m[id].first < 1)
      return false;
    m[id].first--;
    return true;
  }
};


int test() {
  cout << __FILE__ << ", " << __FUNCTION__ << endl;
  TokenBucket tb(2);
  int k = 1024;
  bitset<1024> bs;
  while (k-- > 512)
    tb.isPermitted() ? bs.set(k) : bs.reset(k);
  this_thread::sleep_for(1s);
  assert(bs.count() == 2);
  while (k--)
    tb.isPermitted() ? bs.set(k) : bs.reset(k);
  cout << bs.count() << endl;
  assert(bs.count() == 4);
  return 0;
}
}


/*
#include <iostream>
// Stream
#include <fstream>
#include <iostream>

// STL
#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
#include <forward_list>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Memory Management
#include <memory>


using namespace std;

// Design and develop an implementation of a rate limiter.
// The only required configuration parameter is the allowed rate.
// The rate is defined as "allowed requests per second".
// The implementation should return true for any call that is within the given rate, and false otherwise.
//    boolean isPermitted();

// config: 2 rps
// 0.2s ... r.isPermitted() -> true
// 0.3s ... r.isPermitted() -> true
// 0.4s ... r.isPermitted() -> false
// ... -> false
// 1.1s ... r.isPermitted() -> false
// 1.2s ... r.isPermitted() -> true
// 1.21s... r.isPermitted() -> false

// isPermitted(callerId)

using callerId=int;
using node= pair<long, int>;
class TokenBucket{
  int capacity;
  int tokenPerSecond;

  double tokens;
  long timestamp;

  mutex mu;
  map<callerId, pair<double, long>> m;// map of caller to his tokenbuket info



  //priority_queue<node> pq; //min heap
  //int pq_cap=10000;

public:
  TokenBucket(int rps, TimeUnit unit){
    capacity=tokenPerSecond=rps;//  second (int)(System.currentTimeMillis()/unit.toSeconds(1L));
    tokens = 0.0;
    timestamp=time(NULL);//System.currentTimeMillis();
  }

  void cleanup(){
    long now=time(NULL);//System.currentTimeMillis()  //unit=ms
    lock_guard<mutex> lg(mu);
    auto it=m.begin();
    while(it!=m.end()){
      if(now - it->second->second > THRSHOLD_VALUE) //timestamp
        it=m.erase(it);// return the next iterator after erase
      else
        it++;
    }
  }


  bool isPermitted(callerId id){

    lock_guard<mutex> lg(mu); // unique_lock<mutex> ul(mu);

    long now=time(NULL);//System.currentTimeMillis()  //unit=ms
    m[id].first += (now-m[id].second)*tokenPerSecond / 1000.0;
    m[id].second = now;
    m[id].first=max(m[id].first, capacity);

    //
    //pq.emplace(now, callerid);


    if(m[id].first<1)
      return false;
    m[id].first--;
    return true;
  }

  bool isPermitted(){
    long now=time(NULL);//System.currentTimeMillis()  //unit=ms

    // 300
    // 600 - 300 = 300 * 2 = 600 / 1000. = 0.6
    // 900 - 600 = 300

    // rps: 100 call rate: 2000 rps
    //

    tokens += (now-timestamp)*tokenPerSecond;// / 1000.0;
    timestamp = now;
    tokens=max(tokens, capacity);
    if(tokens<1) return false;
    tokens--;
    return true;
  }

};

int main() {
  cout << "Henry" << endl;
  return 0;
}
*/
#endif //PNSEI_RATE_LIMITER_TOKEN_BUCKET_H
