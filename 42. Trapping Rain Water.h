#pragma once

#include "henry.h"

namespace _42 {
    struct Solution {// maxMinMax
        int trap(vector<int>& A) {
            int L = A.size(), left = 0, right = L - 1, res = 0, maxleft = 0, maxright = 0;
            while (left <= right) {
                if (A[left] <= A[right]) {
                    if (A[left] >= maxleft) maxleft = A[left];
                    else res += maxleft - A[left];
                    left++;
                } else {
                    if (A[right] >= maxright) maxright = A[right];
                    else res += maxright - A[right];
                    right--;
                }
            }
            return res;
        }
    };

    struct Solution2 {// maxMinMax, 9ms
        int trap(vector<int>& height) {
            int L = height.size(), r = 0;
            if (L <= 2) return r;
            vector<int> lm(L), rm(L); // left max, right max
            for (int i = 0, t = 0; i<L; ++i) lm[i] = t = max(t, height[i]);
            for (int i = L - 1, t = 0; i >= 0; --i) rm[i] = t = max(t, height[i]);
            for (int i = 1; i<L - 1; ++i) // ignore the first and last point safely
                r += max(min(lm[i - 1], rm[i + 1]) - height[i], 0);
            return r;
        }
    };

    void test() {
        Solution sln;
        vector<int> vi = { 0,1,0,2,1,0,1,3,2,1,2,1 };
        assert(sln.trap(vi)==6);
    }

    void test2() {
        Solution2 sln;
        vector<int> vi = { 0,1,0,2,1,0,1,3,2,1,2,1 };
        assert(sln.trap(vi)==6);
    }
}