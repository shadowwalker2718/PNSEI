//
// Created by henry on 12/15/18.
//

#ifndef PNSEI_CPP_FASTER_THAN_C_H
#define PNSEI_CPP_FASTER_THAN_C_H


#include <henry.h>
#include <sys/resource.h>


namespace _cpp_c {

  template<typename T>
  const T *bsearch(const T *key, const T *base, size_t num, size_t size,
                   int (*cmp)(const T *key, const T *elt)) {
    const T *start = base, *end = start + num, *pivot;
    int result;

    while (start < end) {
      pivot = start + ((end - start) >> 1);
      result = cmp(key, pivot);
      if (result == 0)
        return pivot;
      if (result > 0) {
        start = pivot + 1;
      } else
        end = pivot;
    }
    return NULL;
  }

  struct node {
    int v;
    long extra;
  };

  int cmp(const node *a, const node *b) {
    if (a->v < b->v) return -1;
    if (a->v > b->v) return 1;
    return 0;
  }

  int test() {
    // set stack size to 64MB
    /*struct rlimit rl;
    getrlimit(RLIMIT_STACK, &rl);
    rl.rlim_cur = 64L * 1024L * 1024L;
    setrlimit(RLIMIT_STACK, &rl);*/

    static const int z=1024;
    node* ns = (node*)malloc(z*sizeof(node));
    REP(i,0,z){
      ns[i].v=i;
    }

    REP(i,0,z){
      node t={i,0};
      auto r=bsearch<node>(&t,&ns[0],z,sizeof(node),cmp);
      assert(r->v==i);
    }
    free(ns);
    return 0;
  }


}

#endif //PNSEI_CPP_FASTER_THAN_C_H
