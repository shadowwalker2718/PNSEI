#pragma once
#include "henry.h"
#include <mutex> // For std::unique_lock
#include <numeric>
#include <shared_mutex>

namespace _concurrent_hashmap {

int hash(int i) { return i * 3 % 8; }

struct hashentry {
  int k;
  double v;
  hashentry *next = 0;
  int ha;
  hashentry() : k(0), v(0), ha(0) {}
  hashentry(int k_, double v_, int ha_ = 0) : k(k_), v(v_), ha(ha_) {}
};

// single thread hash map by chaining
class hmap {
  array<hashentry, 8> p; // 注意bucket里面是一个empty slot
public:
  double get(int k) {
    int ha = hash(k);
    auto c = p[ha].next;
    while (c) {
      if (c->k == k)
        return c->v;
      c = c->next;
    }
    return NAN;
  }
  void put(int k, double v) {
    int ha = hash(k);
    auto t = new hashentry(k, v);
    auto c = p[ha].next;
    if (c == 0) {
      p[ha].next = t;
    } else {
      while (c->next)
        c = c->next;
      c->next = t;
    }
  }
  void erase(int k) {
    int ha = hash(k);
    auto hd = p[ha].next;
    if (hd == 0)
      return;
    auto pv = &p[ha];
    while (hd) {
      if (hd->k == k) {
        pv->next = hd->next;
        delete hd;
        return;
      }
      pv = hd, hd = hd->next;
    }
  }
  void loop() {
    for (auto e : p) {
      if (e.next) {
        auto c = e.next;
        do {
          cout << c->k << " -> " << c->v << ",";
          c = c->next;
        } while (c);
        cout << endl;
      }
    }
  }
};

void test() {
  vector<int> vi(100);
  iota(vi.begin(), vi.end(), 1);
  hmap hm;
  for (int i : vi)
    hm.put(i, i * 0.23);
  for (int i : vi) {
    if (hm.get(i) != i * 0.23)
      cout << "ERROR\n";
    if (i % 35 != 1)
      hm.erase(i);
  }
  hm.loop();
}

/////////////////////////////////////////////////////////////////////
struct seg {
  shared_mutex mu;
  hashentry *next;
};

// int -> double
class chmap {
  array<seg, 8> p;

public:
  double get(int k) {
    int ha = hash(k);
    shared_lock<shared_mutex> lock(p[ha].mu);
    auto c = p[ha].next;
    while (c) {
      if (c->k == k)
        return c->v;
      c = c->next;
    }
    return NAN;
  }
  void put(int k, double v) {
    int ha = hash(k);
    auto t = new hashentry(k, v);
    unique_lock<shared_mutex> lock(p[ha].mu);
    auto c = p[ha].next;
    if (c == 0) {
      p[ha].next = t;
    } else {
      while (c->next)
        c = c->next;
      c->next = t;
    }
  }
  void erase(int k) {
    int ha = hash(k);
    unique_lock<shared_mutex> lock(p[ha].mu);
    auto hd = p[ha].next;
    if (hd == 0)
      return;
    if (hd->next == 0 && hd->k == k) {
      hd->next = 0;
      return;
    }
    auto pv = hd;
    hd = hd->next;
    while (hd) {
      if (hd->k == k) {
        pv->next = hd->next;
        delete hd;
        return;
      }
      pv = hd, hd = hd->next;
    }
  }
};

} // namespace _concurrent_hashmap
