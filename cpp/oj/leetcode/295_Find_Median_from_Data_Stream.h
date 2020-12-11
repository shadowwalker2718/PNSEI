//
// Created by Henry Wu on 11/23/18.
//

#ifndef PNSEI_295_FIND_MEDIAN_FROM_DATA_STREAM_H
#define PNSEI_295_FIND_MEDIAN_FROM_DATA_STREAM_H

// https://leetcode.com/problems/find-median-from-data-stream/
// http://sde.quant365.com/binary-search-tree.html#find-median-from-data-stream-1
// http://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=208621
#include "pnsei.h"

namespace _295 {

// TODO - there is a bug there, probably in succ or pred, when there are two equal nodes
// Hard when dealing with duplicate value nodes!!!! Refer to the java version
struct node {
  int val;
  node *l, *r;

  node(int d) : val(d), l(nullptr), r(nullptr) {}

  void insert(int d) {
    if (d < val) {
      if (l) {
        l->insert(d);
      } else {
        l = new node(d);
      }
    } else if (d >= val) { // treat equal number as greater
      if (r) {
        r->insert(d);
      } else {
        r = new node(d);
      }
    }
  }
  //node* pred(){}
};

struct medianTree {
  node *R=nullptr;
  node *lm=0, *um=0; // lower median and upper median
  int z=0;
  medianTree(){}
  void addNum(int d) {
    if (!R) {
      lm = um = R = new node(d), z++;
      return;
    }
    R->insert(d);
    if(z&1){ // odd, then lm==um
      if(d<lm->val){
        lm = pred(lm);
      }else{ // (d>=lm->val)
        um = succ(um);
      }
    }else{ // even before insertion
      if(d<lm->val){
        um = lm;
      }else if(lm->val <= d && d < lm->val){
        lm = succ(lm);// actually node d
        um = pred(um);
      }else{ // lm->val <= d
        lm = um;
      }
    }
    z++;
  }

  node* pred(node* n){
    if(n->l){
      auto c=n->l;
      while(c->r) c=c->r;
      return c;
    }
    // find one less than n->val, and n has no left child (no need to consider n->r), so we need to use Root
    node* c=R, *r=nullptr;
    while(c){
      if(c->val < n->val)
        r = c, c=c->r;
      else if(c->val == n->val)
        return r;
      else{
        c = c->l;
      }
    }
    return r;
  }
  // find the one greater than n->val
  node* succ(node* n){
    if(n->r){
      auto c=n->r;
      while(c->l) c=c->l;
      return c;
    }
    node *c=R, *r=nullptr;
    while(c){
      if(c->val > n->val) r=c, c=c->l;
      else if(c->val == n->val) return r;
      else{
        c = c->r;
      }
    }
    return r;
  }

  // Returns the median of current data stream
  double findMedian() {
    return (lm->val + um->val) / 2.0;
  }
};

using MedianFinder = medianTree;

/*struct Node {
  weak_ptr<Node> parent; //
  shared_ptr<Node> left;
  shared_ptr<Node> right;
  int data;

  Node(int d) { this->data = d; }

  void add(int d) {
    if (d >= this->data) {
      if (right == nullptr) {
        right = make_shared<Node>(d);
        right->parent = shared_ptr<Node>(this);
      } else
        right->add(d);
    } else {
      if (left == nullptr) {
        left = make_shared<Node>(d);
        left->parent = shared_ptr<Node>(this);
      } else
        left->add(d);
    }
  }

  shared_ptr<Node> predecessor() {
    if (left != nullptr)
      return left->rightMost();
    weak_ptr<Node> pred = parent;
    shared_ptr<Node> child(this);
    while (pred.lock() != nullptr && child != pred->right) {
      child = pred;
      pred = pred->parent.lock();
    }
    return pred;
  }

  shared_ptr<Node> successor() {  //CLRS 292
    if (right != nullptr)
      return right->leftMost();
    shared_ptr<Node> successor = parent;
    shared_ptr<Node> child(this);
    while (successor != nullptr && child != successor->left) {
      child = successor;
      successor = successor->parent;
    }
    return successor;
  }

  shared_ptr<Node> leftMost() {
    if (left == nullptr)
      return shared_ptr<Node>(this);
    return left->leftMost();
  }

  shared_ptr<Node> rightMost() {
    if (right == nullptr)
      return shared_ptr<Node>(this);
    return right->rightMost();
  }
};

class MedianFinder {
  shared_ptr<Node> root;
  shared_ptr<Node> lower_median;
  shared_ptr<Node> upper_median;
  int size;
public:
  MedianFinder() : size(0) {}

  // Adds a number into the data structure.
  void addNum(int num) {
    if (root == nullptr) {
      root = make_shared<Node>(num);
      lower_median = root;
      upper_median = root;
    } else {
      root->add(num);
      ////!!!! adjust lower_median and upper_median
      if (size % 2 == 0) {
        if (num < lower_median->data) {
          upper_median = lower_median;
        } else if (lower_median->data <= num && num < upper_median->data) {
          lower_median = lower_median->successor();
          upper_median = upper_median->predecessor();
          //upper_median = lower_median = r;
        } else if (upper_median->data <= num) {
          lower_median = upper_median;
        }
      } else {
        if (num < lower_median->data) {
          lower_median = lower_median->predecessor();
        } else {
          upper_median = upper_median->successor();
        }
      }
    }
    size++;
  }

  // Returns the median of current data stream
  double findMedian() {
    return (lower_median->data + upper_median->data) / 2.0;
  }
};*/

void test() {
  {
    MedianFinder mf;
    mf.addNum(0);
    mf.addNum(0);
    assert(mf.findMedian() == 0);
  }

  {
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    assert(mf.findMedian() == 1.5);
    mf.addNum(3);
    assert(mf.findMedian() == 2.0);
  }
}
}


#endif //PNSEI_295_FIND_MEDIAN_FROM_DATA_STREAM_H
