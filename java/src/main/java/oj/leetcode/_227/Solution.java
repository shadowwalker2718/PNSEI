package oj.leetcode._227;

import java.util.Stack;

public class Solution {
    public int calculate(String s) {
        int res = 0, d = 0;
        char sign = '+';
        Stack<Integer> nums = new Stack<>();
        for (int i = 0; i < s.length(); ++i) {
            if (s.charAt(i) >= '0') {
                d = d * 10 + s.charAt(i) - '0';
            }
            if ((s.charAt(i) < '0' && s.charAt(i) != ' ') || i == s.length() - 1) {
                if (sign == '+') nums.push(d);
                if (sign == '-') nums.push(-d);
                if (sign == '*' || sign == '/') {
                    int tmp = sign == '*' ? nums.peek() * d : nums.peek() / d;
                    nums.pop();
                    nums.push(tmp);
                }
                sign = s.charAt(i);
                d = 0;
            }
        }
        while (!nums.empty()) {
            res += nums.peek();
            nums.pop();
        }
        return res;
    }
    public static void main(String[] args){
        Solution sln = new Solution();
        System.out.println(5==sln.calculate(" 3+5 / 2 "));
    }
}
