//
// Created by Henry Wu on 11/28/18.
//

#ifndef PNSEI_SQRT_DOUBLE_H
#define PNSEI_SQRT_DOUBLE_H

#include "pnsei.h"

namespace _sqrt_double{

double mysqrt(double c){
  if(c < 0) return numeric_limits<double>::max();
  double h=0.0, t=c+0.25;
  while(abs(t-h)>=1e-11){
    double m=h+(t-h)/2;
    if(m*m < c){
      h=m;
    }else{
      t=m;
    }
  }
  return t;
}

void test(){
  double r;
  r=mysqrt(1.0);
  assert(abs(r-1.0)<=1e-10);
  assert(abs(mysqrt(0.03)-sqrt(0.03))<=1e-10);
  assert(abs(mysqrt(3000)-sqrt(3000))<=1e-10);
}

}

#endif //PNSEI_SQRT_DOUBLE_H
