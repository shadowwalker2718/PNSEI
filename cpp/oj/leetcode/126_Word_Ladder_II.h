//
// Created by Henry Wu on 11/23/18.
//

#ifndef PNSEI_126_WORD_LADDER_II_H
#define PNSEI_126_WORD_LADDER_II_H

#include "pnsei.h"
// http://sde.quant365.com/graph.html#word-ladder-ii
namespace _126 {
/*
  Given two words (beginWord and endWord), and a dictionary's word list,
  find all shortest transformation sequence(s) from beginWord to endWord, such that:

  Only one letter can be changed at a time
  Each transformed word must exist in the word list.
  Note that beginWord is not a transformed word.
  Note:

  Return an empty list if there is no such transformation sequence.
  All words have the same length.
  All words contain only lowercase alphabetic characters.
  You may assume no duplicates in the word list.
  You may assume beginWord and endWord are non-empty and are not the same.

  Example 1:
  Input:
  beginWord = "hit",
  endWord = "cog",
  wordList = ["hot","dot","dog","lot","log","cog"]
  Output:
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

  Example 2:
  Input:
  beginWord = "hit"
  endWord = "cog"
  wordList = ["hot","dot","dog","lot","log"]
  Output: []
  Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
 * */

class Solution {//Bidirectional BFS+DFS.Runtime:76 ms.Your runtime beats 97.94%...
  unordered_map<string, unordered_set<string>> sucessors; // CLRS 601, 647, 685
#define CONNECT(s, t, b) sucessors[b?s:t].insert(b?t:s)

  // forward用来表示方向forward, build path的时候用
  bool bfs_recursive(USS &F, USS &B, bool is_forward, USS &W) {
    if (F.empty() || B.empty()) return false;
    if (F.size() > B.size()) // always do bfs with less nodes
      return bfs_recursive(B, F, !is_forward, W);
    for (const string &s : F) W.erase(s);
    for (const string &s : B) W.erase(s);
    USS next_layer;
    bool isConnected = false;
    for (const string &word : F) {
      for (int i = 0; i < word.size(); i++) {
        string str(word);
        for (str[i] = 'a'; str[i] <= 'z'; str[i]++) {
          if (word[i] != str[i])
            if (B.count(str)) {
              isConnected = true;
              CONNECT(word, str, is_forward);
            } else if (!isConnected && W.count(str)) { ////
              next_layer.insert(str);
              CONNECT(word, str, is_forward);
            }
        }
      }
    }
    if (isConnected)
      return true;
    else
      return bfs_recursive(next_layer, B, is_forward, W);
  }

  bool bfs(string& beginWord, string& endWord, bool is_forward, USS &W) {
    USS F = {beginWord}, B = {endWord};
    W.erase(beginWord), W.erase(endWord);
    USS next_layer;
    while(!F.empty()){
      bool isConnected = false;
      for (const string &word : F) {
        for (int i = 0; i < word.size(); i++) {
          string str(word);
          for (str[i] = 'a'; str[i] <= 'z'; str[i]++) {
            if (word[i] != str[i])
              if (B.count(str)) {
                isConnected = true;
                CONNECT(word, str, is_forward);
                W.erase(str);
              } else if (W.count(str) && !isConnected) { ////
                next_layer.insert(str);
                CONNECT(word, str, is_forward);
                W.erase(str);
              }else{}//pass
          }
        }
      }
      if (isConnected)
        return true;
      //if(next_layer.empty())
      //  return false;
      F=next_layer, next_layer.clear();
      if (F.size() > B.size()) // always do bfs with less nodes
        swap(F, B), is_forward=!is_forward;
    }
    return false;
  }

  void dfs(VVS &r, vector<string> &path, const string &curWord, string &endWord) {
    path.push_back(curWord);
    if (curWord == endWord){
      r.push_back(path);
    }else{
      for (const string& nextWord : sucessors[curWord])
        dfs(r, path, nextWord, endWord);
    }
    path.pop_back();
  }

public:
  VVS findLadders(string beginWord, string endWord, VS &v) {
    VVS r;
    USS W(v.begin(), v.end()), F = {beginWord}, B = {endWord};
    if(!W.count(endWord))
      return r;
    if (bfs_recursive(F, B, true, W)) {
      vector<string> path;
      dfs(r, path, beginWord, endWord);
    }
    return r;
  }
  VVS findLadders2(string beginWord, string endWord, VS &v) {
    VVS r;
    USS W(v.begin(), v.end());
    if(!W.count(endWord))
      return r;
    if (bfs(beginWord, endWord, true, W)) {
      vector<string> path;
      dfs(r, path, beginWord, endWord);
    }
    return r;
  }
};

void test() {
  VS vs = {"hot", "dot", "dog", "lot", "log", "cog"};
  assert(2 == Solution().findLadders("hit", "cog", vs).size());
  assert(2 == Solution().findLadders2("hit", "cog", vs).size());
  vs={"hot","dot","dog","lot","log"};
  assert(0 == Solution().findLadders("hit", "cog", vs).size());
};

}


#endif //PNSEI_126_WORD_LADDER_II_H
