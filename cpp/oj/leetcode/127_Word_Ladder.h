//
// Created by Henry Wu on 11/23/18.
//

#ifndef PNSEI_127_WORD_LADDER_H
#define PNSEI_127_WORD_LADDER_H

#include "pnsei.h"

namespace _127 {

// https://leetcode.com/problems/word-ladder/
/*
 * Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest
 * transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]

As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog", return its length 5.
 * */

// http://sde.quant365.com/graph.html#word-ladder

struct Solution { // 99%
  int ladderLength(string beginWord, string endWord, vector<string> &ws) {
    unordered_set<string> F = {beginWord},
        B = {endWord},
        next_layer,
        W(ws.begin(), ws.end());
    if (W.count(endWord) == 0) return 0;
    W.erase(endWord);
    int count = 1; //
    while (!F.empty()) {
      for (const string &w: F) {
        for (int i = 0; i < w.size(); ++i) {
          string t(w); //
          for (t[i] = 'a'; t[i] != 'z'; ++t[i]) {
            if (t[i] == w[i]) continue;
            if (B.count(t)) return count + 1;
            else if (W.count(t))
              next_layer.insert(t), W.erase(t);
          }
        }
      }
      F = next_layer, next_layer.clear(), count++;
      if (F.size() > B.size())
        swap(F, B);
    }
    return 0;
  }
};

void test(){
  VS vs={"hot","dot","dog","lot","log","cog"};
  assert(5 == Solution().ladderLength("hit", "cog", vs));
};

}

#endif //PNSEI_127_WORD_LADDER_H
