package oj.leetcode._224;

import java.util.Stack;

public class Solution {
    public int calculate(String s) {
        int res=0, sign=1, n=s.length();
        Stack<Integer> stk = new Stack<>();
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c>='0'){
                int num=0;
                while(i<n && s.charAt(i)>='0'){
                    num=10*num + (s.charAt(i++)-'0');
                }
                res+= sign*num;
                --i;
            } else if(c=='+'){
                sign=1;
            } else if(c=='-'){
                sign=-1;
            } else if(c=='('){
                stk.push(res);
                stk.push(sign);
                res =0;
                sign = 1;
            } else if (c==')'){
                res*=stk.pop(); //result of inner block
                res+=stk.pop();
            }
        }
        return res;
    }

    public static void main(String[] args){
        Solution sln = new Solution();
        System.out.println(23==sln.calculate("(1+(4+5+2)-3)+(6+8)"));
    }
}
