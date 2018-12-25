//
// Created by henry on 10/24/18.
//

#ifndef PNSEI_ID_ALLOCATOR_H
#define PNSEI_ID_ALLOCATOR_H

/*
 * https://www.1polong long3acres.com/bbs/thread-361979-1-1.html

 * 第一轮算法,alloc id. HashTable + Queue
 写了一个简单实现,然后分析这个解法哪里不好,计算了一下memory
 usage.然后说可以用BitSet来记录每个Id的使用情况,这样可以把内存使用降低到1/32.
 简单聊了一下BitSet的实现原理,分析了时间复杂度是O(n).没有实现,然后继续讨论了优化可可能性,给出了Segment
 Tree的解法.面试官说suppose给你的max
 capacity永远是2的N次,帮我降低实现难度,让我实现了一下.中间出了点小bug,被面试官发现了,很快修正了.做完以后还有10分钟左右,面试官问有没有一个解法可以做到O
 constant的复杂度,不是O(1).
 想了一会儿没想出来,只想到了从HashMap的角度出发,时间不多了就结束了,最后面试官简单说了一下思路,没太搞明白,但是确实是HashMap的方向.


alloc id 我onsite也遇到了, 最后的最优解法 是建立一个2n个bit的segment
graph_MST,然后o（lg n)的复杂度完成所有操作*/

/*
 * 编程题就一道,给一个数N,生成N个id, 用户可以调用allocate()来分配一个id,
用完后调用release()释放id, 这样别的用户可以用.
一开始给了基于bit的解法,但allocate的复杂度是O(N), 要求改进,并提示memory不是问题.
最后的方法是基于hash的.所有的id生成后放到hash table里,然后从里面取

Dropbox 真是万年题不变啊. 当时我用Tree, 刚好是space有要求

嗯,挺开放的题目,可难可易,取决于那一位面试官的考点在哪儿了

http://www.1polong long3acres.com/bbs/thread-194896-1-1.html

实现两个函数,long long allocate()和void
release(long longid),每调用一次allocate返回的id需要unique,为1到N之间的一个整数.如果release以后,就可以继续被allocate.之前用array+hashmap,
 达到O(1)时间和O(N)空间.后来被告知空间用得太多,map空间效率低,最后用了bitmap.这题其实和实现文件系统的metadata区域比较类似,不
 过最后居然是用时间换空间,有点让我诧异.

https://blog.csdn.net/whuwangyi/article/details/43112895

http://massivealgorithms.blogspot.com/2016/08/leetcode-379-design-phone-directory.html

Related OJ:
https://leetcode.com/problems/design-phone-directory/
*/
#include "henry.h"
#include "cplusplus/profiler.h"

namespace _sgement_tree {
// drawback: cannot return the newly-released ones
class IDAllocator {
  long long tree_size; // even number always
  vector<bool> segment_tree;

  void __build_tree(long long n) {
    segment_tree.resize(2 * n); // all false when initialization
    tree_size = 2 * n;
  }

  // O(LogN)
  void __update(long long tree_index, bool b) {
    segment_tree[tree_index] = b;
    long long i = tree_index;
    while (i > 0) {
      if (i % 2 == 1) {
        segment_tree[i / 2] = segment_tree[i] & segment_tree[i - 1];
      } else {
        segment_tree[i / 2] = segment_tree[i] & segment_tree[i + 1];
      }
      i = i / 2;
    }
  }

public:
  IDAllocator(long long n) {
    __build_tree(n);
  }

  // O(LogN)
  long long allocate() {
    if (segment_tree[1])
      return -1;
    // We can always get you allocated!!!
    long long i = 1, j = 2;
    // 1. find
    while (j < tree_size) {
#if 1
      if (i & 1) {
        if (segment_tree[j]) { j++; }
      } else {
        if (!segment_tree[j + 1]) { j++; }
      }
#else
      if (segment_tree[j]) { j++; }
#endif
      i = j, j = i << 1;;
    }
    long long tree_index = i;
    // 2. update
    __update(tree_index, true);
    return tree_index - tree_size / 2;
  }

  // O(LogN)
  bool release(long long n) {
    long long tree_index = n + tree_size / 2;
    if (!segment_tree[tree_index])
      return false;
    __update(tree_index, false); // update
    return true;
  }
};

class Nary_SegTree_IDAllocator {
  int K_Branches = 8;
  long long tree_size; // even number always
  vector<bool> segment_tree;
  long long inner_node_number;

  void __build_tree(long long n) {
    inner_node_number = ceil((n - 1.0) / (K_Branches - 1.0));
    tree_size = inner_node_number + n;
    segment_tree.resize(tree_size); // all false when initialization
    fill(segment_tree.begin(), segment_tree.end(), true); // true means available!!
  }

  void __update(long long tree_index, bool b) {
    if (segment_tree[tree_index]==b) // optimization
      return;
    long long i, pid, t, cid;
    if (b) {
      segment_tree[tree_index] = true;
      i = tree_index;
      while (i > 0) {
        pid = (i - 1) / K_Branches;
        if (segment_tree[pid]) // optimization
          return;
        segment_tree[pid] = true;
        i = pid;
      }
    } else {
      segment_tree[tree_index] = false;
      i = tree_index;
      while (i > 0) {
        pid = (i - 1) / K_Branches;
        t = pid * K_Branches;
        for (int j = 1; j <= K_Branches; j++) {
          cid = t + j;
          if(cid >= tree_size) break;
          if (segment_tree.at(cid)) {
            __update(pid, true);
            return;
          }
        }
        segment_tree[pid] = false;
        i = pid;
      }
    }

  }

public:
  Nary_SegTree_IDAllocator(long long n, int K = 8) : K_Branches(K) {
    __build_tree(n);
  }

  // O(LogN)
  long long allocate() {
    if (!segment_tree[0])
      return -1;
    // We can always get you allocated!!!
    long long i = 0, j, cid, t;
    // 1. find
    while (i < tree_size) {
      t = i * K_Branches;
      for (j = 1; j <= K_Branches; j++) {
        cid = t + j;
        if (cid >= tree_size)
          break;
        if (segment_tree[cid]) {
          i = cid;
          break;
        }
      }
      if (cid >= tree_size)
        break;
    }
    long long tree_index = i;
    // 2. update
    __update(tree_index, false);
    return tree_index - inner_node_number;
  }

  // O(LogN)
  bool release(long long n) {
    long long tree_index = n + inner_node_number;
    if (segment_tree[tree_index])
      return false;
    __update(tree_index, true); // update
    return true;
  }
};


void test() {
  // N-ary Segment Tree
  {
    long long n = 100;
    Nary_SegTree_IDAllocator o(n, 8);
    vector<long long> v(n);
    long long i = n;
    while (i--) {
      long long t = o.allocate();
      v[t] = 1;
    }
    assert(std::accumulate(v.begin(), v.end(), 0) == n);
    assert(o.allocate() == -1);
  }


  for (long long n = 9; n <= 500; n++) {
    Nary_SegTree_IDAllocator o(n);
    vector<long long> v(n);
    long long i = n;
    //cout << n << ":";
    while (i--) {
      long long t = o.allocate();
      //cout << t << ",";
      v[t] = 1;
    }
    //cout << endl;
    assert(std::accumulate(v.begin(), v.end(), 0) == n);
    assert(o.allocate() == -1);
  }
#define PERFORMANCE_TEST
#ifdef PERFORMANCE_TEST
  static const long long N = 1024LL;
  for (int BRANCHES = 2; BRANCHES <= 128; BRANCHES <<= 1) {
    cout << "BRANCHES NUMBER:" << BRANCHES << endl;
    for (long long i = 1; i <= 1024 * 1024; i *= 2) {
      Nary_SegTree_IDAllocator o(N * i, BRANCHES);
      raii_timer a_timer(N * i);
      for (long long k = 0; k < N * i; k++) {
        long long t = o.allocate();
      }
    }
    this_thread::sleep_for(10s);
  }
#endif

  {
    // test if the newly released id will be allocated first!?
    // YES. Segment tree has this property!!!
    srand(0xdeadbeef);
    long long n = 100, i = n / 3, t = 0;
    Nary_SegTree_IDAllocator o(n);
    vector<long long> v;
    while (i--) {
      t = o.allocate();
      v.push_back(t);
    }
    vector<long long> released_ids;
    for (long long i = 0; i < v.size(); i++) {
      if (rand() & 1) {
        released_ids.push_back(v[i]);
        o.release(v[i]);
      }
    }
    REP(k, 0, released_ids.size()) {
      t = o.allocate();
      assert(t == released_ids[k]);
    }

  }

}

/* https://www.pvk.ca/Blog/2014/04/13/k-ary-heapsort/
time_us,vm_k,rss_k
1
247084,16976,3860
2
533716,17232,4296
4
1069470,17744,4824
8
2304338,18768,5880
16
4489187,20816,7992
32
9446463,24912,12216
64
19325465,33104,20400
128
40407462,49488,36768
256
82994624,82256,69504
512
171168289,147792,134976


>>> 1*(2**20) / 247084.
4.243803726667854
>>> 512*(2**20) / 171168289.
3.1365091930082913

3 ids per us on average

247084,16976,3860
533716,17232,4296
1069470,17744,4824
2304338,18768,5880
4489187,20816,7992
9446463,24912,12216
19325465,33104,20400
40407462,49488,36768
82994624,82256,69504
171168289,147792,134976

8-ary segment tree:
x,time_us,vm_k,rss_k
1,144,16716,1976
2,274,16716,1976
4,579,16716,1976
8,1128,16716,1976
16,2308,16716,1976
32,4795,16716,1976
64,10077,16716,1976
128,25493,16716,1976
256,43310,16716,1976
512,86194,16864,4080
1024,170558,16940,4092
2048,354209,17088,4352
4096,707692,17380,4616
8192,1547075,17964,5144
16384,2960504,19136,6200
32768,6135929,21476,8576
65536,12382496,26156,13328
131072,25748848,35520,22568
262144,52091120,54244,41312
524288,110673564,91692,78800
// >>> 512*1024.*1024/110673564
//4.850940844373639

16-ary segment tree:
x,time_us,vm_k,rss_k
1,144,16716,1940
2,300,16716,1940
4,662,16716,1940
8,1447,16716,1940
16,2901,16716,1940
32,9064,16716,1940
64,16206,16716,1940
128,26652,16716,1940
256,62635,16716,1940
512,106819,16860,4112
1024,239757,16932,4124
2048,444266,17068,4384
4096,823088,17340,4648
8192,1656532,17888,5176
16384,3672065,18980,6232
32768,7252857,21164,8344
65536,14851553,25532,12832
131072,29649999,34272,21544
262144,61801851,51748,38968
524288,134401702,86700,73816


 BRANCHES NUMBER:2
x,time_us,vm_k,rss_k,avg
1024,158,16716,1940,6.481
2048,318,16716,1940,6.4403
4096,650,16716,1940,6.3015
8192,1298,16716,1940,6.3112
16384,2657,16716,1940,6.1664
32768,5601,16716,1940,5.8504
65536,11306,16716,1940,5.7966
131072,23264,16716,1940,5.6341
262144,49364,16856,4192,5.3104
524288,96892,16928,4208,5.4111
1048576,210191,17052,4268,4.9887
2097152,425162,17308,4528,4.9326
4194304,926607,17820,5056,4.5265
8388608,1698039,18844,6112,4.9402
16777216,3545360,20892,8224,4.7322
33554432,7200313,24988,12448,4.6601
67108864,14608784,33180,20632,4.5937
134217728,29911294,49564,37000,4.4872
268435456,65619861,82332,69736,4.0908
536870912,127205084,1.4787e+05,1.3521e+05,4.2205
1073741824,254357567,2.7894e+05,2.6615e+05,4.2214
BRANCHES NUMBER:4
1024,369,16792,4268,2.7751
2048,874,16792,4268,2.3432
4096,1426,16792,4268,2.8724
8192,3730,16792,4268,2.1962
16384,8570,16792,4268,1.9118
32768,15854,16792,4268,2.0669
65536,19780,16792,4268,3.3132
131072,25140,16792,4268,5.2137
262144,43267,16792,4268,6.0588
524288,79689,16792,4268,6.5792
1048576,160046,16964,4268,6.5517
2097152,333423,17136,4268,6.2898
4194304,660659,17476,4792,6.3487
8388608,1342696,18160,5320,6.2476
16777216,2929027,19524,6640,5.7279
33554432,5727032,22256,9544,5.859
67108864,12137566,27716,14824,5.529
134217728,24103047,49564,36736,5.5685
268435456,48628647,71408,58624,5.5201
536870912,100243745,1.151e+05,1.0245e+05,5.3557
1073741824,205661826,2.0248e+05,1.8957e+05,5.2209
BRANCHES NUMBER:8
1024,200,27716,15068,5.12
2048,326,27716,15068,6.2822
4096,681,27716,15068,6.0147
8192,1330,27716,15068,6.1594
16384,2723,27716,15068,6.0169
32768,5769,27716,15068,5.68
65536,11842,27716,15068,5.5342
131072,21398,27716,15068,6.1254
262144,40583,27716,15068,6.4595
524288,98495,27716,15068,5.323
1048576,195694,27716,15068,5.3582
2097152,336785,27716,15068,6.227
4194304,699732,27716,15068,5.9942
8388608,1387884,27716,15068,6.0442
16777216,2917191,27716,15068,5.7512
33554432,5897477,27716,15068,5.6896
67108864,12040543,27716,15068,5.5736
134217728,24656644,35520,22720,5.4435
268435456,49834892,72972,60208,5.3865
536870912,101788617,1.1042e+05,97580,5.2744
1073741824,210250021,1.8532e+05,1.7256e+05,5.107
BRANCHES NUMBER:16
1024,174,35520,22872,5.8851
2048,415,35520,22872,4.9349
4096,825,35520,22872,4.9648
8192,1615,35520,22872,5.0724
16384,2912,35520,22872,5.6264
32768,5767,35520,22872,5.682
65536,12858,35520,22872,5.0969
131072,22092,35520,22872,5.933
262144,44483,35520,22872,5.8931
524288,91755,35520,22872,5.714
1048576,190627,35520,22872,5.5007
2097152,389428,35520,22872,5.3852
4194304,785384,35520,22872,5.3405
8388608,1673414,35520,22872,5.0129
16777216,3469715,35520,22872,4.8353
33554432,7001754,35520,22872,4.7923
67108864,14129194,35520,22872,4.7497
134217728,28770616,35520,22872,4.6651
268435456,62372632,70476,57716,4.3037
536870912,121049955,1.0543e+05,92564,4.4351
1073741824,244797226,1.7533e+05,1.6252e+05,4.3862
BRANCHES NUMBER:32
1024,412,35520,22872,2.4854
2048,874,35520,22872,2.3432
4096,1821,35520,22872,2.2493
8192,4513,35520,22872,1.8152
16384,8733,35520,22872,1.8761
32768,17507,35520,22872,1.8717
65536,14517,35520,22872,4.5144
131072,28960,35520,22872,4.526
262144,58616,35520,22872,4.4722
524288,130684,35520,22872,4.0119
1048576,259947,35520,22872,4.0338
2097152,516911,35520,22872,4.0571
4194304,1194359,35520,22872,3.5118
8388608,2106147,35520,22872,3.9829
16777216,4483086,35520,22872,3.7423
33554432,9917414,35520,22872,3.3834
67108864,19273216,35520,22872,3.482
134217728,38204559,35520,22872,3.5131
268435456,77629688,69348,56660,3.4579
536870912,159664190,1.0317e+05,90452,3.3625
1073741824,341981420,1.7082e+05,1.5804e+05,3.1398
BRANCHES NUMBER:64
1024,215,35520,22872,4.7628
2048,475,35520,22872,4.3116
4096,1094,35520,22872,3.7441
8192,2144,35520,22872,3.8209
16384,4537,35520,22872,3.6112
32768,9252,35520,22872,3.5417
65536,18652,35520,22872,3.5136
131072,38554,35520,22872,3.3997
262144,85105,35520,22872,3.0802
524288,183607,35520,22872,2.8555
1048576,345549,35520,22872,3.0345
2097152,707562,35520,22872,2.9639
4194304,1520360,35520,22872,2.7588
8388608,3075569,35520,22872,2.7275
16777216,6773607,35520,22872,2.4769
33554432,13755396,35520,22872,2.4394
67108864,27432109,35520,22872,2.4464
134217728,55591331,35520,22872,2.4144
268435456,113266629,68812,56132,2.3699
536870912,235778992,1.021e+05,89396,2.277
1073741824,512233110,1.6868e+05,1.5592e+05,2.0962



 ==============================================================
BRANCHES NUMBER:2
x,time_us,vm_k,rss_k,avg
1024,151,16720,1956,6.7815
2048,300,16720,1956,6.8267
4096,614,16720,1956,6.671
8192,1317,16720,1956,6.2202
16384,2542,16720,1956,6.4453
32768,5760,16720,1956,5.6889
65536,11834,16720,1956,5.5379
131072,22895,16856,1956,5.7249
262144,50804,16824,4104,5.1599
524288,95384,16960,4104,5.4966
1048576,202458,17084,4196,5.1792
2097152,405498,17340,4456,5.1718
4194304,912454,17852,4984,4.5967
8388608,1665101,18876,6040,5.0379
16777216,3361552,20924,8152,4.9909
33554432,7100969,25020,12376,4.7253
67108864,14274980,33212,20560,4.7012
134217728,29266253,49596,36928,4.5861
268435456,59516461,82364,69664,4.5103
536870912,121395320,1.479e+05,1.3514e+05,4.4225
1073741824,245472075,2.7897e+05,2.6608e+05,4.3742
BRANCHES NUMBER:4
1024,149,16824,4196,6.8725
2048,295,16824,4196,6.9424
4096,630,16824,4196,6.5016
8192,1416,16824,4196,5.7853
16384,2882,16824,4196,5.6849
32768,4378,16824,4196,7.4847
65536,9064,16824,4196,7.2304
131072,18546,16824,4196,7.0674
262144,42875,16824,4196,6.1141
524288,91073,16824,4196,5.7568
1048576,177526,16996,4196,5.9066
2097152,319647,17168,4196,6.5608
4194304,634128,17508,4720,6.6143
8388608,1274591,18192,5248,6.5814
16777216,2622604,19556,6568,6.3972
33554432,5480724,22288,9472,6.1223
67108864,11241732,27748,14752,5.9696
134217728,22616743,49596,36664,5.9344
268435456,47223504,71440,58552,5.6844
536870912,95566359,1.1513e+05,1.0238e+05,5.6178
1073741824,190841478,2.0251e+05,1.895e+05,5.6264
BRANCHES NUMBER:8
1024,149,27748,14996,6.8725
2048,356,27748,14996,5.7528
4096,644,27748,14996,6.3602
8192,1359,27748,14996,6.028
16384,2822,27748,14996,5.8058
32768,5896,27748,14996,5.5577
65536,11227,27748,14996,5.8374
131072,23152,27748,14996,5.6614
262144,40591,27748,14996,6.4582
524288,77425,27748,14996,6.7716
1048576,157776,27748,14996,6.646
2097152,322022,27748,14996,6.5124
4194304,750105,27748,14996,5.5916
8388608,1384086,27748,14996,6.0608
16777216,2733870,27748,14996,6.1368
33554432,5728496,27748,14996,5.8575
67108864,11922650,27748,14996,5.6287
134217728,25457608,35552,22648,5.2722
268435456,47704354,73004,60136,5.6271
536870912,95987648,1.1045e+05,97508,5.5931
1073741824,199455077,1.8535e+05,1.7248e+05,5.3834
BRANCHES NUMBER:16
1024,135,35552,22800,7.5852
2048,274,35552,22800,7.4745
4096,598,35552,22800,6.8495
8192,1153,35552,22800,7.1049
16384,2362,35552,22800,6.9365
32768,4876,35552,22800,6.7203
65536,10354,35552,22800,6.3295
131072,20810,35552,22800,6.2985
262144,42068,35552,22800,6.2314
524288,87005,35552,22800,6.026
1048576,182693,35552,22800,5.7396
2097152,391675,35552,22800,5.3543
4194304,750886,35552,22800,5.5858
8388608,1539349,35552,22800,5.4495
16777216,3385247,35552,22800,4.956
33554432,6702151,35552,22800,5.0065
67108864,13511732,35552,22800,4.9667
134217728,28140616,35552,22800,4.7695
268435456,58065850,70508,57644,4.6229
536870912,116343132,1.0546e+05,92492,4.6145
1073741824,240273843,1.7536e+05,1.6245e+05,4.4688
BRANCHES NUMBER:32
1024,412,35552,22800,2.4854
2048,841,35552,22800,2.4352
4096,1669,35552,22800,2.4542
8192,3448,35552,22800,2.3759
16384,7420,35552,22800,2.2081
32768,17536,35552,22800,1.8686
65536,19927,35552,22800,3.2888
131072,28754,35552,22800,4.5584
262144,66225,35552,22800,3.9584
524288,118649,35552,22800,4.4188
1048576,252802,35552,22800,4.1478
2097152,508522,35552,22800,4.124
4194304,1175799,35552,22800,3.5672
8388608,2158710,35552,22800,3.8859
16777216,4483810,35552,22800,3.7417
33554432,9262385,35552,22800,3.6227
67108864,19113471,35552,22800,3.5111
134217728,38867185,35552,22800,3.4532
268435456,78722211,69380,56588,3.4099
536870912,164546297,1.032e+05,90380,3.2627
1073741824,352349414,1.7086e+05,1.5796e+05,3.0474

 * */


} // namespace dropbox_find_highest_minimum_sharpness

#endif // PNSEI_ID_ALLOCATOR_H
