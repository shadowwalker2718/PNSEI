#pragma once
#include "pnsei.h"

namespace _208_ext {
#define ix(x) (x - 'a')
#define iy(y) ('a' + y)

struct node {
  bool k = false;   // k represent the end of a string
  node *n[26] = {}; // Use index to represent the current char, n mean next
  int count = 0;
};

struct trie {
  trie() { r = new node(); }
  void insert(const string &s) {
    node *cur = r;
    for (char c : s) {
      if (cur->n[ix(c)] == 0)
        cur->n[ix(c)] = new node();
      cur = cur->n[ix(c)];
    }
    cur->k = true;
  }
  bool search(const string &s) { return _search(s, 0); }
  bool start_with(const string &s) { return _search(s, 1); }
  vector<string> get_words_start_with(const string &s) {
    vector<string> re;
    node *cur = r;
    for (char c : s) {
      if (cur == 0 || cur->n[ix(c)] == 0)
        return re;
      cur = cur->n[ix(c)];
    }
    _getwords(cur, re, s);
    return re;
  }
  vector<string> get_words() {
    vector<string> re;
    _getwords(r, re, "");
    return re;
  }

  int word_count() { return _word_count(r); }

  int word_count_start_with(const string &s) {
    node *cur = r;
    for (char c : s) {
      if (cur == 0 || cur->n[ix(c)] == 0)
        return 0;
      cur = cur->n[ix(c)];
    }
    return _word_count(cur);
  }

  vector<string> fuzzy_match(const string &s) {
    vector<string> re;
    for (char c : s) {
      // TODO
    }
    return re;
  }

  void remove(const string &s) {
    node *cur = r;
    for (char c : s) {
      if (cur == 0 || cur->n[ix(c)] == 0)
        return;
      cur = cur->n[ix(c)];
    }
    if (cur)
      cur->k = false;
  }

private:
  int _word_count(node *no) {
    if (no == 0)
      return 0;
    int re = no->k ? 1 : 0;
    for (int i = 0; i < 26; ++i)
      if (no->n[i])
        re += _word_count(no->n[i]);
    return re;
  }

  void _getwords(node *no, vector<string> &re, const string &prefix) {
    if (no->k)
      re.push_back(prefix);
    for (int i = 0; i < 26; i++) {
      if (no->n[i])
        _getwords(no->n[i], re, prefix + (char)('a' + i));
    }
  }

  // the code snippet is reused many times
  bool
  _search(const string &s,
          bool partial) { // along the way to search, all nodes are not null.
    node *cur = r;
    for (char c : s) {
      if (cur == 0 || cur->n[ix(c)] == 0)
        return false;
      cur = cur->n[ix(c)];
    }
    return partial ? true : cur->k;
  }
  node *r; // root
};

void test() {
  trie tr;
  vector<string> vs = {"area", "lead", "wall", "lady", "ball"};
  for_each(vs.begin(), vs.end(), [&tr](const string &s) { tr.insert(s); });
  assert(true == tr.start_with("ar"));
  assert(true == tr.start_with("le"));
  assert(true == tr.start_with("wa"));
  assert(true == tr.start_with("la"));
  assert(true == tr.start_with("ba"));
  vector<string> re = tr.get_words_start_with("l");
  for (string &s : re)
    cout << s << endl;
  assert(5 == tr.word_count());
  assert(2 == tr.word_count_start_with("l"));
}
}
