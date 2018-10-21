#include "henry.h"

int global_int = 0;
mutex mu; 
void rec() {
  if (global_int > 10) return;
  lock_guard<mutex> lk(mu);
  cout << " " << global_int++;
  rec();
}


int main(){
  lock_guard<mutex> g(mu);
  lock_guard<mutex> g2(mu);
  rec();
  cout<<endl;
  return 0;
}
