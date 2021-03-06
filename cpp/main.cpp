#include "concurrency_parallel/BoundedBlockingQueue.h"
#include "concurrency_parallel/DelayQueue.h"
#include "concurrency_parallel/concurrent_hashmap.h"
#include "concurrency_parallel/concurrent_linkedlist.h"
#include "concurrency_parallel/h2o.h"
#include "concurrency_parallel/my_memory_order.h"
#include "concurrency_parallel/my_semaphore.h"
#include "concurrency_parallel/todo_rwlock.h"
#include "cplusplus/cpp_faster_than_c.h"
#include "cplusplus/mytime.h"
#include "graph/787_Cheapest_Flights_Within_K_Stops.h"
#include "graph/MST_Kruskal_Prim.h"
#include "graph/SS_Dijkstra_Shortest.h"
#include "oj/leetcode/10_Regular_Expression_Matching.h"
#include "oj/leetcode/126_Word_Ladder_II.h"
#include "oj/leetcode/127_Word_Ladder.h"
#include "oj/leetcode/149_Max_Points_on_a_Line.h"
#include "oj/leetcode/162_Find_Peak_Element.h"
#include "oj/leetcode/18_4Sum.h"
#include "oj/leetcode/208_Implement_Trie_Prefix_Tree.h"
#include "oj/leetcode/208_Implement_Trie_Prefix_Tree_ext.h"
#include "oj/leetcode/214_Shortest_Palindrome.h"
#include "oj/leetcode/295_Find_Median_from_Data_Stream.h"
#include "oj/leetcode/307_Range_Sum_Query_Mutable_Fenwick.h"
#include "oj/leetcode/314_binary-tree-vertical-order-traversal.h"
#include "oj/leetcode/34_Search_for_a_Range.h"
#include "oj/leetcode/361_Bomb_Enemy.h"
#include "oj/leetcode/388_Longest_Absolute_File_Path.h"
#include "oj/leetcode/391_Perfect_Rectangle.h"
#include "oj/leetcode/394_Decode_String.h"
#include "oj/leetcode/407_Trapping_Rain_Water_II.h"
#include "oj/leetcode/422_Valid_Word_Square.h"
#include "oj/leetcode/425_Word_Squares.h"
#include "oj/leetcode/42_Trapping_Rain_Water.h"
#include "oj/leetcode/438_Find_All_Anagrams_in_a_String.h"
#include "oj/leetcode/44_Wildcard_Matching.h"
#include "oj/leetcode/459_Repeated_Substring_Pattern.h"
#include "oj/leetcode/464_Can_I_Win.h"
#include "oj/leetcode/465_Optimal_Account_Balancing.h"
#include "oj/leetcode/587_Erect_the_Fence.h"
#include "oj/leetcode/65_Valid_Number.h"
#include "oj/leetcode/68_Text_Justification.h"
#include "oj/leetcode/722.h"
#include "oj/leetcode/76_Minimum_Window_Substring.h"
#include "oj/leetcode/927_Three_Equal_Parts.h"
#include "oj/leetcode/947_Most_Stones_Removed_with_Same_Row_or_Column.h"
#include "oj/leetcode/987.h"
#include "oj/leetcode/98_Validate_Binary_Search_Tree.h"
#include "oj/leetcode/[13]Roman to Integer.h"
#include "oj/leetcode/todo_668_Kth_Smallest_Number_in_Multiplication_Table.h"
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
#include "pnsei.h"
#include "company/addepar/8puzzle_AStar.h"
#include "company/addepar/Find_a_peak_element_in_a_2D_array.h"
#include "company/addepar/kway_merge_file.h"
#include "company/addepar/local_minimum_tree.h"
#include "company/addepar/segment_tree.h"
#include "company/addepar/stock_reconciliation.h"
#include "company/addepar/winner_tree.h"
#include "company/bloomberg/encode_list_with_dups.h"
#include "company/bolt/Remove_brackets_from_an_algebraic_string.h"
#include "company/cruise/150_Evaluate_Reverse_Polish_Notation.h"
#include "company/cruise/224_Basic_Calculator.h"
#include "company/cruise/29_Divide_Two_Integers.h"
#include "company/cruise/307_Range_Sum_Query_Mutable_segmentTree.h"
#include "company/cruise/432_All_Oone_Data_Structure_LFU_Variant.h"
#include "company/cruise/529_Minesweeper.h"
#include "company/cruise/816_Ambiguous_Coordinates.h"
#include "company/cruise/LFU.h"
#include "company/cruise/all_points_in_Kmiles.h"
#include "company/cruise/build_tree_by_indentation.h"
#include "company/cruise/clique.h"
#include "company/cruise/closest_car.h"
#include "company/cruise/distributed_LRU.h"
#include "company/cruise/interval_subtraction.h"
#include "company/cruise/no_or_single_parent_graph.h"
#include "company/cruise/number_of_islands_variant1.h"
#include "company/cruise/segment_tree_2d.h"
#include "company/databricks/csv_query.h"
#include "company/databricks/division.h"
#include "company/databricks/traverse_bt_parent.h"
#include "company/dropbox/highest_minimum_sharpness.h"
#include "company/dropbox/id_allocator_segment_tree.h"
#include "company/google/bzoj1090.h"
#include "company/google/gg_findmaxwith1flip.h"
#include "company/linkedin/254_Factor_Combinations.h"
#include "company/linkedin/272_Closest_Binary_Search_Tree_Value_II.h"
#include "company/linkedin/605_Can_Place_Flowers.h"
#include "company/linkedin/_binary_search.h"
#include "company/linkedin/addinterval.h"
#include "company/linkedin/all_palindrome_subsequences.h"
#include "company/linkedin/blowoff_leaf.h"
#include "company/linkedin/frequent_element.h"
#include "company/linkedin/intersected.h"
#include "company/linkedin/maxstack.h"
#include "company/linkedin/midstack.h"
#include "company/linkedin/onsite1.h"
#include "company/linkedin/probability.h"
#include "company/linkedin/sqrt_double.h"
#include "company/uber/_20181217.h"
#include "company/uber/longest_poolchain.h"
#include "company/uber/rate_limiter_Token_Bucket.h"
#include "company/uber/uber_LRU_customized_eviction.h"
#include "company/uber/uber_carpool.h"
#include "company/weride/Fibonacci_Number.h"
#include "company/weride/N_Choose_K_with_different_prob.h"
#include "company/weride/hamiltonian_cycle_string_chain.h"
#include "company/weride/k_means_DP.h"
#include "company/weride/todo_480_Sliding_Window_Median.h"
#include "utils/todo_binarytree.h"

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
  _224::test();

  databricks::traverse::post_order_traversal();
  databricks::traverse::pre_order_traversal();
  databricks::traverse::in_order_traversal();
  databricks::csv_query::test();
  //databricks::csv_query::parse("FROM city.csv");
  ///////////////////////////////////////////////////////////////
  // Augmented Data Structure
  ///////////////////////////////////////////////////////////////
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
  //_465_account_balancing::test();
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
  concurrency_parallel::test();
  _concurrent_hashmap::test();
  _find_dup::test();
  _knighttour::test();
  segregate_even_odd_ll::test();
  blowoff_leaf::test();
  _cruise_interval::test();
  _cruise_dijkstra::test();
  //_cruise_islands::test();
  _cruise_geometry::spatial_indices::test();
  _addepar_kway_merge::test();
  _weride_prob::test();
  _weride_hamiltonian::test();
  _weride_kmeans::test();
  _150::test();
  _816::test();
  cruise_recover_tree::test();
  _skiplist::test();
  addepar_reconcile::test();
  _winner_tree::test();
    _10::test();
  addepar_segmenttree::test();
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
  concurrency_parallel::test();
  _lnkd_totalcovered_length::test();
  _indexheap::test();
  _indexheap::test2();
  _google_MaxWithOneFlip::test();
  _lnkd_is_serialized_tree::test();
  _mytime::system_info();

  return 0;
}
