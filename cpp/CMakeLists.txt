cmake_minimum_required(VERSION 3.12)
project(pnsei)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
#SET(CMAKE_CXX_FLAGS -lstdc++fs)


include_directories(.)

add_executable(pnsei
        oj/leetcode/149_Max_Points_on_a_Line.h
        "oj/leetcode/208_Implement_Trie_Prefix_Tree_ext.h"
        oj/leetcode/208_Implement_Trie_Prefix_Tree.h
        "oj/leetcode/214_Shortest_Palindrome.h"
        "oj/leetcode/230_Kth_Smallest_Element_in_a_BST.h"
        "practice/linkedin/254_Factor_Combinations.h"
        "oj/leetcode/307_Range_Sum_Query_Mutable_Fenwick.h"
        "oj/leetcode/34_Search_for_a_Range.h"
        "oj/leetcode/361_Bomb_Enemy.h"
        "oj/leetcode/388_Longest_Absolute_File_Path.h"
        "oj/leetcode/391_Perfect_Rectangle.h"
        "oj/leetcode/394_Decode_String.h"
        "oj/leetcode/407_Trapping_Rain_Water_II.h"
        "oj/leetcode/42_Trapping_Rain_Water.h"
        "oj/leetcode/422_Valid_Word_Square.h"
        "oj/leetcode/425_Word_Squares.h"
        "oj/leetcode/65_Valid_Number.h"
        "oj/leetcode/68_Text_Justification.h"
        oj/leetcode/438_Find_All_Anagrams_in_a_String.h
        "oj/leetcode/94_Binary_Tree_Inorder_Traversal.h"
        "oj/leetcode/99_Recover_Binary_Search_Tree.h"
        practice/linkedin/all_palindrome_subsequences.h
        others/todo_avl.h
        utils/todo_binarytree.h
        practice/linkedin/blowoff_leaf.h
        concurrency_parallel/BoundedBlockingQueue.h
        practice/google/bzoj1090.h
        others/calendar.h
        practice/linkedin/605_Can_Place_Flowers.h
        others/comb_sum.h
        concurrency_parallel/concurrent_hashmap.h
        concurrency_parallel/deadlock.h
        concurrency_parallel/DelayQueue.h
        concurrency_parallel/deadlock.cpp
        others/dup.h
        practice/bloomberg/encode_list_with_dups.h
        practice/linkedin/frequent_element.h
        practice/google/gg_findmaxwith1flip.h
        practice/google/gg_intrange.h
        concurrency_parallel/h2o.h
        practice/linkedin/hangman.h
        "others/HDU_pushbox.h"
        henry.h
        others/IndexMaxPQ.h
        practice/linkedin/intersected.h
        others/justifytextline.h
        "others/Kth_Smallest_in_Lexicographical_Order.h"
        others/kangaroos.h
        others/knighttour.h
        others/KNN.h
        others/ksum.h
        practice/cruise/LFU.h
        others/_linkedlist.h
        practice/linkedin/addinterval.h
        practice/linkedin/midstack.h
        main.cpp
        practice/linkedin/maxstack.h
        oj/leetcode/76_Minimum_Window_Substring.h
        others/MultiDimensionArray.h
        others/print_matrix.h
        others/reliterator.h
        others/reverse_string.h
        others/segregate_even_odd_ll.h
        others/serialize_tree.h
        others/shortest_non_substring.h
        others/skiplist.h
        others/sparsematrix.h
        others/stree.h
        practice/addepar/winner_tree.h "oj/leetcode/927_Three_Equal_Parts.h" practice/cruise/clique.h practice/cruise/distributed_LRU.h practice/cruise/encircular.h "practice/dropbox/todo_289_Game_of_Life.h"
        "practice/dropbox/highest_minimum_sharpness.h"
        "practice/addepar/kway_merge_file.h"
        "practice/addepar/kway_merge_file.cpp" practice/dropbox/find_duplicate_files.h practice/dropbox/id_allocator_segment_tree.h practice/dropbox/web_crawler.h
        practice/dropbox/message_queue.h practice/dropbox/highest_minimum_sharpness.h practice/dropbox/bittorrent_merge.h practice/dropbox/key_value_store.h
        oj/leetcode/655_Print_Binary_Tree.h graph/MST_Kruskal_Prim.h graph/SS_Dijkstra_Shortest.h
        graph/787_Cheapest_Flights_Within_K_Stops.h
        graph/_785_Is_Graph_Bipartite.h practice/addepar/local_minimum_tree.h practice/addepar/stock_reconciliation.h
        oj/leetcode/44_Wildcard_Matching.h oj/leetcode/10_Regular_Expression_Matching.h
        practice/cruise/307_Range_Sum_Query_Mutable_segmentTree.h utils/todo_binarytree.cpp
        practice/bolt/Remove_brackets_from_an_algebraic_string.h practice/addepar/Find_a_peak_element_in_a_2D_array.h
        oj/leetcode/162_Find_Peak_Element.h oj/leetcode/109_Convert_Sorted_List_to_Binary_Search_Tree.h practice/addepar/segment_tree.h
        oj/leetcode/37_Sudoku_Solver.h practice/addepar/wildcard_simplified.h oj/leetcode/935_Knight_Dialer.h
        oj/leetcode/465_Optimal_Account_Balancing.h practice/addepar/8puzzle_AStar.h oj/leetcode/43_Multiply_Strings.h
        oj/leetcode/121_Best_Time_to_Buy_and_Sell_Stock.h practice/addepar/boggle.h oj/leetcode/329_Longest_Increasing_Path_in_a_Matrix.h
        practice/cruise/number_of_islands_variant1.h practice/cruise/closest_car.h practice/cruise/no_or_single_parent_graph.h
        practice/cruise/224_Basic_Calculator.h practice/cruise/build_tree_by_indentation.h practice/cruise/overlap_interval.h
        practice/cruise/all_points_in_Kmiles.h practice/cruise/todo_task_scheduler_with_cooldown.h practice/cruise/529_Minesweeper.h
        practice/cruise/dup_strings_in_two_arrays.h practice/cruise/todo_union_find.h practice/cruise/todo_euclidean_clustering.h practice/cruise/oa.h
        practice/cruise/real_time_moving_average.h practice/cruise/word_cloud.h practice/cruise/kalman_filter.h practice/cruise/todo_heatmap_argmax.h
        practice/cruise/todo_overlap_polygon.h practice/cruise/design_excel.h practice/cruise/166_Fraction_to_Recurring_Decimal.h practice/cruise/RANSAC.h
        practice/cruise/reversing_strings_inside_parentheses.h practice/cruise/308_Range_Sum_Query_2D_Mutable.h
        practice/cruise/816_Ambiguous_Coordinates.h practice/cruise/227_Basic_Calculator_II.h practice/cruise/150_Evaluate_Reverse_Polish_Notation.h
        practice/cruise/304_Range_Sum_Query_2D_Immutable.h practice/cruise/Pairwise_swap_elements_of_a_given_linked_list.h
        practice/cruise/interval_subtraction.h practice/uber/267_Palindrome_Permutation_II.h practice/uber/160_Intersection_of_Two_Linked_Lists.h
        practice/uber/uber_LRU_customized_eviction.h practice/uber/short_message_formatting.h oj/leetcode/22_Generate_Parentheses.h
        oj/leetcode/200_Number_of_Islands.h oj/leetcode/305_Number_of_Islands_II.h oj/leetcode/406_Queue_Reconstruction_by_Height.h
        oj/leetcode/694_Number_of_Distinct_Islands.h "oj/leetcode/711_Number_of_Distinct_Islands_II.h"
        practice/uber/359_Logger_Rate_Limiter.h practice/uber/rate_limiter_Token_Bucket.h cplusplus/mytime.h oj/leetcode/18_4Sum.h oj/leetcode/454_4Sum_II.h oj/leetcode/943_Find_the_Shortest_Superstring.h oj/leetcode/944_Delete_Columns_to_Make_Sorted.h oj/leetcode/464_Can_I_Win.h practice/weride/todo_postman_pass_checkpoints.h oj/leetcode/587_Erect_the_Fence.h oj/leetcode/469_Convex_Polygon.h oj/leetcode/189_Rotate_Array.h oj/leetcode/nary_tree_codec.h practice/uber/longest_poolchain.h oj/leetcode/745_Prefix_and_Suffix_Search.h practice/dropbox/isDownloadComplete.h oj/leetcode/253_Meeting_Rooms_II.h concurrency_parallel/concurrent_linkedlist.h concurrency_parallel/concurrent_queue.h concurrency_parallel/threadpool.h concurrency_parallel/objectpool.h concurrency_parallel/scopedlock.h concurrency_parallel/todo_rwlock.h practice/cruise/432_All_Oone_Data_Structure_LFU_Variant.h concurrency_parallel/memorypool.h practice/linkedin/set_cover_3rd_degree_friends.h practice/weride/shortest_path.h oj/leetcode/774_Minimize_Max_Distance_to_Gas_Station.h oj/leetcode/127_Word_Ladder.h oj/leetcode/126_Word_Ladder_II.h practice/weride/todo_480_Sliding_Window_Median.h oj/leetcode/295_Find_Median_from_Data_Stream.h oj/leetcode/285_Inorder_Successor_in_BST.h practice/weride/k_means_DP.h practice/weride/todo_poj_1160_Post_Office.h practice/weride/hamiltonian_cycle_string_chain.h practice/weride/todo_179_Largest_Number.h practice/weride/todo_864_Shortest_Path_to_Get_All_Keys.h practice/weride/N_Choose_K_with_different_prob.h concurrency_parallel/concurrent_stack.h oj/leetcode/947_Most_Stones_Removed_with_Same_Row_or_Column.h practice/cruise/segment_tree_2d.h oj/leetcode/todo_850_Rectangle_Area_II.h practice/dropbox/todo_multithread_token_bucket.h practice/linkedin/sqrt_double.h practice/weride/Fibonacci_Number.h oj/leetcode/773_sliding_puzzle.h oj/leetcode/415_Add_Strings.h oj/leetcode/todo_668_Kth_Smallest_Number_in_Multiplication_Table.h others/todo_graph_partition.h others/todo_727_Minimum_Window_Subsequence.h practice/linkedin/628_Maximum_Product_of_Three_Numbers.h practice/linkedin/256_Paint_House.h practice/linkedin/265_Paint_House_II.h practice/linkedin/150_Evaluate_Reverse_Polish_Notation.h practice/linkedin/_binary_search.h practice/linkedin/272_Closest_Binary_Search_Tree_Value_II.h practice/linkedin/onsite1.h oj/leetcode/255_Verify_Preorder_Sequence_in_Binary_Search_Tree.h oj/leetcode/98_Validate_Binary_Search_Tree.h practice/cruise/29_Divide_Two_Integers.h practice/cruise/christmas_tree.h cplusplus/cpp_faster_than_c.h practice/uber/uber_carpool.h concurrency_parallel/my_memory_order.h concurrency_parallel/my_semaphore.h practice/uber/_20181217.h cplusplus/profiler.h oj/leetcode/962_Maximum_Width_Ramp.h oj/leetcode/459_Repeated_Substring_Pattern.h practice/uber/_20190120.h)


add_executable(pnsei_test practice/databricks/csv_query_test.cpp
        graph/SS_Dijkstra_Shortest_test.cpp
        graph/_785_Is_Graph_Bipartite_test.cpp
        practice/nightfall/stretched_tree_test.cpp
        utils/todo_binarytree.cpp
        utils/todo_binarytree_test.cpp
        )

add_executable(segment_tree utils/segtree.cpp)

IF (WIN32)
    # set stuff for windows
ELSE()
    target_link_libraries(${PROJECT_NAME} stdc++fs)
    target_link_libraries(pnsei_test gtest gtest_main)
ENDIF()
