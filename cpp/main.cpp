#include "henry.h"

#include "utils/binarytree.h"
#include "HDU_1254.h"
#include "IndexMaxPQ.h"
#include "Kth_Smallest_in_Lexicographical_Order.h"
#include "MultiDimensionArray.h"
#include "comb_sum.h"
#include "concurrency_parallel/BoundedBlockingQueue.h"
#include "concurrency_parallel/DelayQueue.h"
#include "addepar/concurrent_hashmap.h"
#include "concurrency_parallel/deadlock.h"
#include "concurrency_parallel/h2o.h"
#include "cruise/clique.h"
#include "dropbox/highest_minimum_sharpness.h"
#include "dropbox/id_allocator_segment_tree.h"
#include "dup.h"
#include "encode_list_with_dups.h"
#include "google/bzoj1090.h"
#include "google/gg_findmaxwith1flip.h"
#include "justifytextline.h"
#include "kangaroos.h"
#include "knighttour.h"
#include "ksum.h"
#include "leetcode/149_Max_Points_on_a_Line.h"
#include "leetcode/208_Implement_Trie_Prefix_Tree.h"
#include "leetcode/208_Implement_Trie_Prefix_Tree_ext.h"
#include "leetcode/214_Shortest_Palindrome.h"
#include "leetcode/254_Factor_Combinations.h"
#include "leetcode/307_Range_Sum_Query_Mutable_Fenwick.h"
#include "leetcode/34_Search_for_a_Range.h"
#include "leetcode/361_Bomb_Enemy.h"
#include "leetcode/388_Longest_Absolute_File_Path.h"
#include "leetcode/391_Perfect_Rectangle.h"
#include "leetcode/394_Decode_String.h"
#include "leetcode/407_Trapping_Rain_Water_II.h"
#include "leetcode/422_Valid_Word_Square.h"
#include "leetcode/425_Word_Squares.h"
#include "leetcode/42_Trapping_Rain_Water.h"
#include "leetcode/438_Find_All_Anagrams_in_a_String.h"
#include "leetcode/65_Valid_Number.h"
#include "leetcode/68_Text_Justification.h"
#include "leetcode/927_Three_Equal_Parts.h"
#include "leetcode/94_Binary_Tree_Inorder_Traversal.h"
#include "lfu.h"
#include "linkedin/addinterval.h"
#include "linkedin/all_palindrome_subsequences.h"
#include "linkedin/blowoff_leaf.h"
#include "linkedin/canPlaceFlower.h"
#include "linkedin/frequent_element.h"
#include "linkedin/intersected.h"
#include "linkedin/maxstack.h"
#include "linkedin/midstack.h"
#include "minwindowsub.h"
#include "print_matrix.h"
#include "reliterator.h"
#include "reverse_string.h"
#include "segregate_even_odd_ll.h"
#include "serialize_tree.h"
#include "shortest_non_substring.h"
#include "skiplist.h"
#include "sparsematrix.h"
#include "stree.h"
#include "addepar/winner_tree.h"
#include "graph/graph.h"
#include "graph/_785_Is_Graph_Bipartite.h"
#include "leetcode/307_Range_Sum_Query_Mutable_segmentTree.h"
#include "bolt/Remove_brackets_from_an_algebraic_string.h"

#include "addepar/addepar.h"
#include "addepar/stock_reconciliation.h"
#include "addepar/44_Wildcard_Matching.h"
#include "addepar/local_minimum_tree.h"
#include "addepar/Find_a_peak_element_in_a_2D_array.h"
#include "addepar/162_Find_Peak_Element.h"
#include "addepar/segment_tree.h"
#include "addepar/10_Regular_Expression_Matching.h"
#include "addepar/465_Optimal_Account_Balancing.h"
#include "addepar/8puzzle_AStar.h"
#include "addepar/37_Sudoku_Solver.h"

#include "cruise/all_points_in_Kmiles.h"
#include "cruise/build_tree_by_indentation.h"
#include "cruise/816_Ambiguous_Coordinates.h"
#include "cruise/224_Basic_Calculator.h"
#include "cruise/150_Evaluate_Reverse_Polish_Notation.h"
#include "cruise/529_Minesweeper.h"
/*class Solutionx {
public:
  vector<int> grayCode(int n) {
    if (n<1) return{ 0 };
    vector<int> r{ 0 };
    set<int> s;
    dfs(r, s, n, 0);
    return r;
  }
  void dfs(vector<int>& r, set<int>& s, int n, int x) {
    for (int i = 0; i<n; ++i) {
      int z = (x & (1 << i));
      if (z == 0) {
        int y = x | (1 << i);
        if (s.count(y)) continue;
        r.push_back(y), s.insert(y);
        dfs(r, s, n, y);
      }
    }
  }
};*/

int main(int argc, char **argv) {
  _529::test();
  _150::test();
  _224::test();
  _816::test();
  cruise_recover_tree::test();
  _cruise_geometry::__quadtree::test();
  _skiplist::test();
  _37_dfs::test();
  addepar_reconcile::test();
  _winner_tree::test();
  addepar_AStar::test();
  _465::test();
  _10::test();
  _44::test();
  addepar_segmenttree::test();
  _162::test();
  _addepar_find_peak_2D::test();
  _34::test();
  binarytree_test();
  _addepar::test();
  bolt::test();
  _307_segmentTree::test();


  _785_Is_Graph_Bipartite::test();
  graph_Dijkstra::test();
  graph_MST::test();
  _allLPS::test();
  _frequent_element::test();
  _214::test();
  _delayqueue::test();
  _68::test();
  lc_438::test();
  dropbox_find_highest_minimum_sharpness::test_find_highest_minimum_sharpness();
  dropbox_sgementtree::tes();
  addepar::test();
  cruise_2017_09_20::test();
  _927::test();

  /*Solutionx x;
  x.grayCode(2);*/

  _segment_tree::test();
  _shortest_non_substring::test();
  _RLEIterator::test();
  minwindowsub::test();

  _comb_sum::test();

  _canPlaceFlower::test();

  _winner_tree::test();

  _reverse_string::test();

  _sparsematrix::test();

  _kangaroos::test();

  _254::test();

  _concurrent_hashmap::test();

  _find_dup::test();
  _knighttour::test();
  segregate_even_odd_ll::test();
  blowoff_leaf::test();
  _minmaxstack::test();
  K_th_Smallest_in_Lexicographical_Order::test();
  bbg_encode_list_with_dups::test();

  _multi_dimension_array::test();
  _lnkd_is_intersected::test();
  _lfu::test();
  justify_text_line::test();

  _print_matrix::test();
  _h2o::mainthread2();
  _h2o::test();
  deadlock::test();
  _linkedin::test();
  _lnkd_totalcovered_length::test();
  _149::test();

  _indexheap::test();
  _indexheap::test2();

  google::test();

  _lnkd_is_serialized_tree::test();
  _midstack::test();
  _65::test();
  _361::test();
  _42::test();
  _42::test2();

  _208::test();
  _208_ext::test();
  _391::test();
  _394::test();
  _388::test();
  _307::test();
  _425::test();
  _425::test2();
  _425::test3();

  _422::test();

  _407::test();

  _bzoj1090::test();

  _ksum::test();
  _hdu_1254::test();
  return 0;
}
