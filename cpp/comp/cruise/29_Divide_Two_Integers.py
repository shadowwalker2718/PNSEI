# -*- coding: utf-8 -*-
"""
Given two integers dividend and divisor, divide two integers without using multiplication, division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3

Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Note:

Both dividend and divisor will be 32-bit signed integers.
The divisor will never be 0.
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer
range: [−231,  231 − 1]. For the purpose of this problem, assume that your function returns 231 − 1 when
the division result overflows.

https://leetcode.com/problems/divide-two-integers/


https://kingsfish.github.io/2017/10/11/Leetcode-29-Divide-Two-Integers/
举个例子,假设除数为3,被除数为16,那么商应该是5.我们从2的0次幂与
除数的乘积也即20x3=3开始,幂次逐渐增加,直至超过被除数.可以看出,当
幂次达到2时刚好超过16（3x2^0+3x2^1+3x2^2=21>16).那么从3x2^2开
始往下累加,3x2^2=12<16,那么记录下2^2=4.再看3x2^1,发现3x2^2+3x2^1=18>16
,因此略过2^1=2.再看3x2^0,发现发现3x2^2+3x2^0=15<16,那么将2^0=1记录下.
次幂累加结束,计算一下商,分别记录了4和1,因此结果4+1=5,
此答案也即为最终的商.
"""


class Solution(object):
    def divide(self, x, y):
        """
        :type dividend x: int
        :type divisor y: int
        :rtype: int
        """
        if x == -2147483648 and y == -1:
            return 2147483647
        sign = -1 if (x ^ y) < 0 else 1
        x, y = abs(x), abs(y)
        m = 1
        c = [y]
        while x >= y:
            m += m  # 2^k
            y += y  # y * 2^k
            c.append(y)

        r, sm = 0, 0
        c.pop()
        for i in c[::-1]:
            m >>= 1
            if sm + i <= x:
                sm += i
                r += m
        return r * sign


sln = Solution()
assert(sln.divide(7, -3)==-2)
assert(sln.divide(10, 3)==3)
