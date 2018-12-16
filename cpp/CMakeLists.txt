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
        "linkedin/254_Factor_Combinations.h"
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
        todo_avl.h
        utils/todo_binarytree.h
        linkedin/blowoff_leaf.h
        concurrency_parallel/BoundedBlockingQueue.h
        google/bzoj1090.h
        calendar.h
        linkedin/605_Can_Place_Flowers.h
        comb_sum.h
        concurrency_parallel/concurrent_hashmap.h
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
        "HDU_pushbox.h"
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
        addepar/winner_tree.h "leetcode/927_Three_Equal_Parts.h" cruise/clique.h cruise/distributed_LRU.h cruise/encircular.h "dropbox/todo_289_Game_of_Life.h"
        "dropbox/highest_minimum_sharpness.h"
        "addepar/kway_merge_file.h"
        "addepar/kway_merge_file.cpp" dropbox/find_duplicate_files.h dropbox/id_allocator_segment_tree.h dropbox/web_crawler.h
        dropbox/message_queue.h dropbox/highest_minimum_sharpness.h dropbox/bittorrent_merge.h dropbox/key_value_store.h
        leetcode/655_Print_Binary_Tree.h graph/MST_Kruskal_Prim.h graph/SS_Dijkstra_Shortest.h
        graph/787_Cheapest_Flights_Within_K_Stops.h
        graph/_785_Is_Graph_Bipartite.h addepar/local_minimum_tree.h addepar/stock_reconciliation.h
        leetcode/44_Wildcard_Matching.h leetcode/10_Regular_Expression_Matching.h
        cruise/307_Range_Sum_Query_Mutable_segmentTree.h utils/todo_binarytree.cpp
        bolt/Remove_brackets_from_an_algebraic_string.h addepar/Find_a_peak_element_in_a_2D_array.h
        leetcode/162_Find_Peak_Element.h leetcode/109_Convert_Sorted_List_to_Binary_Search_Tree.h addepar/segment_tree.h
        leetcode/37_Sudoku_Solver.h addepar/wildcard_simplified.h leetcode/935_Knight_Dialer.h
        leetcode/465_Optimal_Account_Balancing.h addepar/8puzzle_AStar.h leetcode/43_Multiply_Strings.h
        leetcode/121_Best_Time_to_Buy_and_Sell_Stock.h addepar/boggle.h leetcode/329_Longest_Increasing_Path_in_a_Matrix.h
        cruise/number_of_islands_variant1.h cruise/closest_car.h cruise/no_or_single_parent_graph.h
        cruise/224_Basic_Calculator.h cruise/build_tree_by_indentation.h cruise/overlap_interval.h
        cruise/all_points_in_Kmiles.h cruise/todo_task_scheduler_with_cooldown.h cruise/529_Minesweeper.h
        cruise/dup_strings_in_two_arrays.h cruise/todo_union_find.h cruise/todo_euclidean_clustering.h cruise/oa.h
        cruise/real_time_moving_average.h cruise/word_cloud.h cruise/kalman_filter.h cruise/todo_heatmap_argmax.h
        cruise/todo_overlap_polygon.h cruise/design_excel.h cruise/166_Fraction_to_Recurring_Decimal.h cruise/RANSAC.h
        cruise/reversing_strings_inside_parentheses.h cruise/308_Range_Sum_Query_2D_Mutable.h
        cruise/816_Ambiguous_Coordinates.h cruise/227_Basic_Calculator_II.h cruise/150_Evaluate_Reverse_Polish_Notation.h
        cruise/304_Range_Sum_Query_2D_Immutable.h cruise/Pairwise_swap_elements_of_a_given_linked_list.h
        cruise/interval_subtraction.h uber/267_Palindrome_Permutation_II.h uber/160_Intersection_of_Two_Linked_Lists.h
        uber/uber_LRU_customized_eviction.h uber/short_message_formatting.h leetcode/22_Generate_Parentheses.h
        leetcode/200_Number_of_Islands.h leetcode/305_Number_of_Islands_II.h leetcode/406_Queue_Reconstruction_by_Height.h
        leetcode/694_Number_of_Distinct_Islands.h "leetcode/711_Number_of_Distinct_Islands_II.h"
        uber/359_Logger_Rate_Limiter.h uber/rate_limiter_Token_Bucket.h cplusplus/mytime.h leetcode/18_4Sum.h leetcode/454_4Sum_II.h leetcode/943_Find_the_Shortest_Superstring.h leetcode/944_Delete_Columns_to_Make_Sorted.h leetcode/464_Can_I_Win.h weride/todo_postman_pass_checkpoints.h leetcode/587_Erect_the_Fence.h leetcode/469_Convex_Polygon.h leetcode/189_Rotate_Array.h leetcode/nary_tree_codec.h uber/longest_poolchain.h leetcode/745_Prefix_and_Suffix_Search.h dropbox/isDownloadComplete.h leetcode/253_Meeting_Rooms_II.h concurrency_parallel/concurrent_linkedlist.h concurrency_parallel/concurrent_queue.h concurrency_parallel/threadpool.h concurrency_parallel/objectpool.h concurrency_parallel/scopedlock.h concurrency_parallel/todo_rwlock.h cruise/432_All_Oone_Data_Structure_LFU_Variant.h concurrency_parallel/memorypool.h linkedin/set_cover_3rd_degree_friends.h weride/shortest_path.h leetcode/774_Minimize_Max_Distance_to_Gas_Station.h leetcode/127_Word_Ladder.h leetcode/126_Word_Ladder_II.h weride/todo_480_Sliding_Window_Median.h leetcode/295_Find_Median_from_Data_Stream.h leetcode/285_Inorder_Successor_in_BST.h weride/k_means_DP.h weride/todo_poj_1160_Post_Office.h weride/hamiltonian_cycle_string_chain.h weride/todo_179_Largest_Number.h weride/todo_864_Shortest_Path_to_Get_All_Keys.h weride/N_Choose_K_with_different_prob.h concurrency_parallel/concurrent_stack.h leetcode/947_Most_Stones_Removed_with_Same_Row_or_Column.h cruise/segment_tree_2d.h leetcode/todo_850_Rectangle_Area_II.h dropbox/todo_multithread_token_bucket.h linkedin/sqrt_double.h weride/Fibonacci_Number.h leetcode/773_sliding_puzzle.h leetcode/415_Add_Strings.h leetcode/todo_668_Kth_Smallest_Number_in_Multiplication_Table.h todo_graph_partition.h todo_727_Minimum_Window_Subsequence.h linkedin/628_Maximum_Product_of_Three_Numbers.h linkedin/256_Paint_House.h linkedin/265_Paint_House_II.h linkedin/150_Evaluate_Reverse_Polish_Notation.h linkedin/_binary_search.h linkedin/272_Closest_Binary_Search_Tree_Value_II.h linkedin/onsite1.h leetcode/255_Verify_Preorder_Sequence_in_Binary_Search_Tree.h leetcode/98_Validate_Binary_Search_Tree.h cruise/29_Divide_Two_Integers.h cruise/christmas_tree.h cplusplus/cpp_faster_than_c.h uber/uber_carpool.h concurrency_parallel/my_memory_order.h concurrency_parallel/my_semaphore.h)

IF (WIN32)
    # set stuff for windows
ELSE()
    target_link_libraries(${PROJECT_NAME} stdc++fs)
ENDIF()
