//
// Created by henry on 12/24/18.
//

#ifndef PNSEI_TIMER_H
#define PNSEI_TIMER_H

/*
Simple C++11 profiler class to profile your function calls, etc.
Usage:
	profiler e;

	e.begin();
	myFunctionToBeProfiled();
	auto microseconds = e.end();
*/


#include "henry.h"
#include <unistd.h> // _SC_PAGE_SIZE
#include <iomanip> // setprecision


void process_mem_usage(double &vm_usage, double &resident_set) {
  vm_usage = 0.0;
  resident_set = 0.0;
  ifstream stat_stream("/proc/self/stat", ios_base::in);
  string pid, comm, state, ppid, pgrp, session, tty_nr;
  string tpgid, flags, minflt, cminflt, majflt, cmajflt;
  string utime, stime, cutime, cstime, priority, nice;
  string O, itrealvalue, starttime;
  unsigned long vsize;
  long rss;
  stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
              >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
              >> utime >> stime >> cutime >> cstime >> priority >> nice
              >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest
  stat_stream.close();
  // getpagesize()
  long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
  vm_usage = vsize / 1024.0;
  resident_set = rss * page_size_kb;
}

class profiler {
protected:
  chrono::high_resolution_clock::time_point _begin;
public:
  void begin() { _begin = chrono::high_resolution_clock::now(); }

  chrono::microseconds end() {
    auto diff = chrono::high_resolution_clock::now() - _begin;
    return chrono::duration_cast<chrono::microseconds>(diff);
  }
};

static bool raii_timer_b = false;

class raii_timer : public profiler {
  long long _delta = -1;
  double vm_usage = -1;
  double resident_set = -1;
  long long x = 0;
public:
  raii_timer(long long var) {
    if (!raii_timer_b) {
      cout << "x,time_us,vm_k,rss_k,avg" << endl;
      raii_timer_b = true;
    }
    x = var;
    begin();
  }

  ~raii_timer() {
    _delta = end().count();
    process_mem_usage(vm_usage, resident_set);
    cout << x << "," << _delta << "," << vm_usage << "," << resident_set << "," << setprecision(5)
         << (_delta == 0 ? 0 : double(x) / _delta) << endl;
  }
};


#endif //PNSEI_TIMER_H
