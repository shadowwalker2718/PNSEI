#include <stdio.h>

int division_with_add_sub2(int num, int denum) {
  int res = 0;
  int r, z, pr, pz, n;
  n = num;

MY_CODE:
  r=1, z= denum, pr=1, pz=z;
  if (z <= n){
WHILE_LOOP:
    pr = r, pz = z, z += z, r += r;
    if (z<= n)
      goto WHILE_LOOP;
  }
  n = n -pz;
  res+=pr;
  if (n >= denum)
    goto MY_CODE;
  printf("%d, %d\n", res, num);
  return 0;
}

int main(){
  division_with_add_sub2(11, 2);
  return 0;
}
