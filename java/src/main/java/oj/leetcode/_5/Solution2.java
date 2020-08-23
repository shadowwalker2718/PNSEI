package oj.leetcode._5;

import java.util.Arrays;

import static org.junit.Assert.assertEquals;

public class Solution2 {

    public String longestPalindrome(String s) {
        int L = s.length(), x = 0, y = 0;
        if (L<=1)
            return s;
        // U[i][j] is true means s[i:j] is a palindrome.
        Boolean[][] U = new Boolean[L][];
        for (int i = 0; i < L; i++) {
            U[i] = new Boolean[L];
            Arrays.fill(U[i], false);
        }
        for (int i = 0; i<L; ++i)
            U[i][i] = true;
        // Traver a upper triangular matrix
        for (int j = 0; j<L; ++j)
            for (int i = j - 1; i >= 0; --i){
                boolean charEqual = s.charAt(i) == s.charAt(j);
                if (charEqual){
                    if (j==i+1)
                        U[i][j] = true;
                    else
                        U[i][j] = U[i + 1][j - 1];
                }
                if (U[i][j]){
                    if (y-x < j-i){
                        x = i;
                        y = j;
                    }
                }
            }
        return s.substring(x, y+1);
    }
    public static void main(String[] args){
        Solution2 sln = new Solution2();
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
