//
// Created by Henry Wu on 11/18/18.
//

#ifndef PNSEI_469_CONVEX_POLYGON_H
#define PNSEI_469_CONVEX_POLYGON_H

#include "henry.h"

namespace _469 {
/* https://leetcode.com/problems/convex-polygon/description/
 * ---------------------

 一道计算几何的基础题目,上次面试Google就挂在一道计算几何题目上了.为了便于说明,
 我们假设多边形的顶点是呈逆时针排列的,那么该多边形是凸多边形的充要条件是:对于多边
 形的任何一条边,其下一条边必须是不朝右拐的（可以向左拐,也可以不拐).那么如何判断
 下一条边是不朝右拐呢?假设假设当前边形成的向量是v1,下一条边形成的向量是v2,那么
 v2不朝右拐的充要条件是v1 x v2 >= 0,也就是它们形成的有向三角形的面积大于等于0,
 符合右手法则.

对于多边形顶点呈顺时针排列的情况,判断方式刚好相反.该算法的时间复杂度是O(n),空间复杂度是O(1).
---------------------

原文:https://blog.csdn.net/magicbean2/article/details/78593338

 * */
class Solution {
public:
  bool isConvex(vector<vector<int>> &points) {
    long n = points.size(), prev = 0, cur = 0;
    for (long i = 0; i < n; ++i) {
      cur = det2({points[i], points[(i + 1) % n], points[(i + 2) % n]});
      if (cur != 0) {
        if ((cur ^ prev) < 0) {
          return false;
        } else {
          prev = cur;
        }
      }
    }
    return true;
  }

private:
  long det2(const vector<vector<int>> &A) {
    return (A[1][0] - A[0][0]) * (A[2][1] - A[0][1]) - (A[1][1] - A[0][1]) * (A[2][0] - A[0][0]);
  }
};

class Solution2 {
public:
  bool isConvex(vector<vector<int>> &points) {
    long n = points.size(), prev = INT_MAX, cur = 0;
    for (long i = 0; i < n; ++i) {
      cur = det2({points[i], points[(i + 1) % n], points[(i + 2) % n]});

      if(cur==0){
        continue;
      }
      if (prev==INT_MAX){
        prev = cur;
        continue;
      }
      if ((cur^prev)<0) {
        return false;
      } else {
        prev = cur;
      }
    }
    return true;
  }

private:
  long det2(const vector<vector<int>> &A) {
    return (A[1][0] - A[0][0]) * (A[2][1] - A[0][1]) - (A[1][1] - A[0][1]) * (A[2][0] - A[0][0]);
  }
};

}


#endif //PNSEI_469_CONVEX_POLYGON_H
