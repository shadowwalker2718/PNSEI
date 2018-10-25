cmake_minimum_required(VERSION 3.12)
project(pnsei)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)
#SET(CMAKE_CXX_FLAGS -lstdc++fs)


include_directories(.)

add_executable(pnsei
        149.h
        "208. Implement Trie (Prefix Tree).h"
        208_Implement_Trie_Prefix_Tree.h
        "214. Shortest Palindrome.h"
        "230. Kth Smallest Element in a BST.h"
        "254. Factor Combinations.h"
        "307. Range Sum Query - Mutable.h"
        "34. Search for a Range.h"
        "361. Bomb Enemy.h"
        "388. Longest Absolute File Path.h"
        "391. Perfect Rectangle.h"
        "394. Decode String.h"
        "407. Trapping Rain Water II.h"
        "42. Trapping Rain Water.h"
        "422. Valid Word Square.h"
        "425. Word Squares.h"
        "65. Valid Number.h"
        "68. Text Justification.h"
        68.h
        "94. Binary Tree Inorder Traversal.h"
        "99. Recover Binary Search Tree.h"
        allLPS.h
        avl.h
        binarytree.h
        blowoff_leaf.h
        BoundedBlockingQueue.h
        bzoj1090.h
        calendar.h
        canPlaceFlower.h
        comb_sum.h
        concurrent_hashmap.h
        deadlock.h
        DelayQueue.h
        deadlock.cpp
        dup.h
        encode_list_with_dups.h
        frequent_element.h
        gg_findmaxwith1flip.h
        gg_intrange.h
        h2o.h
        hangman.h
        "HDU 1254.h"
        henry.h
        IndexMaxPQ.h
        is_intersected.h
        justifytextline.h
        "K-th Smallest in Lexicographical Order.h"
        kangaroos.h
        knighttour.h
        KNN.h
        ksum.h
        lfu.h
        ll.h
        lnkd_addinterval.h
        lnkd_midstack.h
        main.cpp
        maxstack.h
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
        winner_tree.h "927. Three Equal Parts.h" cruise/clique.h cruise/lru.h cruise/encircular.h "dropbox/289. Game of Life.h"
        "addepar/addepar.h"
        "addepar/addepar.cpp")

target_link_libraries(${PROJECT_NAME} stdc++fs)
