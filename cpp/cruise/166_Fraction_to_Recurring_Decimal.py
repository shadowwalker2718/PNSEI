class Solution(object):
    def fractionToDecimal(self, n, d):
        """
        :type numerator: int
        :type denominator: int
        :rtype: str
        """
        r=''
        if n==0:
            return "0"
        r+='-' if n^d<0 else ''
        n=n if n>0 else -n
        d=d if d>0 else -d
        r+=str(n/d)
        n%=d
        if n==0:
            return r
        r+='.'
        # hard part
        m={n:len(r)}
        while n:
            n*=10
            r+=str(n/d)
            n%=d
            if n in m:
                r=r[:m[n]] + '(' + r[m[n]:] + ')'
                break
            else:
                m[n]=len(r)

        return r

sln = Solution()
assert(sln.fractionToDecimal(3,13) == '0.(230769)')
assert(sln.fractionToDecimal(-3,13) == '-0.(230769)')
assert(sln.fractionToDecimal(-2,-3) == '0.(6)')
