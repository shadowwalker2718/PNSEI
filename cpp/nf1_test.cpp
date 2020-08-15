#include <gtest/gtest.h>
#include "nf.h"

void hello(){
  cout << "hello" << ", " << time(0) << endl;
}
void hello1(){
  cout << "hello1" << ", " << time(0) << endl;
}
void hello2(){
  cout << "hello2" << ", " << time(0) << endl;
}

TEST(nf, timeout1){
  using namespace js_timeout;
  DelayQueue dq;
  int id = dq.set_timeout(1000, hello);
  EXPECT_TRUE(dq.rbTree.size()==1);
  dq.clear(id);
  EXPECT_TRUE(dq.rbTree.size()==0);
}

TEST(nf, timeout2){
  using namespace js_timeout;
  DelayQueue dq;
  int id1 = dq.set_timeout(1000, hello);
  EXPECT_TRUE(id1==0);
  dq.clear(id1);
  EXPECT_TRUE(dq.rbTree.size()==0);
  int id2 = dq.set_timeout(1000, hello);
  EXPECT_TRUE(id2==1);
}

void consume(js_timeout::DelayQueue& dq){
  dq.daemon();
}

TEST(nf, timeout3){
  using namespace js_timeout;
  DelayQueue dq;
  thread consumer(consume, ref(dq));
  cout << "time:" << time(0) << endl;
  dq.set_timeout(5000, hello);
  dq.set_timeout(3000, hello1);
  dq.set_timeout(2000, hello2);
  this_thread::sleep_for(100s);
}


TEST(nf, timeout4){
  using namespace js_timeout;
  DelayQueue dq;
  int id = dq.set_timeout(5000, hello);
  EXPECT_TRUE(id == 0);
  int id1 = dq.set_timeout(3000, hello1);
  EXPECT_TRUE(id1 == 1);
  int id2 = dq.set_timeout(2000, hello2);
  EXPECT_TRUE(id2 == 2);
  auto it = dq.rbTree.begin();
  //cout << it->id << endl;
  EXPECT_TRUE(it->id == id2);
  dq.clear(id2);
  it = dq.rbTree.begin();
  EXPECT_TRUE((*it).id == id1);
  dq.clear(id1);
  it = dq.rbTree.begin();
  EXPECT_TRUE((*it).id == id);
}