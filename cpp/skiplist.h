#pragma once

#include "henry.h"
#include <random>


// very good!!!
// http://ticki.github.io/blog/skip-lists-done-right/
// https://en.wikipedia.org/wiki/Skip_list
namespace _skiplist {
#define MaxLevel 5

typedef struct SkipListNode {
  int key;
  int value;
  int level;
  SkipListNode *next[MaxLevel];
} SkipListNode;

typedef struct SkipList {
  SkipListNode *head;
  int level;
  int length;
} SkipList;

SkipListNode *makeNode(int level, int key, int value) {
  SkipListNode *pNode = (SkipListNode *) malloc(sizeof(SkipListNode));
  pNode->key = key;
  pNode->value = value;
  pNode->level = level;
  for (int i = 0; i < MaxLevel; ++i) // every node has MaxLevel children, some of them are NULL
    pNode->next[i] = NULL;
  return pNode;
}

void initSkipList(SkipList *pSkipList) {
  if (!pSkipList)
    return;
  srand(0xdeadbeef);
  pSkipList->head = makeNode(-1, -1, -1);
  pSkipList->length = 0;
  pSkipList->level = 1;
}

int randomLevel() {
  // return rand() % MaxLevel;
  int newLevel = 1;
  while (rand() < 0.4 * RAND_MAX)
    ++newLevel;
  return min(newLevel, MaxLevel);
}

bool insertNode(SkipList *pSkipList, int searchKey, int newValue) {
  if (!pSkipList)
    return false;

  SkipListNode *update[MaxLevel] = {};////
  //FindGreaterOrEqual
  SkipListNode *cur = pSkipList->head; // insert position
  // from top to bottom
  for (int i = pSkipList->level - 1; i >= 0; i--) {
    while (cur->next[i] && cur->next[i]->key < searchKey)
      cur = cur->next[i];
    update[i] = cur;
  }
  cur = cur->next[0];
  if (cur && cur->key == searchKey) {
    cur->value = newValue;
  } else {
    int k = randomLevel();
    if (k > pSkipList->level) {
      for (int i = pSkipList->level; i < k; i++)
        update[i] = pSkipList->head; ////////
      pSkipList->level = k;
    }
    auto nn = makeNode(k, searchKey, newValue);
    for (int i = 0; i < k; ++i) {
      auto tmp = update[i]->next[i]; // insert a new node in the linked list
      update[i]->next[i] = nn;
      nn->next[i] = tmp;
    }
    pSkipList->length++;
  }
  return true;
}

SkipListNode *searchNode(SkipList *pSkipList, int searchKey) {
  if (!pSkipList or pSkipList->head)
    return NULL;

  SkipListNode *cur = pSkipList->head, *tn; // insert position
  int k = pSkipList->level;
  while (k >= 0) {
    tn = cur->next[k]; //temp biggest child node
    if (tn) {
      int ck = tn->key;
      if (ck > searchKey) {
        k--;
      } else if (ck < searchKey) {
        cur = tn;
      } else {
        return tn;
      }
    } else {
      k--;
    }
  }
  return NULL;

  /*for (int i = pSkipList->level - 1; i >= 0; --i) {
    while (pNode->next[i] && pNode->next[i]->key < searchKey)
      pNode = pNode->next[i];
  }
  pNode = pNode->next[0];
  if (pNode && pNode->key == searchKey)
    return pNode;
  return NULL;*/
}

bool deleteNode(SkipList *pSkipList, int searchKey) {
  if (!pSkipList)
    return false;

  SkipListNode *pNode = pSkipList->head;
  SkipListNode *update[MaxLevel];

  for (int i = pSkipList->level - 1; i >= 0; i--) {
    while (pNode->next[i] && pNode->next[i]->key < searchKey) {
      pNode = pNode->next[i];
    }
    update[i] = pNode;
  }

  pNode = pNode->next[0];
  if (pNode && pNode->key == searchKey) {
    for (int i = 0; i < pSkipList->level; ++i) {
      if (update[i] && update[i]->next[i] != pNode) {
        break;
      }
      update[i]->next[i] = pNode->next[i];
    }
    free(pNode);
    while (pSkipList->level > 1 &&
           pSkipList->head->next[pSkipList->level - 1] == NULL) {
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

  while (pNode->next[0]) {
    cout << pNode->next[0]->value << " " << pNode->next[0]->level << endl;
    pNode = pNode->next[0];
  }
}

int test() {

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
  cout << pNode->value << endl;
  travelList(&sl);

  SkipList list;
  initSkipList(&list);

  insertNode(&list, 10, 10);
  insertNode(&list, 2, 2);
  insertNode(&list, 5, 5);

  travelList(&list);

  pNode = searchNode(&list, 2);
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
