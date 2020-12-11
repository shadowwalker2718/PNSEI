#ifndef PNSEI_DIVISION_H
#define PNSEI_DIVISION_H
#include "pnsei.h"

namespace databricks {

// Exception:
//   Signal: SIGFPE (Arithmetic exception) INT_MIN/-1
//   Signal: SIGFPE (Arithmetic exception) 1/0
int division0(int x, int y) {
  return x/y;
}

// 并不会对计算产生影响
int division(int x, int y) {
  if (x==INT_MIN) throw exception();
  if (x<0) return -division(-x, y);
  if (y<0) return -division(x, -y);
  if (y==0) throw exception();
  int r = 0;
  while (x >= y) { // 10, 2 o(N) but N<32
    int z = y, a = 1;
    while (z <= x) { // o(N)
      z <<= 1, a <<= 1;
    } // 16
    r += a >> 1;
    x -= z >> 1;
  }
  return r;
}

int division2(int x, int y) {
  int r = 0;
  long z = long(y) << 32;
  long a = long(1) << 32;
  while (x >= y) { // 11, 2
    while (z > x) {
      z >>= 1, a >>= 1;
    } // 16
    r += a;
    x -= z;
  }
  return r;
}

// recursive way
int division3(int x, int y) {
  int r = 0;
run_division3:
  if (x >= y) { // 10, 2 o(N) but N<32
    int z = y, a = 1;
    while (z <= x) { // o(N)
      z <<= 1, a <<= 1;
    } // 16
    r += a >> 1;
    x -= z >> 1;
    r += division3(x, y);
  }
  return r;
}

int division4(int x, int y) {
  int r = 0;
run_division4:
  if (x >= y) { // 10, 2 o(N) but N<32
    int z = y, a = 1;
    while (z <= x) { // o(N)
      z <<= 1, a <<= 1;
    } // 16
    r += a >> 1;
    x -= z >> 1;
    goto run_division4;
  }
  return r;
}

// x/y
int division_with_add_sub(int x, int y) {
  if ((x^y) < 0){
    return x<0?-division_with_add_sub(-x,y):-division_with_add_sub(x,-y);
  }
  if (x<y) return 0;
  int r=1, z=y, pr=1, pz=z;
  while(z <= x)
    pr = r, pz = z, z += z, r += r;
  pr += division_with_add_sub(x-pz, y);
  return pr;
}

// x divided by y, returns: {quotient, reminder}
pair<int,int> division_with_add_sub2(int num, int denum) {
  int res = 0;
MY_CODE:
  if ((num ^ denum) < 0){
    auto res = num <0?division_with_add_sub2(-num, denum):division_with_add_sub2(num,-denum);
    return {-res.first, -res.second};
  }
  if (num < denum) return {0, num};

  int r=1, z= denum, pr=1, pz=z;
  if (z <= num){
WHILE_LOOP:
    pr = r, pz = z, z += z, r += r;
    if (z<= num)
      goto WHILE_LOOP;
  }
WHILE_LOOP_END:
  num = num - pz;
  res += pr;
  if (num >= denum)
    goto MY_CODE;

  return {res, num};
}

void test(){
  assert(division_with_add_sub(11,2) == 5);
  assert(division_with_add_sub(8,2) == 4);
  assert(division4(11, 2) == division0(11,2));
  assert(division3(11, 2) == division0(11,2));
  assert(division3(11, 2) == division(11,2));
  assert(division2(11, 2) == division0(11,2));

  // Corner Case
  assert(division(-11, 2) == division0(-11, 2));
  assert(division(INT_MIN, 0) == division0(INT_MIN, 0));
  assert(division0(INT_MIN, -1) == division(INT_MIN, -1));
}

} // namespace databricks

#endif // PNSEI_DIVISION_H
