#pragma once
#include "henry.h"
#include <random>

namespace _skiplist {
#define MaxLevel 5

typedef struct SkipListNode {
  int key;
  int value;
  int level;
  SkipListNode *forward[MaxLevel];
} SkipListNode;

typedef struct SkipList {
  SkipListNode *head;
  int level;
  int length;
} SkipList;

SkipListNode *makeNode(int level, int key, int value) {
  SkipListNode *pNode = (SkipListNode *)malloc(sizeof(SkipListNode));
  pNode->key = key;
  pNode->value = value;
  pNode->level = level;
  for (int i = 0; i < MaxLevel; ++i)
    pNode->forward[i] = NULL;
  return pNode;
}

void initSkipList(SkipList *pSkipList) {
  if (!pSkipList)
    return;
  srand(0xdeadbeef);
  SkipListNode *head = makeNode(0, 0, 0);
  if (!head)
    return;
  pSkipList->head = head;
  pSkipList->length = 0;
  pSkipList->level = 1;

  for (int i = 0; i < MaxLevel; i++)
    pSkipList->head->forward[i] = NULL;
}

int randomLevel() {
  // return rand() % MaxLevel;
  int newLevel = 1;
  while ((rand() & 0xFFFF) < (0.4 * 0xFFFF))
    ++newLevel;
  return min(newLevel, MaxLevel);
}

bool insertNode(SkipList *pSkipList, int searchKey, int newValue) {
  if (!pSkipList)
    return false;

  SkipListNode *update[MaxLevel]={};
  //FindGreaterOrEqual
  SkipListNode *cur = pSkipList->head;
  // from top to bottom
  for (int i = pSkipList->level - 1; i >= 0; i--) {
    while (cur->forward[i] && cur->forward[i]->key < searchKey)
      cur = cur->forward[i];
    update[i] = cur;
  }
  cur = cur->forward[0];
  if (cur && cur->key == searchKey) {
    cur->value = newValue;
  } else {
    int k = randomLevel();
    if (k > pSkipList->level) {
      for (int i = pSkipList->level; i < k; i++)
        update[i] = pSkipList->head;
      pSkipList->level = k;
    }
    cur = makeNode(k, searchKey, newValue);
    for (int i = 0; i < k; ++i) {
      cur->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = cur;
    }
    pSkipList->length++;
  }
  return true;
}

SkipListNode *searchNode(SkipList *pSkipList, int searchKey) {
  if (!pSkipList)
    return NULL;

  SkipListNode *pNode = pSkipList->head;
  if (!pNode)
    return NULL;

  for (int i = pSkipList->level - 1; i >= 0; --i) {
    while (pNode->forward[i] && pNode->forward[i]->key < searchKey)
      pNode = pNode->forward[i];
  }

  pNode = pNode->forward[0];
  if (pNode && pNode->key == searchKey)
    return pNode;
  return NULL;
}

bool deleteNode(SkipList *pSkipList, int searchKey) {
  if (!pSkipList)
    return false;

  SkipListNode *pNode = pSkipList->head;
  SkipListNode *update[MaxLevel];

  for (int i = pSkipList->level - 1; i >= 0; i--) {
    while (pNode->forward[i] && pNode->forward[i]->key < searchKey) {
      pNode = pNode->forward[i];
    }
    update[i] = pNode;
  }

  pNode = pNode->forward[0];
  if (pNode && pNode->key == searchKey) {
    for (int i = 0; i < pSkipList->level; ++i) {
      if (update[i] && update[i]->forward[i] != pNode) {
        break;
      }
      update[i]->forward[i] = pNode->forward[i];
    }
    free(pNode);
    while (pSkipList->level > 1 &&
           pSkipList->head->forward[pSkipList->level - 1] == NULL) {
      pSkipList->level--;
    }
    pSkipList->length--;
    return true;
  }
  return false;
}

void travelList(SkipList *pSkipList) {
  SkipListNode *pNode = pSkipList->head;
  if (!pNode)
    return;

  while (pNode->forward[0]) {
    cout << pNode->forward[0]->value << " " << pNode->forward[0]->level << endl;
    pNode = pNode->forward[0];
  }
}

int test() {

  SkipList sl;
  initSkipList(&sl);
  insertNode(&sl, 22,22);
  insertNode(&sl, 19,19);
  insertNode(&sl, 7,7);
  insertNode(&sl, 3,3);
  insertNode(&sl, 37,37);
  insertNode(&sl, 37,73);
  travelList(&sl);

  SkipList list;
  initSkipList(&list);

  insertNode(&list, 10, 10);
  insertNode(&list, 2, 2);
  insertNode(&list, 5, 5);

  travelList(&list);

  SkipListNode *pNode = searchNode(&list, 2);
  cout << pNode->value << endl;

  pNode = searchNode(&list, 10);
  cout << pNode->value << endl;

  cout << "----" << endl;
  deleteNode(&list, 2);
  travelList(&list);

  cout << "----" << endl;
  deleteNode(&list, 10);
  travelList(&list);

  cout << "----" << endl;
  deleteNode(&list, 7);
  travelList(&list);
  return 0;
}
}
