#include "henry.h"

#include "149_Max_Points_on_a_Line.h"
#include "208. Implement Trie (Prefix Tree).h"
#include "208_Implement_Trie_Prefix_Tree.h"
#include "214. Shortest Palindrome.h"
#include "254. Factor Combinations.h"
#include "307. Range Sum Query - Mutable.h"
#include "361. Bomb Enemy.h"
#include "388. Longest Absolute File Path.h"
#include "391. Perfect Rectangle.h"
#include "394. Decode String.h"
#include "407. Trapping Rain Water II.h"
#include "42. Trapping Rain Water.h"
#include "422. Valid Word Square.h"
#include "425. Word Squares.h"
#include "438_Find_All_Anagrams_in_a_String.h"
#include "65. Valid Number.h"
#include "68_Text_Justification.h"
#include "927. Three Equal Parts.h"
#include "94. Binary Tree Inorder Traversal.h"
#include "HDU 1254.h"
#include "IndexMaxPQ.h"
#include "K-th Smallest in Lexicographical Order.h"
#include "MultiDimensionArray.h"
#include "addepar/addepar.h"
#include "allLPS.h"
#include "blowoff_leaf.h"
#include "bzoj1090.h"
#include "canPlaceFlower.h"
#include "comb_sum.h"
#include "concurrency_parallel/BoundedBlockingQueue.h"
#include "concurrency_parallel/DelayQueue.h"
#include "concurrency_parallel/concurrent_hashmap.h"
#include "concurrency_parallel/deadlock.h"
#include "concurrency_parallel/h2o.h"
#include "cruise/clique.h"
#include "dropbox/highest_minimum_sharpness.h"
#include "dropbox/id_allocator.h"
#include "dup.h"
#include "encode_list_with_dups.h"
#include "frequent_element.h"
#include "gg_findmaxwith1flip.h"
#include "is_intersected.h"
#include "justifytextline.h"
#include "kangaroos.h"
#include "knighttour.h"
#include "ksum.h"
#include "leetcode/34_Search_for_a_Range.h"
#include "lfu.h"
#include "linkedin/lnkd_addinterval.h"
#include "linkedin/lnkd_midstack.h"
#include "maxstack.h"
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
#include "winner_tree.h"
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
  _delayqueue::test();
  _68::test();
  lc_438::test();
  dropbox::test_find_highest_minimum_sharpness();
  dropbox::tes();
  addepar::test();
  cruise_2017_09_20::test();
  _927::test();
  /*try {
    float x = 1.02, y = 0;
    cout << x / y << endl;
    int x2 = 1, y2 = 0;
    cout << x2 / y2 << endl;
  } catch (const exception& e) {
    cout << e.what() << endl;
  }*/
  /*Solutionx x;
  x.grayCode(2);*/

  _segment_tree::test();
  _shortest_non_substring::test();
  _RLEIterator::test();

  _frequent_element::test();

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
  _allLPS::test();
  _h2o::mainthread2();
  _h2o::test();
  _34::test();
  deadlock::test();
  _linkedin::test();
  _lnkd_totalcovered_length::test();
  _149::test();
  _skiplist::test();

  _indexheap::test();
  _indexheap::test2();

  google::test();

  _lnkd_is_serialized_tree::test();
  _midstack::test();
  _65::test();
  _214::test();
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
