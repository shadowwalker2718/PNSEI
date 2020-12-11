//
// Created by Henry Wu on 11/3/18.
//

#ifndef PNSEI_SEGMENT_TREE_H
#define PNSEI_SEGMENT_TREE_H

#include "pnsei.h"
#include "utils/todo_binarytree.h"

namespace addepar_segmenttree{

    void test(){
        vector<int> v={1,2,3,4,5};
        TreeNode* r1 = build_segment_tree_algo1(v);
        print_binary_tree_horizontal(r1);
        TreeNode* r2 = build_segment_tree_algo2(v);
        print_binary_tree_horizontal(r2);

        /*********************************************************************************
                          15
                  10              5
              9      1      2      3
            4  5
            ********************************************************************************
            ********************************************************************************
                          15
                  6              9
              3      3      4      5
            1  2
            ********************************************************************************
         */

        v={1,2,3,4,5,6,7,8};
        r1 = build_segment_tree_algo1(v);
        print_binary_tree_horizontal(r1);
        r2 = build_segment_tree_algo2(v);
        print_binary_tree_horizontal(r2);

        v={1,2,3,4,5,6,7,8,9,10};
        // Should not use vector<raw pointer>
        /*
         *  Strange things happen for this code
         *  The r1's 1 node was changed after building r2
         *  TO investigate.....
         *  v={1,2,3,4,5,6,7,8,9,10};
         *  r1 = build_segment_tree_algo1(v);
            r2 = build_segment_tree_algo2(v);
            print_binary_tree_horizontal(r1);
            print_binary_tree_horizontal(r2);
         *
         * */
        r1 = build_segment_tree_algo1(v);
        print_binary_tree_horizontal(r1);

        r2 = build_segment_tree_algo2(v);
        print_binary_tree_horizontal(r2);

    }


}

#endif //PNSEI_SEGMENT_TREE_H
