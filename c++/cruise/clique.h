//
// Created by henry on 10/21/18.
//
#include "henry.h"

#ifndef C_LRU_H
#define C_LRU_H

/*
 * [] Cruise onsite面 [复制链接] |试试Instant~

 https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=293409&ctid=228575

发个小公司 onsite 面经吧攒个人品，申的是无人驾驶相关类岗位，总共被4个人面，一人一小时，第一个人出题是sparse matrix设计set,get,add，第二个题是图里的connected component, 第三题是图像里面找像素比周围rxr区域都大的点（专业名词heatmap argmax）并优化算法，第四题是leetcode range sum 2d 那个。 感觉题都不难，但是要白板写，从没在白板写过。

被技术问题问倒了，多纬度数据如何存储，查找，这个不难kd-tree，然后区间查找如何o(1)这个真不知道，然后问了些神经网络的东西，我做过一些，但从没研究过神经网络里面模型的意义，被问到了自己调的网络的模型意义，半年前搭的网络早忘了具体模型意义，答不上来，然后问了如何在实际中应用，没有实际相关领域工作经验答不上来。。。

第二天发据信了。

 OA 三题，一个半小时，第一题Pascal's Triangle , 第二题大意是一个robot，可以执行G，L，R，三种操作，对应为直行，左转，右转，现在给定一个操作序列， 如GLR, 或是其他的如LR， 给定的操作直行无限次操作，请问哪种操作序列可以保证robot会停留在一个圆里面活动（即不会一直往前走），第三题是hackrank上的clique题，你可以去看看

 * */


namespace cruise_2017_09_20{
  // http://sde.quant365.com/linkedin-2017-interview-questions-part-3.html#sparse-matrix-storage
  // https://www.hackerrank.com/challenges/clique/problem
  // https://www.youtube.com/watch?v=t-_ZWbugSb8
  // https://www.youtube.com/watch?v=eya-cyk-7-4
  // https://www.youtube.com/watch?v=qZs767KQcvE
  int get_edges(int k, int n){ // mono increasing with k
    return int(1.0*(k-1)*n*n/k/2);
  }
  // find the first get_edges(x) >= edge_num
  int clique(int n, int m) { // 3,2
    int lo = 0, hi = n; //3
    while (lo <= hi) {
      int mid = lo + (hi - lo) / 2; // 1, 2
      int t=get_edges(mid, n);
      if (t < m)
        lo = mid+1;
      else if(t==m)
        return mid;
      else
        hi = mid-1;
    }
    return lo;

  }
  void test(){
    assert(clique(3,2) == 2);
    assert(clique(4,6) == 4);
    assert(clique(5,7) == 3);

    vector<pair<int,int>> vp={{35, 152},
                              {29, 258},
                              {45, 566},
                              {38, 164},
                              {51, 122}};
    vector<int> rs={2,3,3,2,2};
    for(int i=0;i<vp.size();i++){
      assert(clique(vp[i].first, vp[i].second) == rs[i]);
    }
    cout << clique(19,166) << endl;
  }
}

#endif //C_LRU_H
