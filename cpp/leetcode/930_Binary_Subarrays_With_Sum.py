from collections import defaultdict

# https://leetcode.com/problems/binary-subarrays-with-sum/
"""
In an array A of 0s and 1s, how many non-empty subarrays have sum S?

Example 1:
Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
"""

class Solution:
    def numSubarraysWithSum(self, A, S):
        """
        :type A: List[int]
        :type S: int
        :rtype: int
        """
        d=defaultdict(lambda:0)
        ps=0
        ans=0
        for a in A:
            d[ps]+=1
            ps+=a
            ans+=d[ps-S]
        return ans

A=[1,0,1,0,1]
S = 2
sln=Solution()
print sln.numSubarraysWithSum(A,S) == 4
print sln.numSubarraysWithSum([0,0,0,0,0],0) == 15