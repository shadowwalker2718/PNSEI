//
// Created by root on 11/3/18.
//

#ifndef PNSEI_SEGMENT_TREE_H
#define PNSEI_SEGMENT_TREE_H

#include "henry.h"
#include "utils/binarytree.h"

namespace addepar_segmenttree{

    void test(){
        vector<int> v={1,2,3,4,5};
        TreeNode* r1 = build_segment_tree_algo1(v);
        TreeNode* r2 = build_segment_tree_algo2(v);

        print_binary_tree_horizontal(r1);
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
    }


}

#endif //PNSEI_SEGMENT_TREE_H
