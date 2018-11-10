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

namespace _cruise_geometry{
// C++ Implementation of Quad Tree
// Used to hold details of a point
struct Point
{
  int x;
  int y;
  Point(int _x, int _y)
  {
    x = _x;
    y = _y;
  }
  Point()
  {
    x = 0;
    y = 0;
  }
};

// The objects that we want stored in the quadtree
struct Node
{
  Point pos;
  int data;
  Node(Point _pos, int _data)
  {
    pos = _pos;
    data = _data;
  }
  Node()
  {
    data = 0;
  }
};

// The main quadtree class
class Quad
{
  // Hold details of the boundary of this node
  Point topLeft;
  Point botRight;

  // Contains details of node
  Node *n;

  // Children of this tree
  Quad *topLeftTree;
  Quad *topRightTree;
  Quad *botLeftTree;
  Quad *botRightTree;

public:
  Quad()
  {
    topLeft = Point(0, 0);
    botRight = Point(0, 0);
    n = NULL;
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
  }
  Quad(Point topL, Point botR)
  {
    n = NULL;
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    topLeft = topL;
    botRight = botR;
  }
  void insert(Node*);
  Node* search(Point);
  bool inBoundary(Point);
};

// Insert a node into the quadtree
void Quad::insert(Node *node)
{
  if (node == NULL)
    return;

  // Current quad cannot contain it
  if (!inBoundary(node->pos))
    return;

  // We are at a quad of unit area
  // We cannot subdivide this quad further
  if (abs(topLeft.x - botRight.x) <= 1 &&
      abs(topLeft.y - botRight.y) <= 1)
  {
    if (n == NULL)
      n = node;
    return;
  }

  if ((topLeft.x + botRight.x) / 2 >= node->pos.x)
  {
    // Indicates topLeftTree
    if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
    {
      if (topLeftTree == NULL)
        topLeftTree = new Quad(
            Point(topLeft.x, topLeft.y),
            Point((topLeft.x + botRight.x) / 2,
                  (topLeft.y + botRight.y) / 2));
      topLeftTree->insert(node);
    }

      // Indicates botLeftTree
    else
    {
      if (botLeftTree == NULL)
        botLeftTree = new Quad(
            Point(topLeft.x,
                  (topLeft.y + botRight.y) / 2),
            Point((topLeft.x + botRight.x) / 2,
                  botRight.y));
      botLeftTree->insert(node);
    }
  }
  else
  {
    // Indicates topRightTree
    if ((topLeft.y + botRight.y) / 2 >= node->pos.y)
    {
      if (topRightTree == NULL)
        topRightTree = new Quad(
            Point((topLeft.x + botRight.x) / 2,
                  topLeft.y),
            Point(botRight.x,
                  (topLeft.y + botRight.y) / 2));
      topRightTree->insert(node);
    }

      // Indicates botRightTree
    else
    {
      if (botRightTree == NULL)
        botRightTree = new Quad(
            Point((topLeft.x + botRight.x) / 2,
                  (topLeft.y + botRight.y) / 2),
            Point(botRight.x, botRight.y));
      botRightTree->insert(node);
    }
  }
}

// Find a node in a quadtree
Node* Quad::search(Point p)
{
  // Current quad cannot contain it
  if (!inBoundary(p))
    return NULL;

  // We are at a quad of unit length
  // We cannot subdivide this quad further
  if (n != NULL)
    return n;

  if ((topLeft.x + botRight.x) / 2 >= p.x)
  {
    // Indicates topLeftTree
    if ((topLeft.y + botRight.y) / 2 >= p.y)
    {
      if (topLeftTree == NULL)
        return NULL;
      return topLeftTree->search(p);
    }

      // Indicates botLeftTree
    else
    {
      if (botLeftTree == NULL)
        return NULL;
      return botLeftTree->search(p);
    }
  }
  else
  {
    // Indicates topRightTree
    if ((topLeft.y + botRight.y) / 2 >= p.y)
    {
      if (topRightTree == NULL)
        return NULL;
      return topRightTree->search(p);
    }

      // Indicates botRightTree
    else
    {
      if (botRightTree == NULL)
        return NULL;
      return botRightTree->search(p);
    }
  }
};

// Check if current quadtree contains the point
bool Quad::inBoundary(Point p)
{
  return (p.x >= topLeft.x &&
          p.x <= botRight.x &&
          p.y >= topLeft.y &&
          p.y <= botRight.y);
}

// Driver program
int test()
{
  Quad center(Point(0, 0), Point(8, 8));
  Node a(Point(1, 1), 1);
  Node b(Point(2, 5), 2);
  Node c(Point(7, 6), 3);
  center.insert(&a);
  center.insert(&b);
  center.insert(&c);
  cout << "Node a: " <<
       center.search(Point(1, 1))->data << "\n";
  cout << "Node b: " <<
       center.search(Point(2, 5))->data << "\n";
  cout << "Node c: " <<
       center.search(Point(7, 6))->data << "\n";
  cout << "Non-existing node: "
       << center.search(Point(5, 5));
  return 0;
}

}


#endif //PNSEI_ALL_POINTS_IN_KMILES_H
