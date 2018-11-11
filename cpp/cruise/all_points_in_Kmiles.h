//
// Created by root on 11/6/18.
//

#ifndef PNSEI_ALL_POINTS_IN_KMILES_H
#define PNSEI_ALL_POINTS_IN_KMILES_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=434773&highlight=cruise
 *
 * 大概四月份店面。判断两个Intervals 是否有重叠。在 coder pad 上用 C++ 实现。这个容易。秒过。
六月昂塞。

 * 六月昂塞。
1. 自动车前面被一辆车挡住，如何判定自动车需要等待还是超过？
--------------------------------------------------------------
2. 自动车需要加油或维护，请找到并返回车附近K距离内得加油或维护站点。
--------------------------------------------------------------
3. 判断树是否平衡，平衡的定义是最优子树的叶子节点数差别不大于一。
4. 用C++实现LRU cache。
感觉自己当天状态不错，问题回答不是完美，但都答出来了。但最后还是悲剧，不明白什么原因。
难道他们要看无Bug秒过？ 我觉得我所表现的现场发现问题，解决问题的能力更有价值呵
 *
 * */

#include "henry.h"

struct Point {
  int x, y;
  Point(int _x, int _y) : x(_x), y(_y) {}
  Point() { x = y = 0; }
};


//#include <boost/geometry/geometries/point.hpp>
//#include <boost/geometry/geometries/box.hpp>
//#include <boost/geometry/index/rtree.hpp>

namespace _cruise_geometry {



//https://stackoverflow.com/questions/1627305/nearest-neighbor-k-d-tree-wikipedia-proof
namespace __kdtree {
//using point2d = boost::geometry::model::point<double, 2, boost::geometry::cartesian_tag>;
//using box2d = boost::geometry::model::box<point2d>;

}

namespace __quadtree {



struct BB { // bounding box
  Point lt;
  Point br;
};

int distance_square(const Point &a, const Point &b) {
  int x = a.x - b.x, y = a.y - b.y;
  return x * x + y * y;
}

int squared_distance(const Point &a, const BB &b) {
  //TODO
  return 0;
}


// The objects that we want stored in the quadtree
struct Node { // point + data
  Point pos;
  int data;
  Node(Point _pos, int _data) : pos(_pos), data(_data) {}
  Node() : data(0) {}
};

struct comp {
  bool operator()(pair<int, Node *> a, pair<int, Node *> b) { return a.first > b.first; }
};
using PriorityQueueT = priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, comp>;

// The main quadtree class
class quadtree {
  //bounding box
  Point l/*topLeft*/, r; //botRight
  // Contains details of node
  vector<Node *> nodes; // ?????
  // Children of this tree
  array<quadtree *, 4> qts; // *tl, *tr, *bl, *br
  //quadtree *tl, *tr, *bl, *br; // could be a vector
  const int MIN_BB_LEN = 4;

  Node *nn_dfs(const Point &p, int &mx2);

  void knn_dfs(const Point &p, int &mx2, PriorityQueueT &);
  void neighbors_dfs(const Point &p, int distance, vector<Node*>&);

public:
  quadtree(Point topL, Point botR);

  void insert(Node *);

  Node *search(Point);// search point to get Node(and data)
  Node *nn(const Point &); // nearest neighbor
  vector<Node *> knn(const Point &p, int k); // nearest neighbor
  vector<Node *> neighbors(const Point &p, int distance); // neighbors in k miles
  bool inBB(Point); // inside bounding box
};

quadtree::quadtree(Point topL, Point botR) {
  l = topL;
  r = botR;
  fill(qts.begin(), qts.end(), nullptr);
}

// Check if current quadtree contains the point
//--------------------> x  (coordinates of 4th quandrant)
// |
// |     l
// |
// v               r
// y
bool quadtree::inBB(Point p) { // depends on the direction of coordinate system
  return (p.x >= l.x && p.x <= r.x && p.y >= l.y && p.y <= r.y);
}

// Insert a node into the quadtree
void quadtree::insert(Node *node) {
  if (node == NULL or !inBB(node->pos)) // Current quad cannot contain it
    return;
  // We are at a quad of unit area, We cannot subdivide this quad further
  if (abs(l.x - r.x) <= MIN_BB_LEN and abs(l.y - r.y) <= MIN_BB_LEN) {
    nodes.push_back(node);
    return;
  }

  if ((l.x + r.x) / 2 >= node->pos.x) {
    // Indicates tl
    if ((l.y + r.y) / 2 >= node->pos.y) {
      if (qts[0] == NULL)
        qts[0] = new quadtree(Point(l.x, l.y), Point((l.x + r.x) / 2, (l.y + r.y) / 2));
      qts[0]->insert(node);
    } else { // Indicates bl
      if (qts[1] == NULL)
        qts[1] = new quadtree(Point(l.x, (l.y + r.y) / 2), Point((l.x + r.x) / 2, r.y));
      qts[1]->insert(node);
    }
  } else {// Indicates tr
    if ((l.y + r.y) / 2 >= node->pos.y) {
      if (qts[2] == NULL)
        qts[2] = new quadtree(Point((l.x + r.x) / 2, l.y), Point(r.x, (l.y + r.y) / 2));
      qts[2]->insert(node);
    } else { // Indicates br
      if (qts[3] == NULL)
        qts[3] = new quadtree(Point((l.x + r.x) / 2, (l.y + r.y) / 2), Point(r.x, r.y));
      qts[3]->insert(node);
    }
  }
}

// Find a node in a quadtree
Node *quadtree::search(Point p) {
  // Current quad cannot contain it
  if (!inBB(p))
    return NULL;
  // We are at a quad of unit length, We cannot subdivide this quad further
  if (!nodes.empty()) { // ONLY leaf nodes have data information
    for (Node *nd: nodes) {
      if (nd->pos.x == p.x and nd->pos.y == p.y)
        return nd;
    }
    return NULL;
  }
  if ((l.x + r.x) / 2 >= p.x) {
    if ((l.y + r.y) / 2 >= p.y) { // Indicates tl
      return qts[0] ? qts[0]->search(p) : NULL;
    } else { // Indicates bl
      return qts[1] ? qts[1]->search(p) : NULL;
    }
  } else {
    if ((l.y + r.y) / 2 >= p.y) { // Indicates tr
      return qts[2] ? qts[2]->search(p) : NULL;
    } else {// Indicates br
      return qts[3] ? qts[3]->search(p) : NULL;
    }
  }
}

Node *quadtree::nn(const Point &p) {
  if (!inBB(p)) return NULL;
  int distance = INT_MAX;
  return nn_dfs(p, distance);
}


Node *quadtree::nn_dfs(const Point &p, int &mx2) {
  if (not inBB(p)) { //////
    // compare with (point - BB) distance; ~ To be improved!
    int dis_square_to_BB = min(min((l.x - p.x) * (l.x - p.x), (r.x - p.x) * (r.x - p.x)),
                               min((l.y - p.y) * (l.y - p.y), (r.y - p.y) * (r.y - p.y)));
    if (mx2 < dis_square_to_BB)
      return NULL;
  }
  Node *r = NULL;
  if (!nodes.empty()) { // leaf qt node
    for (Node *n: nodes) {
      int d = distance_square(p, n->pos);
      if (d < mx2)
        mx2 = d, r = n;
    }
  } else { // other qts
    for (int i = 0; i < 4; i++) {
      if (qts[i] == nullptr) continue;
      auto tmp = qts[i]->nn_dfs(p, mx2);
      if (tmp) {
        r = tmp;
      }
    }
  }
  return r;
}

vector<Node *> quadtree::knn(const Point &p, int k) {
  if (k <= 0) return {};
  vector<Node *> r;
  priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, comp> q;
  int distance = INT_MAX;
  knn_dfs(p, distance, q);
  while (k-- and !q.empty()) {
    r.push_back(q.top().second), q.pop();
  }
  return r;
}

void quadtree::knn_dfs(const Point &p, int &mx2, PriorityQueueT &q) {
  if (not inBB(p)) { //////
    // compare with (point - BB) distance; ~ To be improved!
    int dis_square_to_BB = min(min((l.x - p.x) * (l.x - p.x), (r.x - p.x) * (r.x - p.x)),
                               min((l.y - p.y) * (l.y - p.y), (r.y - p.y) * (r.y - p.y)));
    if (mx2 < dis_square_to_BB)
      return;
  }
  if (!nodes.empty()) { // leaf qt node
    for (Node *n: nodes) {
      int d = distance_square(p, n->pos);
      q.emplace(d, n);
    }
  } else { // other qts
    for (int i = 0; i < 4; i++) {
      if (qts[i] == nullptr) continue;
      qts[i]->knn_dfs(p, mx2, q);
    }
  }
}

vector<Node *> quadtree::neighbors(const Point &p, int distance) {
  vector<Node *> r;
  neighbors_dfs(p,distance*distance,r);
  return r;
}

void quadtree::neighbors_dfs(const Point &p, int dd, vector<Node *> & v) {
  if (not inBB(p)) { //////
    // compare with (point - BB) distance; ~ To be improved!
    int dis_square_to_BB = min(min((l.x - p.x) * (l.x - p.x), (r.x - p.x) * (r.x - p.x)),
                               min((l.y - p.y) * (l.y - p.y), (r.y - p.y) * (r.y - p.y)));
    if (dd < dis_square_to_BB)
      return;
  }
  if (!nodes.empty()) { // leaf qt node
    for (Node *n: nodes) {
      int d = distance_square(p, n->pos);
      if(d<=dd)
        v.emplace_back(n);
    }
  } else { // other qts
    for (int i = 0; i < 4; i++) {
      if (qts[i] == nullptr) continue;
      qts[i]->neighbors_dfs(p, dd, v);
    }
  }
};


// http://ericandrewlewis.github.io/how-a-quadtree-works/
// http://bl.ocks.org/llb4ll/8709363
// https://blog.insightdatascience.com/planting-quadtrees-for-apache-flink-b396ebc80d35
// http://danielblazevski.github.io/assets/player/KeynoteDHTMLPlayer.html#12
// https://developer.apple.com/documentation/gameplaykit/gkquadtree
int test() {
  quadtree qt(Point(0, 0), Point(8, 8));
  Node a(Point(1, 1), 1);
  Node b(Point(2, 5), 2);
  Node c(Point(7, 6), 3);
  Node d(Point(3, 0), 0);
  Node e(Point(7, 7), 7);
  qt.insert(&a);
  qt.insert(&d);
  qt.insert(&b);
  qt.insert(&c);
  qt.insert(&e);
  auto r=qt.knn(Point(3, 3), 2);
  assert(r[0]->data == 2);
  assert(r[1]->data == 1);
  assert(qt.search(Point(1, 1))->data == 1);
  assert(qt.search(Point(2, 5))->data == 2);
  assert(qt.search(Point(7, 6))->data == 3);
  assert(nullptr == qt.search(Point(5, 5)));
  assert(qt.nn(Point(3, 3))->data == 2);
  assert(qt.nn(Point(2, 3))->data == 2);
  assert(qt.nn(Point(2, 4))->data == 2);
  assert(qt.nn(Point(2, 1))->data == 1);
  auto nns=qt.neighbors(Point(3, 3),5);
  assert(nns.size()==4);
  return 0;
}

}
}


#endif //PNSEI_ALL_POINTS_IN_KMILES_H
