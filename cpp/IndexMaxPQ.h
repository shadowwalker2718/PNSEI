#pragma once

#include "henry.h"

namespace _indexheap {

#define PAR(i) ((i - 1) >> 1) // 2n-2
#define LEF(i) ((i << 1) + 1) // 2n+1, 1->3, 1->4
#define RIG(i) ((i << 1) + 2) // 2n+2, 2->5, 2->6

struct index_priority_queue {
  vector<int> volumes; // 100 items
  unordered_map<int, string> index2ticker;
  unordered_map<string, int> ticker2index;

  int size = 0;

  index_priority_queue(int hsize = 100) { volumes.resize(hsize); }

  void push(string s, int v) { // O(LogN)
    volumes[size] = v;
    index2ticker[size] = s;
    ticker2index[s] = size;
    int cindex = size;
    int pindex = PAR(size);
    while (pindex >= 0 && volumes[pindex] < volumes[cindex]) {
      __swap(cindex, pindex); // swap with its parent
      cindex = pindex;
      pindex = PAR(pindex);
    }
    ++size;
  }

  // ix - index1, iy - index2
  void __swap(int ix, int iy) {
    std::swap(volumes[ix], volumes[iy]);
    std::swap(ticker2index[index2ticker[ix]], ticker2index[index2ticker[iy]]);
    std::swap(index2ticker[ix], index2ticker[iy]);
  }

  // update can be decrease or increase ??
  void update(string ticker, int new_volume) { // O(LogN)
    if (ticker2index.find(ticker) == ticker2index.end()) {
      push(ticker, new_volume);
      return;
    }
    int cur_idx = ticker2index[ticker]; // current index
    volumes[cur_idx] = new_volume;
    // 1. increment - swap with its parent (sift up)
    int pindex = PAR(cur_idx);
    while (pindex >= 0 && volumes[pindex] < volumes[cur_idx]) { // LogN
      __swap(cur_idx, pindex);
      cur_idx = pindex;
      pindex = PAR(pindex);
    }
    // 2. decrement - swap with the bigger of its children (sift down)
    int greater_lc_rc = -1;
    while (1) { // LogN
      int lc = LEF(cur_idx), rc = RIG(cur_idx);
      if (rc < size) {
        greater_lc_rc = (volumes[lc] > volumes[rc]) ? lc : rc;
      } else if (rc == size) {
        greater_lc_rc = lc;
      } else
        break;
      if (greater_lc_rc > 0 && volumes[cur_idx] < volumes[greater_lc_rc]) {
        __swap(cur_idx, greater_lc_rc);
        cur_idx = greater_lc_rc;
      } else
        break;
    }
  }

  // Get topK from heap with help of a new size-k heap in O(KLogK)
  void topK(int k) { // O(KLogK) where K==10
    vector<pair<string, int>> vp;
    priority_queue<pair<int, int>> pq; // pair of {volume, index}
    pq.push({volumes[0], 0});
    while (k-- && !pq.empty()) {
      auto pr = pq.top();
      pq.pop();
      vp.emplace_back(index2ticker[pr.second], volumes[pr.second]);
      int lc = LEF(pr.second), rc = RIG(pr.second);
      if (lc < size)
        pq.push(pair<int, int>({volumes[lc], lc})); // LogK
      if (rc < size)
        pq.push(pair<int, int>({volumes[rc], rc}));
    }
    for_each(vp.begin(), vp.end(), [](const pair<string, int> &p) {
      if (p.first.empty())
        return;
      cout << p.first << "-" << p.second << endl;
    });
  }
};

struct stock {
  string ticker;
  int volume;
};

class index_heap {
  vector<stock> stocks; // heap core data, which is basically a graph array
  unordered_map<string, int> ticker_to_index;

  void __swap(int x, int y) {
    swap(ticker_to_index[stocks[x].ticker], ticker_to_index[stocks[y].ticker]);
    swap(stocks[x], stocks[y]);
  }

  void __sift_up(int idx) { // iterative
    if (idx >= stocks.size())
      return;
    int pidx = PAR(idx);
    while (pidx >= 0 && stocks[pidx].volume < stocks[idx].volume) {
      __swap(idx, pidx);
      idx = pidx, pidx = PAR(idx);
    }
  }

  void __sift_down(int idx) { // recursive
    if (idx >= stocks.size())
      return;
    int lchild = 2 * idx + 1, rchild = 2 * idx + 2;
    if (stocks.size() - 1 >= rchild) {
      if (stocks[lchild].volume > stocks[rchild].volume) {
        __swap(idx, lchild);
        __sift_down(lchild);
      } else {
        __swap(idx, rchild);
        __sift_down(rchild);
      }
    } else if (stocks.size() - 1 >= lchild) {
      __swap(idx, lchild);
      __sift_down(lchild);
    } else
      return;
  }

public:
  void push(const stock &s) {
    stocks.push_back(s);
    ticker_to_index[s.ticker] = stocks.size() - 1;
    __sift_up(stocks.size() - 1);
  }

  void update(const string &t, int new_vol) {
    int vol = stocks[ticker_to_index[t]].volume;
    if (new_vol == vol)
      return;
    if (new_vol > vol)
      increase_volume(t, new_vol - vol);
    else
      increase_volume(t, vol - new_vol);
  }

  void increase_volume(const string &t, int vol) {
    stocks[ticker_to_index[t]].volume += vol;
    __sift_up(ticker_to_index[t]);
  }

  void decrease_volume(const string &t, int vol) {
    stocks[ticker_to_index[t]].volume -= vol;
    __sift_down(ticker_to_index[t]);
  }

  vector<stock> topK(int k) {
    vector<stock> r;
    if (stocks.empty())
      return r;
    auto comp = [&](stock &s1, stock &s2) {
      return stocks[ticker_to_index[s1.ticker]].volume <
             stocks[ticker_to_index[s2.ticker]].volume;
    };
    priority_queue<stock, vector<stock>, decltype(comp)> tmpQ(comp); //!!
    tmpQ.push(stocks[0]);
    while (k-- && !tmpQ.empty()) {
      stock tmp = tmpQ.top();
      tmpQ.pop();
      r.push_back(tmp);
      int lchild = 2 * ticker_to_index[tmp.ticker] + 1,
          rchild = 2 * ticker_to_index[tmp.ticker] + 2;
      if (lchild < stocks.size())
        tmpQ.push(stocks[lchild]);
      if (rchild < stocks.size())
        tmpQ.push(stocks[rchild]);
    }
    return r;
  }
};

int test() {
  index_priority_queue h;
  vector<pair<string, int>> data = {
      {"FB", 102},   {"GOOG", 101}, {"AMZ", 103},  {"IBM", 100},  {"UB", 105},
      {"LNKD", 104}, {"BIDU", 106}, {"BBG", 210},  {"MSFT", 321}, {"UBER", 268},
      {"YHOO", 12},  {"AAPL", 234}, {"TWTR", 160}, {"EBAY", 89}};
  for (auto &pr : data)
    h.push(pr.first, pr.second);
  h.topK(20);
  cout << "******************" << endl;
  h.topK(10);
  cout << "******************" << endl;
  h.update("FB", 2500);
  h.topK(3);
  cout << "******************" << endl;
  h.update("FB", 20);
  h.topK(3);
  cout << "******************" << endl;
  h.update("BBG", 2000);
  h.topK(3);
  cout << "******************" << endl;
  return 0;
}

void test2() {
  index_heap ih;
  vector<stock> data = {
      {"FB", 102},   {"GOOG", 101}, {"AMZ", 103},  {"IBM", 100},  {"UB", 105},
      {"LNKD", 104}, {"BIDU", 106}, {"BBG", 210},  {"MSFT", 321}, {"UBER", 268},
      {"YHOO", 12},  {"AAPL", 234}, {"TWTR", 160}, {"EBAY", 89}};
  for (auto &pr : data)
    ih.push(pr);
  auto r = ih.topK(5);
  for (auto s : r) {
    cout << s.ticker << "-" << s.volume << endl;
  }
  cout << "******************" << endl;
  ih.increase_volume("FB", 2500 - 102);
  r = ih.topK(3);
  for (auto s : r) {
    cout << s.ticker << "-" << s.volume << endl;
  }
  cout << "******************" << endl;
}
}
