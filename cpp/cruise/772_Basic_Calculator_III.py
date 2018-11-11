'''
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ),
the plus + or minus sign -, non-negative integers and empty spaces .

The expression string contains only **non-negative integers**, +, -,
 *, / operators , open ( and closing parentheses ) and empty spaces .
  The integer division should truncate toward zero.

You may assume that the given expression is always valid.
 All intermediate results will be in the range of [-2147483648, 2147483647].

Some examples:

"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12

https://leetcode.com/problems/basic-calculator-iii/

https://en.wikipedia.org/wiki/Shunting-yard_algorithm
'''


class Solution(object):
    def calculate(self, s):
        """
        :type s: str
        :rtype: int
        """
        s = s.replace(' ', '')
        precedence = {'*': 1, '/': 1, '+': 0, '-': 0}

        def shunting_yard(s):  # to RPN
            n, q, k = 0, [], []  # one output queue and one operator stack
            for i in range(len(s)):
                c = s[i]
                if c.isdigit():
                    n = n * 10 + int(c)
                elif c == '(':
                    k.append(c)
                elif c == ')':
                    q.append(n)  ####
                    n = 0
                    while k[-1] != '(':
                        q.append(k.pop())
                    k.pop()
                else:
                    if i >= 1 and s[i - 1].isdigit():  ####
                        q.append(n)
                        n = 0
                    while len(k) > 0 and k[-1] != '(' and precedence[k[-1]] >= precedence[c]:
                        q.append(k.pop())
                    k.append(c)
            if len(s) > 1 and s[-1].isdigit():  ####
                q.append(n)
            while len(k) > 0:
                q.append(k.pop())
            return q

        def rpn(v):
            stk = []
            m = {'+': lambda x, y: x + y,
                 '-': lambda x, y: x - y,
                 '*': lambda x, y: x * y,
                 '/': lambda x, y: x // y}
            for c in v:
                if c == '+' or c == '-' or c == '*' or c == '/':
                    stk[-2] = m[c](stk[-2], stk[-1])
                    stk.pop()
                else:
                    stk.append(c)
            return stk[0]

        r = rpn(shunting_yard(s))
        return r


sln = Solution()
# assert(sln.calculate(" -2 ")!=-2) # The expression string contains only non-negative integers
assert (sln.calculate("(2+6* 3)+3") == 23)
assert (sln.calculate("(2+6* 3+5- (3*14/7+2)*5)+3") == -12)
assert (sln.calculate("2*(5+5*2)/3+(6/2+8)") == 21)
assert (sln.calculate(" 6-4 / 2 ") == 4)

# follow up:
#  https://stackoverflow.com/questions/17151972/shunting-yard-algorithmin-javascript-handling-negative-numbers
