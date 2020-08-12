class Solution(object):
    def knightDialer(self, N):
        """
        :type N: int
        :rtype: int
        """
        MOD = 10 ** 9 + 7
        d = [[4, 6], [6, 8], [7, 9], [4, 8], [0, 3, 9], [], [0, 1, 7], [2, 6], [1, 3], [2, 4]]
        ans = [1] * 10
        for i in range(N - 1):
            nans = [0] * 10
            for j in range(10):
                for k in d[j]:
                    nans[j] += ans[k]
            ans = [m % MOD for m in nans]
        return sum(ans) % MOD


sln = Solution()
sln.knightDialer(161)
