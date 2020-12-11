//
// Created by Henry Wu on 11/24/18.
//

#ifndef PNSEI_CONCURRENT_STACK_H
#define PNSEI_CONCURRENT_STACK_H

#include "pnsei.h"

namespace _concurrent_stack{

class concurrent_stack{
  mutex mu;
  condition_variable cv;
  stack<string> stk;
  atomic<int> z;
public:
  concurrent_stack():z(0){}
  bool empty(){
    return z==0;
  }

  void push(){}
  string pop(){
    unique_lock<mutex> ul(mu);
    while(z==0){
      cv.wait(ul);
    }
  }

};



}

#endif //PNSEI_CONCURRENT_STACK_H
