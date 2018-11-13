cmake_minimum_required(VERSION 3.12)
project(pnsei)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
#SET(CMAKE_CXX_FLAGS -lstdc++fs)


include_directories(.)

add_executable(pnsei
        leetcode/149_Max_Points_on_a_Line.h
        "leetcode/208_Implement_Trie_Prefix_Tree_ext.h"
        leetcode/208_Implement_Trie_Prefix_Tree.h
        "leetcode/214_Shortest_Palindrome.h"
        "leetcode/230_Kth_Smallest_Element_in_a_BST.h"
        "leetcode/254_Factor_Combinations.h"
        "leetcode/307_Range_Sum_Query_Mutable_Fenwick.h"
        "leetcode/34_Search_for_a_Range.h"
        "leetcode/361_Bomb_Enemy.h"
        "leetcode/388_Longest_Absolute_File_Path.h"
        "leetcode/391_Perfect_Rectangle.h"
        "leetcode/394_Decode_String.h"
        "leetcode/407_Trapping_Rain_Water_II.h"
        "leetcode/42_Trapping_Rain_Water.h"
        "leetcode/422_Valid_Word_Square.h"
        "leetcode/425_Word_Squares.h"
        "leetcode/65_Valid_Number.h"
        "leetcode/68_Text_Justification.h"
        leetcode/438_Find_All_Anagrams_in_a_String.h
        "leetcode/94_Binary_Tree_Inorder_Traversal.h"
        "leetcode/99_Recover_Binary_Search_Tree.h"
        linkedin/all_palindrome_subsequences.h
        avl.h
        utils/binarytree.h
        linkedin/blowoff_leaf.h
        concurrency_parallel/BoundedBlockingQueue.h
        google/bzoj1090.h
        calendar.h
        linkedin/canPlaceFlower.h
        comb_sum.h
        addepar/concurrent_hashmap.h
        concurrency_parallel/deadlock.h
        concurrency_parallel/DelayQueue.h
        concurrency_parallel/deadlock.cpp
        dup.h
        encode_list_with_dups.h
        linkedin/frequent_element.h
        google/gg_findmaxwith1flip.h
        google/gg_intrange.h
        concurrency_parallel/h2o.h
        linkedin/hangman.h
        "HDU_1254.h"
        henry.h
        IndexMaxPQ.h
        linkedin/intersected.h
        justifytextline.h
        "Kth_Smallest_in_Lexicographical_Order.h"
        kangaroos.h
        knighttour.h
        KNN.h
        ksum.h
        cruise/LFU.h
        _linkedlist.h
        linkedin/addinterval.h
        linkedin/midstack.h
        main.cpp
        linkedin/maxstack.h
        minwindowsub.h
        MultiDimensionArray.h
        print_matrix.h
        reliterator.h
        reverse_string.h
        segregate_even_odd_ll.h
        serialize_tree.h
        shortest_non_substring.h
        skiplist.h
        sparsematrix.h
        stree.h
        addepar/winner_tree.h "leetcode/927_Three_Equal_Parts.h" cruise/clique.h cruise/distributed_LRU.h cruise/encircular.h "dropbox/289_Game_of_Life.h"
        "dropbox/highest_minimum_sharpness.h"
        "dropbox/highest_minimum_sharpness.cpp"
        "addepar/addepar.h"
        "addepar/addepar.cpp" dropbox/find_duplicate_files.h dropbox/id_allocator_segment_tree.h dropbox/web_crawler.h dropbox/message_queue.h dropbox/highest_minimum_sharpness.h dropbox/bittorrent_merge.h dropbox/key_value_store.h leetcode/655_Print_Binary_Tree.h graph/MST_Kruskal_Prim.cpp graph/MST_Kruskal_Prim.h graph/SS_Dijkstra_Shortest.cpp graph/graph.h graph/787_Cheapest_Flights_Within_K_Stops.cpp graph/787_Cheapest_Flights_Within_K_Stops.h graph/_785_Is_Graph_Bipartite.h addepar/local_minimum_tree.h addepar/stock_reconciliation.h addepar/44_Wildcard_Matching.h addepar/10_Regular_Expression_Matching.h leetcode/307_Range_Sum_Query_Mutable_segmentTree.h utils/binarytree.cpp bolt/Remove_brackets_from_an_algebraic_string.h addepar/Find_a_peak_element_in_a_2D_array.h addepar/162_Find_Peak_Element.h addepar/109_Convert_Sorted_List_to_Binary_Search_Tree.h addepar/segment_tree.h addepar/37_Sudoku_Solver.h addepar/wildcard_simplified.h leetcode/935_Knight_Dialer.h addepar/465_Optimal_Account_Balancing.h addepar/8puzzle_AStar.h addepar/43_Multiply_Strings.h addepar/121_Best_Time_to_Buy_and_Sell_Stock.h addepar/boggle.h addepar/329_Longest_Increasing_Path_in_a_Matrix.h cruise/number_of_islands_variant1.h cruise/closest_car.h cruise/no_or_single_parent_graph.h cruise/224_Basic_Calculator.h cruise/build_tree_by_indentation.h cruise/overlap_interval.h cruise/all_points_in_Kmiles.h cruise/task_scheduler_with_cooldown.h cruise/529_Minesweeper.h cruise/dup_strings_in_two_arrays.h cruise/union_find.h cruise/euclidean_clustering.h cruise/oa.h cruise/real_time_moving_average.h cruise/word_cloud.h cruise/kalman_filter.h cruise/heatmap_argmax.h cruise/overlap_polygon.h cruise/design_excel.h cruise/166_Fraction_to_Recurring_Decimal.h cruise/RANSAC.h cruise/reversing_strings_inside_parentheses.h cruise/308_Range_Sum_Query_2D_Mutable.h cruise/816_Ambiguous_Coordinates.h cruise/227_Basic_Calculator_II.h cruise/150_Evaluate_Reverse_Polish_Notation.h cruise/304_Range_Sum_Query_2D_Immutable.h cruise/Pairwise_swap_elements_of_a_given_linked_list.h cruise/interval_subtraction.h uber/267_Palindrome_Permutation_II.h uber/160_Intersection_of_Two_Linked_Lists.h uber/uber_LRU_optimized_delete.h)

target_link_libraries(${PROJECT_NAME} stdc++fs)
