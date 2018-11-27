//
// Created by root on 11/6/18.
//

#ifndef PNSEI_ALL_POINTS_IN_KMILES_H
#define PNSEI_ALL_POINTS_IN_KMILES_H

/*
 * https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=434773&highlight=cruise
 *
 * 大概四月份店面.判断两个Intervals 是否有重叠.在 coder pad 上用 C++ 实现.这个容易.秒过.
六月昂塞.

 * 六月昂塞.
1. 自动车前面被一辆车挡住,如何判定自动车需要等待还是超过?
--------------------------------------------------------------
2. 自动车需要加油或维护,请找到并返回车附近K距离内得加油或维护站点.
--------------------------------------------------------------
3. 判断树是否平衡,平衡的定义是最优子树的叶子节点数差别不大于一.
4. 用C++实现LRU cache.
感觉自己当天状态不错,问题回答不是完美,但都答出来了.但最后还是悲剧,不明白什么原因.
难道他们要看无Bug秒过? 我觉得我所表现的现场发现问题,解决问题的能力更有价值呵
 *
 * */

#include "henry.h"

// https://upload.wikimedia.org/wikipedia/commons/9/9c/KDTree-animation.gif
// https://stackoverflow.com/questions/1627305/nearest-neighbor-k-d-tree-wikipedia-proof
// https://stackoverflow.com/questions/25121878/2d-segment-quad-tree-explanation-with-c

// TODO
/* https://math.stackexchange.com/questions/7356/how-to-find-rectangle-intersection-on-a-coordinate-plane
Rectangle r1 = rect1;
Rectangle r2 = rect2;
Rectangle intersectionRect = null;

int leftX   = Math.max( r1.getX(), r2.getX() );
int rightX  = Math.min( r1.getX() + r1.getWidth(), r2.getX() + r2.getWidth() );
int topY    = Math.max( r1.getY(), r2.getY() );
int bottomY = Math.min( r1.getY() + r1.getHeight(), r2.getY() + r2.getHeight() );

if ( leftX < rightX && topY < bottomY ) {
  intersectionRect = new Rectangle( leftX, topY, rightX-leftX, bottomY-topY );
} else {
  // Rectangles do not overlap, or overlap has an area of zero (edge/corner overlap)
}
*/

struct Point {
  double x, y;

  Point(double _x, double _y) : x(_x), y(_y) {}

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

//--------------------> x  (coordinates of 4th quandrant)
// |
// |     l
// |
// v               r
// y

struct BB { // bounding box or RECT
  Point tl;
  Point br;

  BB(Point x, Point y) { tl = x, br = y; }

  BB() {}

  int width() { return br.x - tl.x; }

  int height() { return br.y - tl.y; }

  Point centroid() { return Point{(br.x - tl.x) / 2.0, (br.y - tl.y) / 2.0}; }

  bool is_overlap(const BB& o){
    return !(o.tl.x>br.x|| o.br.x<tl.x || o.tl.y>br.y || o.br.y<tl.y);
  }

  bool contain(const Point &p) const{
    return tl.x<=p.x && p.x<=br.x && tl.y<=p.y && p.y<=br.y;
  }
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
  BB bb;
  // Contains details of node
  vector<Node *> nodes; // all nodes located in bb/quadtree
  // Children of this tree
  array<quadtree *, 4> children; // *tl, *tr, *bl, *br
  //quadtree *tl, *tr, *bl, *br; // could be a vector
  const int MIN_BB_LEN = 4;

  Node *nn_dfs(const Point &p, int &mx2);

  void knn_dfs(const Point &p, int &mx2, PriorityQueueT &);

  void neighbors_in_circle_dfs(const Point &p, int distance, vector<Node *> &);
  void neighbors_in_rect_dfs(const BB &o, vector<Node *> &r);

public:
  quadtree(Point topL, Point botR);

  quadtree(const BB &b);

  void insert(Node *);

  // Queries
  // point query
  Node *point_query(Point);// search point to get Node(and data)
  // range_query
  vector<Node *> neighbors_in_rect(const BB &);

  vector<Node *> neighbors_in_circle(const Point &p, int distance); // neighbors in k miles


  Node *nn(const Point &); // nearest neighbor
  vector<Node *> knn(const Point &p, int k); // k nearest neighbor
  bool inBB(Point); // inside bounding box
};

quadtree::quadtree(Point topL, Point botR) {
  l = topL;
  r = botR;
  bb = {topL, botR};
  fill(children.begin(), children.end(), nullptr);
}

quadtree::quadtree(const BB &b) {
  bb = b;
  fill(children.begin(), children.end(), nullptr);
}


// Check if current quadtree contains the point
bool quadtree::inBB(Point p) { // depends on the direction of coordinate system
  return (p.x >= bb.tl.x && p.x <= bb.br.x && p.y >= bb.tl.y && p.y <= bb.br.y);
}

// Insert a node into the quadtree
void quadtree::insert(Node *node) {
  if (node == NULL || !inBB(node->pos)) // Current quad cannot contain it
    return;
  // We are at a quad of unit area, We cannot subdivide this quad further
  if (bb.width() <= MIN_BB_LEN && bb.height() <= MIN_BB_LEN) {
    nodes.push_back(node);
    return;
  }

  if (bb.centroid().x >= node->pos.x) {
    // Indicates tl
    if (bb.centroid().y >= node->pos.y) {
      if (children[0] == NULL)
        children[0] = new quadtree(BB{bb.tl, {bb.centroid().x, bb.centroid().y}});
      children[0]->insert(node);
    } else { // Indicates bl
      if (children[1] == NULL)
        children[1] = new quadtree(Point(bb.tl.x, (bb.tl.y + bb.br.y) / 2), Point((bb.tl.x + bb.br.x) / 2, bb.br.y));
      children[1]->insert(node);
    }
  } else {// Indicates tr
    if ((bb.tl.y + bb.br.y) / 2 >= node->pos.y) {
      if (children[2] == NULL)
        children[2] = new quadtree(Point((bb.tl.x + bb.br.x) / 2, bb.tl.y), Point(bb.br.x, (bb.tl.y + bb.br.y) / 2));
      children[2]->insert(node);
    } else { // Indicates br
      if (children[3] == NULL)
        children[3] = new quadtree(Point((bb.tl.x + bb.br.x) / 2, (bb.tl.y + bb.br.y) / 2), Point(bb.br.x, bb.br.y));
      children[3]->insert(node);
    }
  }
}

// Find a node in a quadtree
Node *quadtree::point_query(Point p) {
  // Current quad cannot contain it
  if (!inBB(p))
    return NULL;
  // We are at a quad of unit length, We cannot subdivide this quad further
  if (!nodes.empty()) { // ONLY leaf nodes have data information
    for (Node *nd: nodes) {
      if (nd->pos.x == p.x && nd->pos.y == p.y)
        return nd;
    }
    return NULL;
  }
  if ((bb.tl.x + bb.br.x) / 2 >= p.x) {
    if ((bb.tl.y + bb.br.y) / 2 >= p.y) { // Indicates tl
      return children[0] ? children[0]->point_query(p) : NULL;
    } else { // Indicates bl
      return children[1] ? children[1]->point_query(p) : NULL;
    }
  } else {
    if ((bb.tl.y + bb.br.y) / 2 >= p.y) { // Indicates tr
      return children[2] ? children[2]->point_query(p) : NULL;
    } else {// Indicates br
      return children[3] ? children[3]->point_query(p) : NULL;
    }
  }
}

// must build the quadtree first
vector<Node *> quadtree::neighbors_in_rect(const BB &o) {
  vector<Node *> r;
  neighbors_in_rect_dfs(o, r);
  return r;
}

void quadtree::neighbors_in_rect_dfs(const BB &o, vector<Node *> &r){
  if(bb.is_overlap(o)){
    if (!nodes.empty()) {
      for(Node* n: nodes){
        if(o.contain(n->pos)){
          r.push_back(n);
        }
      }
    }else{
      for (int i = 0; i < 4; i++) {
        if (children[i] == nullptr) continue;
        children[i]->neighbors_in_rect_dfs(o, r);
      }
    }
  }
}

vector<Node *> quadtree::neighbors_in_circle(const Point &p, int distance) {
  vector<Node *> r;
  neighbors_in_circle_dfs(p, distance * distance, r);
  return r;
}

void quadtree::neighbors_in_circle_dfs(const Point &p, int dd, vector<Node *> &r) {
  if (!inBB(p)) { //////
    // compare with (point ~ BB) distance; ~ To be improved!
    int dis_square_to_BB = min(min((bb.tl.x - p.x) * (bb.tl.x - p.x), (bb.br.x - p.x) * (bb.br.x - p.x)),
                               min((bb.tl.y - p.y) * (bb.tl.y - p.y), (bb.br.y - p.y) * (bb.br.y - p.y)));
    if (dd < dis_square_to_BB)
      return;
  }
  if (!nodes.empty()) { // leaf qt node
    for (Node *n: nodes) {
      int d = distance_square(p, n->pos);
      if (d <= dd)
        r.emplace_back(n);
    }
  } else { // other qts
    for (int i = 0; i < 4; i++) {
      if (children[i] == nullptr) continue;
      children[i]->neighbors_in_circle_dfs(p, dd, r);
    }
  }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Node *quadtree::nn(const Point &p) {
  if (!inBB(p)) return NULL;
  int distance = INT_MAX;
  return nn_dfs(p, distance);
}


Node *quadtree::nn_dfs(const Point &p, int &mx2) {
  if (!inBB(p)) { //////
    // compare with (point - BB) distance; ~ To be improved!
    int dis_square_to_BB = min(min((bb.tl.x - p.x) * (bb.tl.x - p.x), (bb.br.x - p.x) * (bb.br.x - p.x)),
                               min((bb.tl.y - p.y) * (bb.tl.y - p.y), (bb.br.y - p.y) * (bb.br.y - p.y)));
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
      if (children[i] == nullptr) continue;
      auto tmp = children[i]->nn_dfs(p, mx2);
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
  while (k-- && !q.empty()) {
    r.push_back(q.top().second), q.pop();
  }
  return r;
}

void quadtree::knn_dfs(const Point &p, int &mx2, PriorityQueueT &q) {
  if (!inBB(p)) { //////
    // compare with (point - BB) distance; ~ To be improved!
    int dis_square_to_BB = min(min((bb.tl.x - p.x) * (bb.tl.x - p.x), (bb.br.x - p.x) * (bb.br.x - p.x)),
                               min((bb.tl.y - p.y) * (bb.tl.y - p.y), (bb.br.y - p.y) * (bb.br.y - p.y)));
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
      if (children[i] == nullptr) continue;
      children[i]->knn_dfs(p, mx2, q);
    }
  }
}


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
  auto ns = qt.neighbors_in_rect({Point(0, 0), Point(8, 8)});
  assert(ns.size() == 5);
  ns = qt.neighbors_in_rect({Point(0, 0), Point(1, 1)});
  assert(ns.size() == 1);
  auto r = qt.knn(Point(3, 3), 2);
  assert(r[0]->data == 2);
  assert(r[1]->data == 1);
  assert(qt.point_query(Point(1, 1))->data == 1);
  assert(qt.point_query(Point(2, 5))->data == 2);
  assert(qt.point_query(Point(7, 6))->data == 3);
  assert(nullptr == qt.point_query(Point(5, 5)));
  assert(qt.nn(Point(3, 3))->data == 2);
  assert(qt.nn(Point(2, 3))->data == 2);
  assert(qt.nn(Point(2, 4))->data == 2);
  assert(qt.nn(Point(2, 1))->data == 1);
  auto nns = qt.neighbors_in_circle(Point(3, 3), 5);
  assert(nns.size() == 4);
  return 0;
}

}
}


#endif //PNSEI_ALL_POINTS_IN_KMILES_H
