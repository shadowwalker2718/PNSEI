//
// Created by Henry Wu on 11/20/18.
//

#ifndef PNSEI_745_PREFIX_AND_SUFFIX_SEARCH_H
#define PNSEI_745_PREFIX_AND_SUFFIX_SEARCH_H

#include "pnsei.h"

namespace _745{

/*
* https://leetcode.com/problems/prefix-and-suffix-search/

Given many words, words[i] has weight i.

Design a class WordFilter that supports one function, WordFilter.f(String prefix, String suffix).
It will return the word with given prefix and suffix with maximum weight. If no word exists, return -1.

Examples:
Input:
WordFilter(["apple"])
WordFilter.f("a", "e") // returns 0
WordFilter.f("b", "") // returns -1
Note:
words has length in range [1, 15000].
For each test case, up to words.length queries WordFilter.f may be made.
words[i] has length in range [1, 10].
prefix, suffix have lengths in range [0, 10].
words[i] and prefix, suffix queries consist of lowercase letters only.
*/

struct Node {
  int w;
  Node* next[27];
  Node(): w(-1) {
    fill(next, next + 27, nullptr);
  }
  Node(int w): w(w) {
    fill(next, next + 27, nullptr);
  }
};

class WordFilter {
  Node root;
  void insertTrie(Node* root, string& word, int weight) {
    Node* cur = root;
    for (auto ch : word) {
      int pos = ch - 'a';
      if (cur->next[pos] == nullptr) {
        cur->next[pos] = new Node(weight);
      }
      cur = cur->next[pos];
      cur->w = weight;
    }
  }
  int searchTrie(Node* root, string& str) {
    Node* cur = root;
    for (auto ch : str) {
      int pos = ch - 'a';
      if (cur->next[pos] == nullptr) {
        return -1;
      }
      cur = cur->next[pos];
    }
    return cur->w;
  }
  // TODO: need to free trie node
public:
  WordFilter(vector<string> words) {
    for (int i = 0; i < words.size(); ++i) {
      int len = words[i].length();
      for (int j = 0; j <= len; ++j) {
        string str = words[i].substr(len - j) + "{" + words[i];
        insertTrie(&root, str, i);
      }
    }
  }
  int f(string prefix, string suffix) {
    string str = suffix + "{" + prefix;
    return searchTrie(&root, str);
  }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */

}

#endif //PNSEI_745_PREFIX_AND_SUFFIX_SEARCH_H
