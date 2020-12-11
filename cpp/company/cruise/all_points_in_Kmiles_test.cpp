#include "all_points_in_Kmiles.h"
#include <gtest/gtest.h>

TEST(all_points_in_Kmiles, a){
  using namespace _cruise_geometry::spatial_indices;
  // http://ericandrewlewis.github.io/how-a-quadtree-works/
  // http://bl.ocks.org/llb4ll/8709363
  // https://blog.insightdatascience.com/planting-quadtrees-for-apache-flink-b396ebc80d35
  // http://danielblazevski.github.io/assets/player/KeynoteDHTMLPlayer.html#12
  // https://developer.apple.com/documentation/gameplaykit/gkquadtree
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
}