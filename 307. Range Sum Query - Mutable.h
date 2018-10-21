#pragma once

#include "henry.h"

namespace _307 {

    class NumArray {
        vector<int> B, N;
    public:
        NumArray(vector<int> &nums) {
            B.resize(nums.size() + 1), N=B;
            for(int i = 0; i<nums.size(); i++) update(i, nums[i]);
        }
        void update(int i, int val) {
            int k = i + 1;
            int delta = val - N[k];
            while (k < B.size()) B[k] += delta, k += (k&-k);
            N[i + 1] = val;
        }
        int sumRange(int i, int j) { return getSum(j + 1) - getSum(i); }
        int getSum(int k) {
            int r = 0;
            while (k>0) r += B[k], k -= (k&-k);
            return r;
        }
    };

    //[7,2,7,2,0],update(4,6),update(0,2),update(0,9),sumRange(4,4),update(3,8),sumRange(0,4),update(4,1),sumRange(0,3),sumRange(0,4),update(0,4)
    void test() {
        vector<int> v = { 7,2,7,2,0 };
        NumArray na(v);
        na.update(4, 6);
        na.update(0, 2);
        na.update(0, 9);
        assert(na.sumRange(4, 4)==6);
        na.update(3, 8);
        assert(na.sumRange(0, 4)==32);
        na.update(4, 1);
        assert(na.sumRange(0, 3)==26);
        assert(na.sumRange(0, 4)==27);
        na.update(0, 4);
    }
}
