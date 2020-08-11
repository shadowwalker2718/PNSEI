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
        "company/linkedin/254_Factor_Combinations.h"
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
        company/linkedin/all_palindrome_subsequences.h
        todo_avl.h
        utils/todo_binarytree.h
        company/linkedin/blowoff_leaf.h
        concurrency_parallel/BoundedBlockingQueue.h
        company/google/bzoj1090.h
        calendar.h
        company/linkedin/605_Can_Place_Flowers.h
        comb_sum.h
        concurrency_parallel/concurrent_hashmap.h
        concurrency_parallel/deadlock.h
        concurrency_parallel/DelayQueue.h
        concurrency_parallel/deadlock.cpp
        dup.h
        encode_list_with_dups.h
        company/linkedin/frequent_element.h
        company/google/gg_findmaxwith1flip.h
        company/google/gg_intrange.h
        concurrency_parallel/h2o.h
        company/linkedin/hangman.h
        "HDU_pushbox.h"
        henry.h
        IndexMaxPQ.h
        company/linkedin/intersected.h
        justifytextline.h
        "Kth_Smallest_in_Lexicographical_Order.h"
        kangaroos.h
        knighttour.h
        KNN.h
        ksum.h
        company/cruise/LFU.h
        _linkedlist.h
        company/linkedin/addinterval.h
        company/linkedin/midstack.h
        main.cpp
        company/linkedin/maxstack.h
        76_Minimum_Window_Substring.h
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
        company/addepar/winner_tree.h "leetcode/927_Three_Equal_Parts.h" company/cruise/clique.h company/cruise/distributed_LRU.h company/cruise/encircular.h "company/dropbox/todo_289_Game_of_Life.h"
        "company/dropbox/highest_minimum_sharpness.h"
        "company/addepar/kway_merge_file.h"
        "company/addepar/kway_merge_file.cpp" company/dropbox/find_duplicate_files.h company/dropbox/id_allocator_segment_tree.h company/dropbox/web_crawler.h
        company/dropbox/message_queue.h company/dropbox/highest_minimum_sharpness.h company/dropbox/bittorrent_merge.h company/dropbox/key_value_store.h
        leetcode/655_Print_Binary_Tree.h graph/MST_Kruskal_Prim.h graph/SS_Dijkstra_Shortest.h
        graph/787_Cheapest_Flights_Within_K_Stops.h
        graph/_785_Is_Graph_Bipartite.h company/addepar/local_minimum_tree.h company/addepar/stock_reconciliation.h
        leetcode/44_Wildcard_Matching.h leetcode/10_Regular_Expression_Matching.h
        company/cruise/307_Range_Sum_Query_Mutable_segmentTree.h utils/todo_binarytree.cpp
        company/bolt/Remove_brackets_from_an_algebraic_string.h company/addepar/Find_a_peak_element_in_a_2D_array.h
        leetcode/162_Find_Peak_Element.h leetcode/109_Convert_Sorted_List_to_Binary_Search_Tree.h company/addepar/segment_tree.h
        leetcode/37_Sudoku_Solver.h company/addepar/wildcard_simplified.h leetcode/935_Knight_Dialer.h
        leetcode/465_Optimal_Account_Balancing.h company/addepar/8puzzle_AStar.h leetcode/43_Multiply_Strings.h
        leetcode/121_Best_Time_to_Buy_and_Sell_Stock.h company/addepar/boggle.h leetcode/329_Longest_Increasing_Path_in_a_Matrix.h
        company/cruise/number_of_islands_variant1.h company/cruise/closest_car.h company/cruise/no_or_single_parent_graph.h
        company/cruise/224_Basic_Calculator.h company/cruise/build_tree_by_indentation.h company/cruise/overlap_interval.h
        company/cruise/all_points_in_Kmiles.h company/cruise/todo_task_scheduler_with_cooldown.h company/cruise/529_Minesweeper.h
        company/cruise/dup_strings_in_two_arrays.h company/cruise/todo_union_find.h company/cruise/todo_euclidean_clustering.h company/cruise/oa.h
        company/cruise/real_time_moving_average.h company/cruise/word_cloud.h company/cruise/kalman_filter.h company/cruise/todo_heatmap_argmax.h
        company/cruise/todo_overlap_polygon.h company/cruise/design_excel.h company/cruise/166_Fraction_to_Recurring_Decimal.h company/cruise/RANSAC.h
        company/cruise/reversing_strings_inside_parentheses.h company/cruise/308_Range_Sum_Query_2D_Mutable.h
        company/cruise/816_Ambiguous_Coordinates.h company/cruise/227_Basic_Calculator_II.h company/cruise/150_Evaluate_Reverse_Polish_Notation.h
        company/cruise/304_Range_Sum_Query_2D_Immutable.h company/cruise/Pairwise_swap_elements_of_a_given_linked_list.h
        company/cruise/interval_subtraction.h company/uber/267_Palindrome_Permutation_II.h company/uber/160_Intersection_of_Two_Linked_Lists.h
        company/uber/uber_LRU_customized_eviction.h company/uber/short_message_formatting.h leetcode/22_Generate_Parentheses.h
        leetcode/200_Number_of_Islands.h leetcode/305_Number_of_Islands_II.h leetcode/406_Queue_Reconstruction_by_Height.h
        leetcode/694_Number_of_Distinct_Islands.h "leetcode/711_Number_of_Distinct_Islands_II.h"
        company/uber/359_Logger_Rate_Limiter.h company/uber/rate_limiter_Token_Bucket.h cplusplus/mytime.h leetcode/18_4Sum.h leetcode/454_4Sum_II.h leetcode/943_Find_the_Shortest_Superstring.h leetcode/944_Delete_Columns_to_Make_Sorted.h leetcode/464_Can_I_Win.h company/weride/todo_postman_pass_checkpoints.h leetcode/587_Erect_the_Fence.h leetcode/469_Convex_Polygon.h leetcode/189_Rotate_Array.h leetcode/nary_tree_codec.h company/uber/longest_poolchain.h leetcode/745_Prefix_and_Suffix_Search.h company/dropbox/isDownloadComplete.h leetcode/253_Meeting_Rooms_II.h concurrency_parallel/concurrent_linkedlist.h concurrency_parallel/concurrent_queue.h concurrency_parallel/threadpool.h concurrency_parallel/objectpool.h concurrency_parallel/scopedlock.h concurrency_parallel/todo_rwlock.h company/cruise/432_All_Oone_Data_Structure_LFU_Variant.h concurrency_parallel/memorypool.h company/linkedin/set_cover_3rd_degree_friends.h company/weride/shortest_path.h leetcode/774_Minimize_Max_Distance_to_Gas_Station.h leetcode/127_Word_Ladder.h leetcode/126_Word_Ladder_II.h company/weride/todo_480_Sliding_Window_Median.h leetcode/295_Find_Median_from_Data_Stream.h leetcode/285_Inorder_Successor_in_BST.h company/weride/k_means_DP.h company/weride/todo_poj_1160_Post_Office.h company/weride/hamiltonian_cycle_string_chain.h company/weride/todo_179_Largest_Number.h company/weride/todo_864_Shortest_Path_to_Get_All_Keys.h company/weride/N_Choose_K_with_different_prob.h concurrency_parallel/concurrent_stack.h leetcode/947_Most_Stones_Removed_with_Same_Row_or_Column.h company/cruise/segment_tree_2d.h leetcode/todo_850_Rectangle_Area_II.h company/dropbox/todo_multithread_token_bucket.h company/linkedin/sqrt_double.h company/weride/Fibonacci_Number.h leetcode/773_sliding_puzzle.h leetcode/415_Add_Strings.h leetcode/todo_668_Kth_Smallest_Number_in_Multiplication_Table.h todo_graph_partition.h todo_727_Minimum_Window_Subsequence.h company/linkedin/628_Maximum_Product_of_Three_Numbers.h company/linkedin/256_Paint_House.h company/linkedin/265_Paint_House_II.h company/linkedin/150_Evaluate_Reverse_Polish_Notation.h company/linkedin/_binary_search.h company/linkedin/272_Closest_Binary_Search_Tree_Value_II.h company/linkedin/onsite1.h leetcode/255_Verify_Preorder_Sequence_in_Binary_Search_Tree.h leetcode/98_Validate_Binary_Search_Tree.h company/cruise/29_Divide_Two_Integers.h company/cruise/christmas_tree.h cplusplus/cpp_faster_than_c.h company/uber/uber_carpool.h concurrency_parallel/my_memory_order.h concurrency_parallel/my_semaphore.h company/uber/_20181217.h cplusplus/profiler.h leetcode/962_Maximum_Width_Ramp.h leetcode/459_Repeated_Substring_Pattern.h company/uber/_20190120.h)


add_executable(pnsei_test company/databricks/csv_query_test.cpp
        graph/SS_Dijkstra_Shortest_test.cpp)

IF (WIN32)
    # set stuff for windows
ELSE()
    target_link_libraries(${PROJECT_NAME} stdc++fs)
    target_link_libraries(pnsei_test gtest gtest_main)
ENDIF()
