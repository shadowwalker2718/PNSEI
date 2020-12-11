#pragma once
#include "pnsei.h"

namespace _h2o {
mutex gm;
atomic<int> hc = 0, oc = 0, th = 0, to = 0;
condition_variable cv;

void h() {
  unique_lock<mutex> gl(gm);

  while (hc == 2) {
    cv.wait(gl);
  }
  hc++; // make hydrogen
  th++; // total h
  cout << __LINE__ << "," << hc << "," << oc << endl;
  cv.notify_one();
}

void o() {
  unique_lock<mutex> gl(gm);
  while (hc != 2) {
    cv.wait(gl);
  }
  oc++; // make oxygen
  to++;
  cout << __LINE__ << "," << hc << "," << oc << endl;
  hc -= 2, --oc; // hc>=2 and oc<=1
  cout << "make water:" << to << "," << th << "," << hc << "," << oc << endl;
  // gl.unlock();
  // if (hc<2) {
  cv.notify_one();
  //}
}

void o2_() {
  unique_lock<mutex> gl(gm);
  while (hc != 2) {
    cv.wait(gl);
  }
  // while (oc == 2) {
  //  cv.wait(gl);
  //}
  oc++; // make_oxygen
  to++;
  if (oc == 2) {
    oc -= 2, hc -= 2;
    cout << "make h2o2:" << to << "," << th << "," << hc << "," << oc << endl;
  }
  cout << __LINE__ << "," << to << "," << oc << endl;
  cv.notify_one();
}

void o2() {
  unique_lock<mutex> gl(gm);
  while (oc == 2) {
    cv.wait(gl);
  }
  oc++; // make_oxygen
  to++;
  cout << __LINE__ << "," << to << "," << oc << endl;
  cv.notify_one();
}

void h2o2() {
  unique_lock<mutex> gl(gm);
  while (oc != 2 || hc != 2) {
    cv.wait(gl);
  }
  cout << "make h2o2:" << to << "," << th << "," << hc << "," << oc << endl;
  oc -= 2, hc -= 2; // make_h2o2
  cv.notify_one();
}

void mainthread3() {
  vector<thread *> threads;
  for (int i = 0; i < 400; ++i) {
    threads.push_back(new thread(h));
    threads.push_back(new thread(o2_));
  }

  for (thread *t : threads) {
    if (t->joinable()) {
      t->join();
      delete t;
    }
  }
}

void mainthread() {
  vector<thread *> threads;
  for (int i = 0; i < 300; ++i) {
    threads.push_back(new thread(h));
    threads.push_back(new thread(h));
    threads.push_back(new thread(o));
  }

  for (thread *t : threads) {
    if (t->joinable()) {
      t->join();
      delete t;
    }
  }
}

void mainthread2() {
  vector<thread *> threads;
  for (int i = 0; i < 100; ++i) {
    threads.push_back(new thread(o2));
    threads.push_back(new thread(h));
    threads.push_back(new thread(h2o2));
    threads.push_back(new thread(h));
    threads.push_back(new thread(o2));
  }

  for (thread *t : threads) {
    if (t->joinable()) {
      t->join();
      delete t;
    }
  }
}

namespace watermaker {
mutex gm;
atomic<int> hc = 0, oc = 0;
condition_variable cv;

void make_hydrogen() { hc++; }
void make_oxygen() { oc++; }
void make_water() { oc--, hc -= 2; }

void h() {
  unique_lock<mutex> gl(gm);
  while (hc == 2) {
    cv.wait(gl);
  }
  hc++; // make_hydrogen
  cv.notify_one();
}

void o() {
  unique_lock<mutex> gl(gm);
  while (hc != 2) {
    cv.wait(gl);
  }
  oc++;          // make_oxygen
  hc -= 2, --oc; // make_water
  cv.notify_one();
}

void run(int n) {
  vector<thread *> threads;
  for (int i = 0; i < n; ++i) {
    threads.push_back(new thread(h));
    threads.push_back(new thread(h));
    threads.push_back(new thread(o));
  }
  for_each(threads.begin(), threads.end(), [](thread *t) {
    if (t->joinable())
      t->join(), delete t;
  });
}
}; // namespace watermaker

void test() { watermaker::run(500); }

} // namespace _h2o

struct Solution { // 3ms
  vector<string> _1_19 = {"One",       "Two",      "Three",   "Four",
                          "Five",      "Six",      "Seven",   "Eight",
                          "Nine",      "Ten",      "Eleven",  "Twelve",
                          "Thirteen",  "Fourteen", "Fifteen", "Sixteen",
                          "Seventeen", "Eighteen", "Nineteen"};
  vector<string> _10_90 = {"Ten",   "Twenty",  "Thirty", "Forty", "Fifty",
                           "Sixty", "Seventy", "Eighty", "Ninety"};

  string rec(int n) {
    if (n >= 1e9) {
      return rec(n / 1e9) + " Billion" + rec(n % (int)1e9);
    } else if (n >= 1e6) {
      return rec(n / 1e6) + " Million" + rec(n % (int)1e6);
    } else if (n >= 1000) {
      return rec(n / 1000) + " Thousand" + rec(n % 1000);
    } else if (n >= 100) { // 100-999
      return rec(n / 100) + " Hundred" + rec(n % 100);
    } else if (n >= 20) { // 20-99
      return " " + _10_90[n / 10 - 1] + rec(n % 10);
    } else if (n >= 1) { // 1-19
      return " " + _1_19[n - 1];
    } else {
      return "";
    }
  }
  string numberToWords(int num) {
    if (num == 0)
      return "Zero";
    string r = rec(num);
    r.erase(r.begin());
    return r;
  }
};
