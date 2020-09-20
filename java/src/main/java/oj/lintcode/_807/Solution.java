package oj.lintcode._807;

import com.sun.corba.se.impl.interceptors.SlotTable;

/*
Palindrome Number II
Determines whether a binary representation of a non-negative integer n is a palindrome
Example
Given n = 0, return True

Explanation:
The binary representation of 0 is: 0
Given n = 3, return True

Explanation:
The binary representation of 3 is: 11
Given n = 4, return False

Explanation:
The binary representation of 4 is: 100
Given n = 6, return False

Explanation:
The binary representation of 6 is: 110
Notice
0 <= n <= 2^32 - 1

代码如下：
注意：
s + 一个digit 可以用
int single_digit = 1;
s = s + static_cast(‘0’ + single_digit);
也可以用
s = s + to_string(single_digit);
前者更快。
*/
import static java.lang.System.out;
public class Solution {
    public Boolean isPalindrome(int n) {
        final String s = Integer.toBinaryString(n);
        return isPal(s);
    }

    private Boolean isPal(String s){
        int i=0;
        int j=s.length()-1;
        while(i<j){
            if (s.charAt(i) != s.charAt(j))
                return false;
            i++; j--;
        }
        return true;
    }

    public static void main(String[] args){
        Solution sln = new Solution();
        out.println(sln.isPalindrome(3));
        out.println(sln.isPalindrome(4));
    }
}
