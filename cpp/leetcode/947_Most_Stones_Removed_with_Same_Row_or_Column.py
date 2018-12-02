class DSU:
    def __init__(self, N):
        self.p = range(N)

    def find(self, x):
        if self.p[x] != x:
            self.p[x] = self.find(self.p[x])
        return self.p[x]

    def union(self, x, y):
        xr = self.find(x)
        yr = self.find(y)
        self.p[xr] = yr

class Solution(object):
    def removeStones(self, stones):
        N = len(stones)
        dsu = DSU(100)
        for x, y in stones:
            dsu.union(x, y + 50)

        l = len({dsu.find(x) for x, y in stones})
        return N - l


assert(Solution().removeStones([[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]))