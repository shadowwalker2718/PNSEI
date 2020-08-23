package oj.leetcode._7;

//Given a 32-bit signed integer, reverse digits of an integer.
//
// Example 1:
//
//
//Input: 123
//Output: 321
//
//
// Example 2:
//
//
//Input: -123
//Output: -321
//
//
// Example 3:
//
//
//Input: 120
//Output: 21
//
//
// Note:
//Assume we are dealing with an environment which could only store integers with
//in the 32-bit signed integer range: [−231, 231 − 1]. For the purpose of this pro
//blem, assume that your function returns 0 when the reversed integer overflows.
// Related Topics Math
// 👍 3591 👎 5641


public class Solution {

    // Consider 3 edge cases:
    // 1. negative number
    // 2. INT_MIN(C++), Integer.MIN_VALUE(Java)
    // 3. greater than INT_MAX after reversing
    public int reverse(int x) {
        if (x==-2147483648)
            return 0;
        if (x<0)
            return -reverse(x);
        long y=0;
        while(x>0){
            int z=x%10;
            y = y*10 + z;
            x /= 10;
        }
        // Integer.MAX_VALUE, Integer.MIN_VALUE
        if (y>2147483647)
            return 0;
        return (int)y;
    }

    public int reverseBit(int x) {
        long y=0;
        while(x>0){
            int z=x&1;
            y = y<<1 | z;
            x >>= 1;
        }
        return (int)y;
    }
}
