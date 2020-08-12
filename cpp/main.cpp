#include "practice/addepar/8puzzle_AStar.h"
#include "practice/addepar/Find_a_peak_element_in_a_2D_array.h"
#include "practice/addepar/kway_merge_file.h"
#include "practice/addepar/local_minimum_tree.h"
#include "practice/addepar/segment_tree.h"
#include "practice/addepar/stock_reconciliation.h"
#include "practice/addepar/winner_tree.h"
#include "practice/bolt/Remove_brackets_from_an_algebraic_string.h"
#include "practice/cruise/150_Evaluate_Reverse_Polish_Notation.h"
#include "practice/cruise/224_Basic_Calculator.h"
#include "practice/cruise/29_Divide_Two_Integers.h"
#include "practice/cruise/307_Range_Sum_Query_Mutable_segmentTree.h"
#include "practice/cruise/432_All_Oone_Data_Structure_LFU_Variant.h"
#include "practice/cruise/529_Minesweeper.h"
#include "practice/cruise/816_Ambiguous_Coordinates.h"
#include "practice/cruise/LFU.h"
#include "practice/cruise/all_points_in_Kmiles.h"
#include "practice/cruise/build_tree_by_indentation.h"
#include "practice/cruise/clique.h"
#include "practice/cruise/closest_car.h"
#include "practice/cruise/distributed_LRU.h"
#include "practice/cruise/interval_subtraction.h"
#include "practice/cruise/no_or_single_parent_graph.h"
#include "practice/cruise/number_of_islands_variant1.h"
#include "practice/cruise/segment_tree_2d.h"
#include "practice/databricks/division.h"
#include "practice/databricks/sql_split.h"
#include "practice/dropbox/highest_minimum_sharpness.h"
#include "practice/dropbox/id_allocator_segment_tree.h"
#include "practice/google/bzoj1090.h"
#include "practice/google/gg_findmaxwith1flip.h"
#include "practice/linkedin/254_Factor_Combinations.h"
#include "practice/linkedin/272_Closest_Binary_Search_Tree_Value_II.h"
#include "practice/linkedin/605_Can_Place_Flowers.h"
#include "practice/linkedin/_binary_search.h"
#include "practice/linkedin/addinterval.h"
#include "practice/linkedin/all_palindrome_subsequences.h"
#include "practice/linkedin/blowoff_leaf.h"
#include "practice/linkedin/frequent_element.h"
#include "practice/linkedin/intersected.h"
#include "practice/linkedin/maxstack.h"
#include "practice/linkedin/midstack.h"
#include "practice/linkedin/onsite1.h"
#include "practice/linkedin/probability.h"
#include "practice/linkedin/sqrt_double.h"
#include "practice/uber/_20181217.h"
#include "practice/uber/_20190120.h"
#include "practice/uber/longest_poolchain.h"
#include "practice/uber/rate_limiter_Token_Bucket.h"
#include "practice/uber/thumbtack.h"
#include "practice/uber/uber_LRU_customized_eviction.h"
#include "practice/uber/uber_carpool.h"
#include "practice/weride/Fibonacci_Number.h"
#include "practice/weride/N_Choose_K_with_different_prob.h"
#include "practice/weride/hamiltonian_cycle_string_chain.h"
#include "practice/weride/k_means_DP.h"
#include "practice/weride/todo_480_Sliding_Window_Median.h"
#include "concurrency_parallel/BoundedBlockingQueue.h"
#include "concurrency_parallel/DelayQueue.h"
#include "concurrency_parallel/concurrent_hashmap.h"
#include "concurrency_parallel/concurrent_linkedlist.h"
#include "concurrency_parallel/deadlock.h"
#include "concurrency_parallel/h2o.h"
#include "concurrency_parallel/my_memory_order.h"
#include "concurrency_parallel/my_semaphore.h"
#include "concurrency_parallel/todo_rwlock.h"
#include "cplusplus/cpp_faster_than_c.h"
#include "cplusplus/mytime.h"
#include "graph/787_Cheapest_Flights_Within_K_Stops.h"
#include "graph/MST_Kruskal_Prim.h"
#include "graph/SS_Dijkstra_Shortest.h"
#include "graph/_785_Is_Graph_Bipartite.h"
#include "henry.h"
#include "leetcode/10_Regular_Expression_Matching.h"
#include "leetcode/126_Word_Ladder_II.h"
#include "leetcode/127_Word_Ladder.h"
#include "leetcode/149_Max_Points_on_a_Line.h"
#include "leetcode/162_Find_Peak_Element.h"
#include "leetcode/18_4Sum.h"
#include "leetcode/208_Implement_Trie_Prefix_Tree.h"
#include "leetcode/208_Implement_Trie_Prefix_Tree_ext.h"
#include "leetcode/214_Shortest_Palindrome.h"
#include "leetcode/295_Find_Median_from_Data_Stream.h"
#include "leetcode/307_Range_Sum_Query_Mutable_Fenwick.h"
#include "leetcode/34_Search_for_a_Range.h"
#include "leetcode/361_Bomb_Enemy.h"
#include "leetcode/37_Sudoku_Solver.h"
#include "leetcode/388_Longest_Absolute_File_Path.h"
#include "leetcode/391_Perfect_Rectangle.h"
#include "leetcode/394_Decode_String.h"
#include "leetcode/407_Trapping_Rain_Water_II.h"
#include "leetcode/422_Valid_Word_Square.h"
#include "leetcode/425_Word_Squares.h"
#include "leetcode/42_Trapping_Rain_Water.h"
#include "leetcode/438_Find_All_Anagrams_in_a_String.h"
#include "leetcode/44_Wildcard_Matching.h"
#include "leetcode/459_Repeated_Substring_Pattern.h"
#include "leetcode/464_Can_I_Win.h"
#include "leetcode/465_Optimal_Account_Balancing.h"
#include "leetcode/587_Erect_the_Fence.h"
#include "leetcode/65_Valid_Number.h"
#include "leetcode/68_Text_Justification.h"
#include "leetcode/76_Minimum_Window_Substring.h"
#include "leetcode/927_Three_Equal_Parts.h"
#include "leetcode/947_Most_Stones_Removed_with_Same_Row_or_Column.h"
#include "leetcode/94_Binary_Tree_Inorder_Traversal.h"
#include "leetcode/98_Validate_Binary_Search_Tree.h"
#include "leetcode/[13]Roman to Integer.h"
#include "leetcode/todo_668_Kth_Smallest_Number_in_Multiplication_Table.h"
#include "others/HDU_pushbox.h"
#include "others/IndexMaxPQ.h"
#include "others/Kth_Smallest_in_Lexicographical_Order.h"
#include "others/MultiDimensionArray.h"
#include "others/comb_sum.h"
#include "others/dup.h"
#include "others/justifytextline.h"
#include "others/kangaroos.h"
#include "others/knighttour.h"
#include "others/ksum.h"
#include "others/print_matrix.h"
#include "others/reliterator.h"
#include "others/reverse_string.h"
#include "others/segregate_even_odd_ll.h"
#include "others/serialize_tree.h"
#include "others/shortest_non_substring.h"
#include "others/skiplist.h"
#include "others/sparsematrix.h"
#include "others/stree.h"
#include "practice/bloomberg/encode_list_with_dups.h"
#include "utils/todo_binarytree.h"

#include "leetcode/722.h"
#include "leetcode/987.h"
#include "leetcode/314_binary-tree-vertical-order-traversal.h"
#include "practice/databricks/csv_query.h"
#include "practice/databricks/traverse_bt_parent.h"
#include "practice/databricks/sql_comment.h"


bool abbyDeng(vector<int> vi){
  int mx = -1;
  vector<int> stk;
  for(int e: vi){
    if (!stk.empty()){
      if (e != stk.back() && e<=mx){
        return false;
      } else if(e==stk.back()){
        stk.pop_back();
      }
    }
    for(int j=mx+1;j<e;j++)
      stk.push_back(j);
    mx = max(e,mx);
  }
  return true;
}

int main(int argc, char **argv) {

  ///////////////////////////////////////////////////////////////
  // Augmented Data Structure
  ///////////////////////////////////////////////////////////////
  //
  // Cache-eviction related
  _lfu::test();
  _lru_classic::test();
  _432::test();
  _uber_lru::test();
  _concurrent_ll::test();
  _midstack::test();
  _minmaxstack::test();
  _480_medianSlidingWindow::test();
  _295::test();

  databricks::comments::test();
  databricks::traverse::post_order_traversal();
  databricks::traverse::pre_order_traversal();
  databricks::traverse::in_order_traversal();
  databricks::csv_query::test();
  //databricks::csv_query::parse("FROM city.csv");
  databricks::sql_split::test();
  _987::test();
  _314::test();
  _314::test2();
  _722::test();
  _42::test3();
  databricks::test();
  bool b = abbyDeng({0,3,6,5,4,7,2,1});
  b = abbyDeng({7,6,5,4,3,2,1,0});
  _13::test();
  _uber_carpool::simple::test();
  _uber_rate_limiter::test();
  _459::test();
  _sgement_tree::test();
  _20181227::test3();
  _mem_order::_ordering::test();
  _cpp_c::test();
  _29::test();
  _probability::test();
  _98::test();
  lki_1::test1();
  _272::test();
  _binary_search::test();
  _canPlaceFlower::test();
  _668::test();
  _fib::test();
  _480_medianSlidingWindow::test();
  _sqrt_double::test();
  _multiparent_tree::test();
  _224::test();
  segment_tree_2d::test();
  _307_segmentTree::test();
  binarytree_test_bug();
  db_dp::test_find_highest_minimum_sharpness();
  binarytree_test();
  _947::test();

  ///////////////////////////////////////////////////////////////
  // Graph Theory
  ///////////////////////////////////////////////////////////////
  // BFS, Bi, MSBFS
  _127::test();
  _126::test();
  // Toplogical Sort, DFS, Khan Algo
  // Bipartite
  //_785_Is_Graph_Bipartite::test();
  // BF, Dijkstra
  _787::test();
  //graph_Dijkstra::test();
  // MST(Prim, Kruskal)
  graph_MST::test();


  ///////////////////////////////////////////////////////////////
  // Concurrency
  ///////////////////////////////////////////////////////////////
  _concurrency::_semaphore_example::test();
  _concurrent_shared_mutex::test();
  _uber_rate_limiter::test();
  _uber_longest_poolchain::test();
  _587::test();
  _464::test();
  _ksum::test();
  _465_account_balancing::test();
  _4sum::test();
  _bzoj1090::test();
  _hdu_1254::test();
  _529_minesweeper::test();
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
  justify_text_line::test();
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
  _print_matrix::test();
  _h2o::mainthread2();
  _h2o::test();
  deadlock::test();
  _concurrent_hashmap::test();
  _find_dup::test();
  _knighttour::test();
  segregate_even_odd_ll::test();
  blowoff_leaf::test();
  _cruise_interval::test();
  _cruise_dijkstra::test();
  _cruise_islands::test();
  _cruise_geometry::__quadtree::test();
  _addepar_kway_merge::test();
  _weride_prob::test();
  _weride_hamiltonian::test();
  _weride_kmeans::test();
  _150::test();
  _816::test();
  cruise_recover_tree::test();
  _skiplist::test();
  _37_dfs::test();
  addepar_reconcile::test();
  _winner_tree::test();
  addepar_AStar::test();
  _10::test();
  _44::test();
  addepar_segmenttree::test();
  _162::test();
  _addepar_find_peak_2D::test();
  _34::test();
  _addepar::test();
  bolt::test();
  _allLPS::test();
  _frequent_element::test();
  _214::test();
  _delayqueue::test();
  _68::test();
  lc_438::test();
  cruise_2017_09_20::test();
  _927::test();
  /*Solutionx x;
  x.grayCode(2);*/
  K_th_Smallest_in_Lexicographical_Order::test();
  bbg_encode_list_with_dups::test();
  _multi_dimension_array::test();
  _lnkd_is_intersected::test();
  _linkedin::test();
  _lnkd_totalcovered_length::test();
  _149::test();
  _indexheap::test();
  _indexheap::test2();
  _google_MaxWithOneFlip::test();
  _lnkd_is_serialized_tree::test();
  _mytime::system_info();

  return 0;
}
