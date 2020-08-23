package oj.leetcode._5;

//Given a string s, find the longest palindromic substring in s. You may assume
//that the maximum length of s is 1000.
//
// Example 1:
//
//
//Input: "babad"
//Output: "bab"
//Note: "aba" is also a valid answer.
//
//
// Example 2:
//
//
//Input: "cbbd"
//Output: "bb"
//
// Related Topics String Dynamic Programming
// 👍 7595 👎 562

import static org.junit.Assert.assertEquals;

class Solution {
    public String longestPalindrome(String s) {
        int L=s.length();
        if (L<=1)
            return s;
        int g=0, start=0, k, local, l, r;
        for (int i = 0; i < L; i++) {// abxba
            k = 1;
            local=1;
            while((l=i-k)>=0 && (r=i+k)<L && s.charAt(l)==s.charAt(r)){
                local+=2;
                k++;
            }
            if (local>g){
                g=local;
                start=i-k+1;
            }
        }
        for (int i = 1; i < L; i++) {// abba
            k = 0;
            local=0;
            while((l=i-k-1)>=0 && (r=i+k)<L && s.charAt(l)==s.charAt(r)){
                local+=2;
                k++;
            }
            if (local>g){
                g=local;
                start=i-k;
            }
        }
        return s.substring(start, g);
    }

    public static void main(String[] args){
        Solution sln = new Solution();
        String r = sln.longestPalindrome("abxba");
        assertEquals(r, "abxba");

        r = sln.longestPalindrome("abbaxxx");
        assertEquals(r, "abba");

        r = sln.longestPalindrome("xx");
        assertEquals(r, "xx");

        r = sln.longestPalindrome("");
        assertEquals(r, "");
    }
}
