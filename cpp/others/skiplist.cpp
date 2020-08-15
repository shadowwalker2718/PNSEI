#include "skiplist.h"
#include <gtest/gtest.h>

TEST(skiplist, basic){
  using namespace _skiplist;
  SkipList sl;
  initSkipList(&sl);
  insertNode(&sl, 22, 22);
  insertNode(&sl, 19, 19);
  insertNode(&sl, 7, 7);
  insertNode(&sl, 3, 3);
  insertNode(&sl, 37, 37);
  insertNode(&sl, 11, 11);
  insertNode(&sl, 55, 55);
  insertNode(&sl, 70, 70);
  insertNode(&sl, 86, 86);
  insertNode(&sl, 98, 98);
  insertNode(&sl, 108, 108);
  insertNode(&sl, 87, 87);
  insertNode(&sl, 93, 93);
  insertNode(&sl, 137, 137);
  insertNode(&sl, 111, 111);
  insertNode(&sl, 155, 155);
  insertNode(&sl, 170, 170);
  insertNode(&sl, 186, 186);
  insertNode(&sl, 198, 198);
  insertNode(&sl, 208, 208);
  SkipListNode *pNode = searchNode(&sl, 208);
  EXPECT_EQ(208, pNode->value);
  travelList(&sl);
}

TEST(skiplist, basic2){
  using namespace _skiplist;
  SkipList list;
  initSkipList(&list);
  insertNode(&list, 10, 10);
  insertNode(&list, 2, 2);
  insertNode(&list, 5, 5);
  travelList(&list);
  auto pNode = searchNode(&list, 2);
  EXPECT_EQ(pNode->value, 2);
  pNode = searchNode(&list, 10);
  EXPECT_EQ(pNode->value, 10);
  deleteNode(&list, 2);
  travelList(&list);
  deleteNode(&list, 10);
  travelList(&list);
  deleteNode(&list, 7);
  travelList(&list);
}