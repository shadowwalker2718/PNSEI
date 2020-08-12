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

import (
	"github.com/stretchr/testify/assert"
	"testing"
)

func TestDateTime_findLength(t *testing.T) {
	A := []int{1,2,3,2,1}
	B := []int{3,2,1,4,7}
	r := findLength(A, B)
	assert.Equal(t, 3, r)
}
