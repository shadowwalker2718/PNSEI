import itertools

# https://leetcode.com/problems/ambiguous-coordinates/

class Solution_Debug(object):
    def ambiguousCoordinates(self, S):
        def make(frag):
            r=[]
            for d in xrange(1, len(frag)+1): # add dot in frag
                left = frag[:d]
                right = frag[d:]
                if not ((left.startswith('0') and left != '0') or right.endswith('0')):
                    r.append(left + ('.' if d != len(frag) else '') + right)
            return r

        S = S[1:-1]
        r=list()
        for i in xrange(1, len(S)):
            _1st = make(S[:i])
            _2nd = make(S[i:])
            for cand in itertools.product(_1st, _2nd):
                r.append("({}, {})".format(*cand))
        return r

class Solution(object):
    def ambiguousCoordinates(self, S):
        def make(frag):
            N = len(frag)
            for d in xrange(1, N+1):
                left = frag[:d]
                right = frag[d:]
                if ((not left.startswith('0') or left == '0')
                        and (not right.endswith('0'))):
                    yield left + ('.' if d != N else '') + right

        S = S[1:-1]
        return ["({}, {})".format(*cand)
                for i in xrange(1, len(S))
                for cand in itertools.product(make(S[:i]), make(S[i:]))]

sln=Solution_Debug()

r=["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)", "(0.12, 3)"]
assert(set(sln.ambiguousCoordinates("(0123)"))== set(r))