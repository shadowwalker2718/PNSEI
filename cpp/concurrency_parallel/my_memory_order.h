//
// Created by henry on 12/15/18.
//

#ifndef PNSEI_MY_MEMORY_ORDER_H
#define PNSEI_MY_MEMORY_ORDER_H

#include "pnsei.h"

namespace _mem_order {

namespace _ordering {
// https://preshing.com/20120515/memory-reordering-caught-in-the-act/
// https://preshing.com/20120625/memory-ordering-at-compile-time/

#include <pnsei.h>
#include <pthread.h>
#include <semaphore.h> // TLPI P1099 unnamed semaphores
#include <stdio.h>

// Set either of these to 1 to prevent CPU reordering
#define USE_CPU_FENCE              0
#define USE_SINGLE_HW_THREAD       0  // Supported on Linux, but not Cygwin or PS3

#if USE_SINGLE_HW_THREAD
#include <sched.h>
#endif

sem_t beginSema1;
sem_t beginSema2;
sem_t endSema;

int X, Y;
int r1, r2;

[[noreturn]] void *thread1Func(void *param) {
  while (1) {
    sem_wait(&beginSema1);  // Wait for signal -1
    // ----- THE TRANSACTION! -----
    X = 1;
#if USE_CPU_FENCE
    asm volatile("mfence" ::: "memory");  // Prevent CPU reordering
#else
    asm volatile("":: : "memory");  // Prevent compiler reordering
#endif
    r1 = Y;
    sem_post(&endSema);  // Notify transaction complete +1
  }
  return NULL;  // Never returns
};

[[noreturn]] void *thread2Func(void *param) {
  while (1) {
    sem_wait(&beginSema2);  // Wait for signal -1
    // ----- THE TRANSACTION! -----
    Y = 1;
#if USE_CPU_FENCE
    asm volatile("mfence" ::: "memory");  // Prevent CPU reordering
#else
    asm volatile("":: : "memory");  // Prevent compiler reordering
#endif
    r2 = X;
    sem_post(&endSema);  // Notify transaction complete +1
  }
  return NULL;  // Never returns
};

int test() {
  // Initialize the semaphores
  sem_init(&beginSema1, 0, 0);
  sem_init(&beginSema2, 0, 0);
  sem_init(&endSema, 0, 0);

  // Spawn the threads
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, thread1Func, NULL);
  pthread_create(&thread2, NULL, thread2Func, NULL);

#if USE_SINGLE_HW_THREAD
// Force thread affinities to the same cpu core.
cpu_set_t cpus;
CPU_ZERO(&cpus);
CPU_SET(0, &cpus);
pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpus);
pthread_setaffinity_np(thread2, sizeof(cpu_set_t), &cpus);
#endif

  // Repeat the experiment ad infinitum
  int detected = 0;
  for (int iterations = 1;; iterations++) {
    // Reset X and Y
    X = 0;
    Y = 0;
    // Signal both threads
    sem_post(&beginSema1); // +1
    sem_post(&beginSema2); // +1
    // Wait for both threads
    sem_wait(&endSema); // -1
    sem_wait(&endSema); // -1
    // Check if there was a simultaneous reorder
    if (r1 == 0 && r2 == 0) {
      detected++;
      printf("%d reorders detected after %d iterations\n", detected, iterations);
      if (detected > 10)
        break;
    }
  }
  sem_destroy(&endSema);
  sem_destroy(&beginSema2);
  sem_destroy(&beginSema1);
  return 0;
}

}

int r1, r2;
atomic<int> x, y;

void func1() {
  r1 = y.load(memory_order_relaxed);
  x.store(r1, memory_order_relaxed);
}

void func2() {
  r2 = x.load(memory_order_relaxed);
  y.store(42, memory_order_relaxed);
}

//struct sequentially_consistent{
char c = 0, b = 0;
int m;
int n;

void f1() {
  while (rand() % 16 != 0) {}
  c = 1;
  asm volatile("":: : "memory");
  m = b;
}

void f2() {
  while (rand() % 16 != 0) {}
  b = 1;
  asm volatile("":: : "memory");
  n = c;
}
//};



void test() {
  while (1) {
    async(launch::async, func1).get();
    async(launch::async, func2).get();
    if (r2 == 42) {
      cout << "reordered0!" << endl;
      break;
    }
  }
  /*while(1){
    sequentially_consistent sc;
    async(launch::async, &sequentially_consistent::f1, &sc).get();
    async(launch::async, &sequentially_consistent::f2, &sc).get();
    if (sc.m==0 and sc.n==0){
      cout << "reordered!" << endl;
      break;
    }
  }*/
  while (1) {
    c = 0;
    b = 0;
    async(launch::async, f1).get();
    async(launch::async, f2).get();
    if (m == 0 and n == 0) {
      cout << "reordered!" << endl;
      break;
    }
  }
}
}

#endif //PNSEI_MY_MEMORY_ORDER_H
