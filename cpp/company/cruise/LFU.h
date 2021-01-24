#pragma once

#include "pnsei.h"

namespace _lfu {
#define LFUKEY int

// LFU - Least Frequently Used
class FreqNode {
public:
  int freq;
  // We use a SET in lieu of a linked list for storing elements with the same
  // access frequency for simplicity of implementation. HASH SET structure
  // which holds the keys of such elements that have the same access frequency.
  // Its insertion, lookup and deletion runtime complexity is O(1).
  unordered_set<LFUKEY> items;

  FreqNode(int f) { this->freq = f; }
};

// LFU - Least Frequently Used Cache Algorithm
// 1 Linked List + 1 Set + 1 Hash
// O(1) for all: Insert, Delete and Lookup
class LFUCache {
public:
  list<FreqNode *> freqNodes;
  // key   : item (key of element)
  // value : point to its parent freqNode.
  //         Those nodes with the same access frequency share a single parent.
  unordered_map<LFUKEY, list<FreqNode *>::iterator> key_to_freqNodes_iter;


  FreqNode *__createNode(int freq, list<FreqNode *>::iterator next) {
    FreqNode *newNode = new FreqNode(freq);
    freqNodes.insert(next, newNode);
    return newNode;
  }

  void __deleteNode(list<FreqNode *>::iterator it) {
    freqNodes.erase(it);
  }

public:
  LFUCache() {}

  ~LFUCache() {
    for (auto it = freqNodes.begin(); it != freqNodes.end(); it++)
      delete (*it);
  }

  // Access (fetch) an element from the LFU cache,
  // simultaneously incrementing its usage count.
  // Assuming the element(key) already exists beforehand.
  // O(1)
  void access(LFUKEY key) {
    if (!key_to_freqNodes_iter.count(key)) {
      // not exist
      return;
    }
    list<FreqNode *>::iterator nodeIt = key_to_freqNodes_iter[key];
    int freqNow = (*nodeIt)->freq;

    list<FreqNode *>::iterator nextNodeIt = nodeIt;
    nextNodeIt++;
    if (nextNodeIt == freqNodes.end() || (*nextNodeIt)->freq != (freqNow + 1)) {
      __createNode(freqNow + 1, nextNodeIt);
    }
    nextNodeIt = nodeIt;
    nextNodeIt++;
    key_to_freqNodes_iter[key] = nextNodeIt;
    (*nextNodeIt)->items.insert(key);

    (*nodeIt)->items.erase(key);
    if ((*nodeIt)->items.empty()) {
      __deleteNode(nodeIt);
    }
  }

  // Insert a NEW element.
  // You must make sure no existing element(key) before calling this.
  // O(1)
  void insert(LFUKEY key) {
    // if (freqNodes.empty() || (*(freqNodes.begin()))->freq != 1) {
    if (freqNodes.empty() || freqNodes.front()->freq != 1) {
      // FreqNode* newNode = new FreqNode(1);
      // freqNodes.insert(freqNodes.begin(), newNode);
      freqNodes.push_front(new FreqNode(1));
    }
    auto nodeIt = freqNodes.begin();
    (*nodeIt)->items.insert(key);
    key_to_freqNodes_iter[key] = nodeIt;
  }

  // Look up an item with key, return its usage count
  // O(1)
  int getFreq(LFUKEY key) {
    if (key_to_freqNodes_iter.count(key)==0)
      return -1;
    if (key_to_freqNodes_iter.find(key) == key_to_freqNodes_iter.end()) {
      // error out
      return -1;
    }
    return (*key_to_freqNodes_iter[key])->freq;
  }

  // Fetches an item with the least usage count (the least frequently used item)
  // in the cache
  // O(1)
  int getLFUItem() {
    if (freqNodes.empty()) {
      // error out
      return -1;
    }
    return (*freqNodes.begin())->freq;
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEST Program
// Test data from Paper
void generateTestData(LFUCache &lfu) {
  vector<int> keys = {'a', 'b', 'c', 'x', 'y', 'z'};
  for (int i = 0; i < 6; i++) {
    lfu.insert(keys[i]);
  }
  lfu.access('a');
  for (int i = 1; i < 3; i++) {
    lfu.access('z');
  }
  for (int i = 1; i < 5; i++) {
    lfu.access('b');
  }
  for (int i = 1; i < 9; i++) {
    lfu.access('c');
  }
}

void printFreq(LFUCache &lfu) {
  for (auto it = lfu.freqNodes.begin(); it != lfu.freqNodes.end(); it++) {
    cout << "Freq = " << (*it)->freq << ": ";
    for (auto iIt = (*it)->items.begin(); iIt != (*it)->items.end(); iIt++) {
      cout << (char) *iIt << " ";
    }
    cout << endl;
  }
}

int test(void) {
  LFUCache lfu;
  generateTestData(lfu);
  printFreq(lfu);
  cout << endl;
  cout << "Accessing z" << endl;
  lfu.access('z');
  printFreq(lfu);

  cout << endl;
  cout << "Least Frequently Used : " << lfu.getLFUItem() << endl;
  cout << endl;
  cout << "Query c's Freq : " << lfu.getFreq('c') << endl;
  cout << "Query z's Freq : " << lfu.getFreq('z') << endl;
  cout << "Accessing z again" << endl;
  lfu.access('z');
  cout << "Query z's Freq again: " << lfu.getFreq('z') << endl;
  printFreq(lfu);
  return 0;
}
}