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
        lfu.h
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
        winner_tree.h "leetcode/927_Three_Equal_Parts.h" cruise/clique.h cruise/lru.h cruise/encircular.h "dropbox/289. Game of Life.h"
        "dropbox/highest_minimum_sharpness.h"
        "dropbox/highest_minimum_sharpness.cpp"
        "addepar/addepar.h"
        "addepar/addepar.cpp" dropbox/find_duplicate_files.h dropbox/id_allocator.h dropbox/web_crawler.h dropbox/message_queue.h dropbox/highest_minimum_sharpness.h dropbox/bittorrent_merge.h dropbox/key_value_store.h leetcode/655_Print_Binary_Tree.h graph/MST_Kruskal_Prim.cpp graph/MST_Kruskal_Prim.h graph/SS_Dijkstra_Shortest.cpp graph/graph.h graph/787_Cheapest_Flights_Within_K_Stops.cpp graph/787_Cheapest_Flights_Within_K_Stops.h graph/_785_Is_Graph_Bipartite.h addepar/local_minimum_tree.h addepar/stock_reconciliation.h addepar/44_Wildcard_Matching.h addepar/10_Regular_Expression_Matching.h leetcode/307_Range_Sum_Query_Mutable_segmentTree.h utils/binarytree.cpp bolt/Remove_brackets_from_an_algebraic_string.h addepar/Find_a_peak_element_in_a_2D_array.h addepar/162_Find_Peak_Element.h addepar/109_Convert_Sorted_List_to_Binary_Search_Tree.h)

target_link_libraries(${PROJECT_NAME} stdc++fs)
