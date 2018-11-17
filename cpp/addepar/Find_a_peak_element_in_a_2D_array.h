//
// Created by root on 11/3/18.
//

#ifndef PNSEI_FIND_A_PEAK_ELEMENT_IN_A_2D_ARRAY_H
#define PNSEI_FIND_A_PEAK_ELEMENT_IN_A_2D_ARRAY_H

/*
 *
 * An element is a peak element if it is greater than or equal to its four neighbors, left, right, top and bottom. For
 * example neighbors for A[i][j] are A[i-1][j], A[i+1][j], A[i][j-1] and A[i][j+1]. For corner elements, missing
 * neighbors are considered of negative infinite value.

Examples:

Input : 10 20 15
        21 30 14
        7  16 32
Output : 30
30 is a peak element because all its
neighbors are smaller or equal to it.
32 can also be picked as a peak.

Input : 10 7
        11 17
Output : 17

// Algo
//////////////////////////////////////////////////////////////
Consider mid column and find maximum element in it.
Let index of mid column be 'mid', value of maximum element in mid column be 'max' and maximum
 element be at 'mat[max_index][mid]'.
If max >= A[index][mid-1] & max >= A[index][pick+1], max is a peak, return max.
If max < mat[max_index][mid-1], recur for left half of matrix.
If max < mat[max_index][mid+1], recur for right half of matrix.

*/


#include "henry.h"

// https://www.geeksforgeeks.org/find-peak-element-2d-array/
namespace _addepar_find_peak_2D{

    int find_peak_2D(vector<vector<int>> m){ // T: O(C*LogR)
        if(m.empty() || m[0].empty()) return INT_MAX;
        int R=m.size(), C=m[0].size(), row_head=0, row_tail=R-1, j;
        while(row_head<row_tail){ // O(LogR)
            int row_mid= row_head+(row_tail-row_head)/2;
            int max_index=max_element(m[row_mid].begin(),m[row_mid].end())-m[row_mid].begin();  //O(C)
            bool ismax=true;
            if((row_mid-1>=0 && m[row_mid][max_index]<=m[row_mid-1][max_index]) ||
                (row_mid+1<R && m[row_mid][max_index]<=m[row_mid+1][max_index])){
                ismax=false;
            }
            if(ismax) return m[row_mid][max_index];
            // find the max of the three and narrow down the range
            if(row_mid-1>=0){
                if (row_mid+1<R && m[row_mid+1][max_index]>m[row_mid-1][max_index]){
                    row_head=row_mid+1;
                }else{
                    row_tail=row_mid-1;
                }
            }else{
                row_head=row_mid+1;
            }
        }
        return *max_element(m[row_head].begin(),m[row_head].end());
    }

    void test(){
        VVI v={{10,	8,	10,	10,	2},
               {14,	13,	12,	11,	13},
               {15,	9,	11,	21,	7},
               {16,	17,	19,	20,	18}};
        set<int> r={21};
        assert(r.count(find_peak_2D(v)));

        v={{10,	8,	10,	10,	2}};
        r={10};
        assert(r.count(find_peak_2D(v)));

        v={{10,	8,	10,	10,	2},
           {14,	13,	12,	11,	13}};
        r={13,14};
        assert(r.count(find_peak_2D(v)));
    }
}

#endif //PNSEI_FIND_A_PEAK_ELEMENT_IN_A_2D_ARRAY_H
