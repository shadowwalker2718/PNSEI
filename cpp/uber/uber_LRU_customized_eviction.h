//
// Created by root on 11/12/18.
//

#ifndef PNSEI_UBER_LRU_OPTIMIZED_DELETE_H
#define PNSEI_UBER_LRU_OPTIMIZED_DELETE_H
/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=454039&highlight=uber
 *
 * 2018(10-12月) 码农类General 本科 全职@Uber - 内推 - Onsite  | Fail | fresh grad应届毕业生
 Uber 10.12 onsite,  感觉面的不错 但还是挂了, LZ还挂了FB 和 Two Sigma,但只有Uber让我痛心,因为对他家的products很喜欢
 一共五轮

 第一轮 team manager behavior

 第二轮, LRU, follow up 优化删除的算法,现在LRU的size不是用Number of element来算,
 而是用byte 比如里面存有: 2 byte data-> 3 byte data -> 8 byte data -> 50 byte
 data, LRU size 是 65 bytes.现在有另外一个8 bytes 的data 要进来. 因为lru已经有
 63 bytes的data, 需要删除. 按照原来的算法,50 bytes data 被删除. 但这不是最优化
 的,最优化的是删除8 byte的data. 这是一个比较Open end 的,LZ最后也只是乱说了一通,
 后面想想,还是应该把那些rule都搞清楚. recruiter说不错所以这个可能不是挂点吧

 第三轮, Letter Combinations of a Phone Number, 用了DFS然后BFS.讨论了
 complexity. 最后他引导我用bit representation 去表达每一个combination,跟着
 他的思路走就好了,没用写代码

 第四轮, bar raiser, behavior

 第五轮, 给两个data streams, 第一个是driver的位置和时间点,第一个是rider的.第一
 问是算出data stream的起始时间和结束时间.因为是按照时间顺序,所以求第一个data point
 和最后一个的就行了. 第二问是求出driver 和 rider碰面的时间点. 和面试官讨论了不同的
 算法,选了其中一种来code, 具体记不清了.之后我问了面试官你会怎么做,他说估计就是看
 rider和driver的距离保持不变一段时间后,取这个距离的开始点.感觉这一轮答得不太好

 最后祝大家面试顺利!

 第二轮越满越好是其中一个条件,同时还要尽量删除least recently的element.所以跟面试官聊清楚哪个条件优先考虑吧
 第五轮的位置用经纬度表示.

 第五轮是system design?
 不是,应该是algorithm design. 他给你问题,然后你讨论算法

 >Biophotonics 发表于 2018-10-31 04:35
 >所以感觉第一个楼主是怎么说的 ? 是从头开始删数据量最小的点吗?
 <LRU那题 follow up吗? 有几个条件:尽量删除少的data,然后尽量删除least recent的data. 还是要和面试官沟通哪个条件要先满足

 >lccccccc 发表于 2018-11-2 13:03
 >想问下第三轮的bit representation具体是什么意思?谢谢!
 <就是说如果每个数字可以对应3个字母,那么久可以用两个bit来表示它的字母组合. 比如1对应ABC, 那么就可以用00 01 10 来表示A, B, C.
 <其它数字同理.这样的话就没有必要用char来表示字母了. 虽然Big(O)是一样的,但实际会少一点

 >多谢楼主分享!第五题中rider是不是刚开始位置一致不变化因为在等driver?如果碰面了的话位置上有相同点吗 ...
 <这个不清楚.他们碰面的时候不一定是位置相等,有可能是很小的距离
 */
#include "henry.h"

namespace _uber_lru {

struct node {
  int k;
  int v;
  int z; // vol, or size
};

class LRU_By_Size {
  list<node> l; // key is unique in the ll
  unordered_map<int, list<node>::iterator> m;
  const int CAPSIZE;

protected:
  int cz = 0;// current size
  bool __promote(list<node> &l, list<node>::iterator it) {
    if (l.begin() != it) {
      l.splice(l.begin(), l, it, next(it)); // a.splice(x, b, [, ))
      return true;
    }
    return false;
  }

  void __remove_node(list<node>::iterator it) {
    m.erase(it->k);
    l.erase(it);
    cz -= it->z;
  }

  // nn - new node we just add to the list
  void __evict(const node &nn) {
    while (CAPSIZE < cz) {
      // eviction policy
      // traverse ll backward and find the node with size equal to nn.z and distance(or time) less than T with tail
      // (concept of time window), if we couldn't find it, evict the last one
      // policy 1
      auto it = l.end();
      int count = 0, T = 10, evicted = 0;
      // https://stackoverflow.com/questions/3610933/iterating-c-vector-from-the-end-to-the-begin
      while (it != l.begin() && count < T) {
        it--;
        count++;
        if (it->z == nn.z && it->k != nn.k) {
          __remove_node(it);
          evicted = 1;
          break;
        }
      }
      // policy 2
      if (!evicted) { // remove from the last one until the capacity is enough ????
        while (CAPSIZE < cz && !l.empty()) {
          __remove_node(prev(l.end()));
        }
      }
    }
  }

public:
  LRU_By_Size(int cap_) : CAPSIZE(cap_) {}

  int get(int k) {
    if (!m.count(k))
      return INT_MIN;
    int r = m[k]->v;
    if (__promote(l, m[k]))
      m[k] = l.begin();
    return r;
  }

  // first we don't consider constraint of size, we just blindly push_front/promote
  // then we do evict
  bool put(int k, int v, int z) {
    // 0. edge case
    if (z > CAPSIZE)
      return false;
    node nn = {k, v, z};
    // 1. old node
    if (m.count(k)) {
      if (__promote(l, m[k]))
        m[k] = l.begin();
      if (l.front().z != z) {
        cz += z - l.front().z;
        l.front().z = z;
      }
      if (l.front().v != v)
        l.front().v = v;
    } else {
      // 2. new code
      // 2.1 evict ?
      // 2.2 add new node to front
      l.push_front(nn);
      m[k] = l.begin();
      cz += z;
    }
    __evict(nn);
    return true;
  }

  int getsize() { return cz; }
};

/*
 *  第二轮, LRU, follow up 优化删除的算法,现在LRU的size不是用Number of element来算,
 而是用byte 比如里面存有: 2 byte data-> 3 byte data -> 8 byte data -> 50 byte
 data, LRU size 是 65 bytes.现在有另外一个8 bytes 的data 要进来. 因为lru已经有
 63 bytes的data, 需要删除. 按照原来的算法,50 bytes data 被删除. 但这不是最优化
 的,最优化的是删除8 byte的data. 这是一个比较Open end 的,LZ最后也只是乱说了一通,
 后面想想,还是应该把那些rule都搞清楚. recruiter说不错所以这个可能不是挂点吧
 * */
void test() {
  LRU_By_Size lru(65);

  lru.put(3, 13, 50);
  lru.put(1, 12, 8);
  lru.put(2, 11, 3);
  lru.put(0, 1, 2);

  lru.put(4, 11, 8);

  assert(lru.getsize() == 63);
  assert(lru.get(3) == 13);
}

}


#endif //PNSEI_UBER_LRU_OPTIMIZED_DELETE_H
