//
// Created by root on 11/3/18.
//

#ifndef PNSEI_162_FIND_PEAK_ELEMENT_H
#define PNSEI_162_FIND_PEAK_ELEMENT_H

#include "henry.h"

// https://leetcode.com/problems/find-peak-element/description/
namespace _162{
    int findPeakElement(vector<int>& nums) {
        int h=0, t=nums.size()-1;
        while(h<t){
            int m=h+(t-h)/2; // lower median
            if(nums[m] > nums[m+1]){
                t=m;
            }else h=m+1;
        }
        return h; // h==t
    }

    void test(){
        VI v={1,2,3,1};
        assert(findPeakElement(v)==2);
        v={1,2,1,3,5,6,4};
        int r=findPeakElement(v);
        assert(r==2 or r==5);
    }
}

#endif //PNSEI_162_FIND_PEAK_ELEMENT_H
