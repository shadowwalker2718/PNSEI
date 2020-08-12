package leetcode

// https://leetcode.com/problems/maximum-length-of-repeated-subarray/
/*
Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:

Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation:
The repeated subarray with maximum length is [3, 2, 1].


Note:

1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100
*/

func findLength(A []int, B []int) int {
    l1 := len(A)
    l2 := len(B)
    dp := make([][]int, l2+1)
    for i:= range l2+1 {
        dp[i] = make([]int, l1+1)
    }
    mx := 0
    for i:=1;i<l1+1;i++{
        for j:=1;j<l2+1;j++{
            if A[i-1] == B[j-1]{
                dp[i][j] = dp[i-1][j-1] + 1
            }
            mx = max(mx, dp[i][j])
        }
    }
    return mx
}
