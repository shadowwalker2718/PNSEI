class Solution(object):
    def calculate(self, s):
        if not s:
            return "0"
        stk, num, preOperator = [], 0, "+"
        for i in xrange(len(s)):
            if s[i].isdigit():
                num = num*10+int(s[i])
            if (not s[i].isdigit() and not s[i].isspace()) or i == len(s)-1:
                if preOperator == "-":
                    stk.append(-num)
                elif preOperator == "+":
                    stk.append(num)
                elif preOperator == "*":
                    stk.append(stk.pop()*num)
                else:
                    tmp = stk.pop()
                    if tmp//num < 0 and tmp%num != 0: # in c++, just tmp/num
                        stk.append(tmp//num+1)
                    else:
                        stk.append(tmp//num)
                preOperator = s[i]
                num = 0
        return sum(stk)

sln=Solution()
sln.calculate("14-3/2")==13