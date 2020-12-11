import collections


class Solution(object):
    def isNStraightHand(self, hand, W):
        count = collections.Counter(hand)
        while count:
            m = min(count)
            for k in range(m, m + W):
                if k not in count:
                    return False
                if count[k] == 1:
                    del count[k]
                else:
                    count[k] -= 1
        return True


sln = Solution()
hand = [1, 2, 3, 6, 2, 3, 4, 7, 8]
W = 3
assert sln.isNStraightHand(hand, W) is True
