//
// Created by root on 11/22/18.
//

#ifndef PNSEI_OBJECTPOOL_H
#define PNSEI_OBJECTPOOL_H

#include "henry.h"

namespace _concurrent_shared_mutex{
/*
   1. Memory Layout
                heads
     ____________|________________
     |           |               |
   [head1]     [head2]       [headN]
   [.....]     [.....]  ...  [.....]
   subpool1    subpool2      subpoolN

   2. freelist connects all free slots
 */

template<std::size_t MAX_OBJ_SIZE>
class pool{
  const size_t aligned_size = (int)(8*ceil(MAX_OBJ_SIZE/8.));// 内存对齐
  /*real capacity can be greater than maxcapacity because after
   expansion, the object can be released.*/
  uint64_t realcap = 0;
  uint64_t mincap = 0;
  uint64_t maxcap = 0;
  atomic<uint64_t> usedcap = {0};
  int16_t obj_size = -1;
  vector<char*> heads; // heads of pools子对象池
  map<char*,int> addr2subpoolsize;
  mutex mtx_freelist;
  mutex mtx_pool_expansion;

  forward_list<char*> freelist;

  uint64_t get_usedcap(){ return usedcap;}

  pool(std::size_t maxCapacity, std::size_t minCapacity){
    static_assert(MAX_OBJ_SIZE>0 && MAX_OBJ_SIZE<1024*1024*100,
                  "MAX_OBJ_SIZE is not correct, should be in range of [0, 100M].");
    assert(maxCapacity>minCapacity);
    mincap = minCapacity;
    realcap = maxcap = maxCapacity;
    uint64_t total_pool_size = maxCapacity * aligned_size;
    char* head = new char[total_pool_size]();// 分配内存空间
    for (int i=0;i<maxcap; ++i){
      freelist.push_front(head + i*aligned_size);// 挂在一个forward_list下面
    }
    heads.emplace_back(head);
    addr2subpoolsize[head] = total_pool_size;
  }

  ~pool(){
    for_each(heads.begin(),heads.end(),[](char* p){delete [] p;});
  }

  /// @brief to find the unused block to place new object instance
  char* find_free_block_and_mark(){
    lock_guard<mutex> g(mtx_freelist);
    char* r = freelist.front();
    freelist.pop_front();
    return r;
  }

  /// @brief to be called by the deleter of shared_ptr
  /// there is no memory deallocation until end of the program
  /// what we need to do is to mark the tag as null, meaning the memory block is not used
  void release_block(char* p){
    lock_guard<mutex> g(mtx_freelist);
    freelist.push_front(p);
    --usedcap;
  }

  /// @brief to allocate memory from pool for a new OBJECT
  /// the memory layout is homogeneous, so all objects must be the same type,
  /// otherwise an exception will be thrown
  /// this function will:
  ///     1. find a free block in the pool memeory
  ///     2. use `placement new` to put an object into the memory slot
  ///     3. put the raw pointer into a shared_ptr to take advantduration of the
  ///        counting reference features
  ///     4. check the capacity left and see if it is necessary to expand the memory pool
  template<typename OBJECT, typename ...ARGS>
  void alloc (std::shared_ptr<OBJECT> & object, ARGS ...args){
    if (MAX_OBJ_SIZE<sizeof(OBJECT)){
      throw "object size is too big!";
    }
    if (obj_size == -1){
      obj_size = sizeof(OBJECT);
    }else if(obj_size != sizeof(OBJECT)){
      throw "Wrong type!";
    }
    char *freeblock = find_free_block_and_mark();
    if (freeblock){
      OBJECT* p = new ((void*)freeblock) OBJECT(args...); // placement new
      object.reset(p, [this](OBJECT* o){
        o->~OBJECT();// call OBJECT's destructor
        this->release_block(reinterpret_cast<char*>(o));
      });
      ++usedcap;
      if (realcap - mincap <  usedcap){
        lock_guard<mutex> g(mtx_pool_expansion);
        //auto f = async(launch::async, &pool::extend_pool, this);
        //f.get();
        auto bundle = bind(&pool::extend_pool, this);
        packaged_task<void()> ptsk(move(bundle));
        auto f = ptsk.get_future();
        thread(move(ptsk)).detach();
        f.get();
      }
    }
  }

  /// @brief Create subpool
  void extend_pool(){
    lock_guard<mutex> g(mtx_freelist);
    uint64_t shortduration = (realcap - mincap);
    uint64_t subpoolsize = shortduration * (aligned_size);
    cout << "\n(" << __LINE__ << ") " << __FUNCTION__ << " expand pool by "
         << shortduration << " slots!" << endl;
    char *head = new char[subpoolsize]();
    for (int i=0;i<shortduration; ++i){
      freelist.push_front(head + i*aligned_size);
    }
    heads.emplace_back(head);
    addr2subpoolsize[head] = subpoolsize;
    realcap += shortduration;
  }
};
}
#endif //PNSEI_OBJECTPOOL_H
