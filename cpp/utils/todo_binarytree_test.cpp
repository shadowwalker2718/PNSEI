#include "gtest/gtest.h"
#include "todo_binarytree.h"

/*
       36
   32       4
 12   20   1   3
5 7 9 11
*/
TEST(tree, segment_tree_build_1){
  // https://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png
  vector<int> vi = {1, 3, 5, 7, 9, 11};
  TreeNode *r = build_segment_tree_algo1(vi);
  print_binary_tree_horizontal(r);
}

/*
       36
   9       27
 4   5   16   11
1 3     7 9
*/
TEST(tree, segment_tree_build_2){
  // https://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png
  vector<int> vi = {1, 3, 5, 7, 9, 11};
  TreeNode *r = build_segment_tree_algo2(vi);
  print_binary_tree_horizontal(r);
}

TEST(segment_tree, t3){
  // check why bugs are here?
  // https://www.geeksforgeeks.org/wp-content/uploads/segment-tree1.png
  vector<int> vi = {1, 3, 5, 7, 9, 11};
  TreeNode *r = build_segment_tree_algo2(vi);
  print_binary_tree_horizontal(r);

  // https://leetcode.com/media/original_images/segtree_example_1.png
  vi = {18, 17, 13, 19, 15, 11, 20, 12, 33, 25};
  r = build_segment_tree_algo2(vi);
  print_binary_tree_horizontal(r);
  print2D(r);

  vi = {4, 5, 6, 7};
  r = build_segment_tree_algo2(vi);
  print2D(r);

  vi = {1, 2, 3, 4, 5};
  r = build_segment_tree_algo1(vi);
  print_binary_tree_horizontal(r);

  r = build_segment_tree_algo2(vi);
  print_binary_tree_horizontal(r);

}