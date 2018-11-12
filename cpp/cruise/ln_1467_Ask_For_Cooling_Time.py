# -*- coding: utf-8 -*-
'''
Description
You have a bunch of skills that need to be released. The release order is arr. Must be released in order.
 Each skill has a cooldown of length n. That is, there must be an interval of at least n seconds between
 two similar skills. It takes 1 second to release each skill, return the time it takes to finish all skills.

The length of the array does not exceed 100,000.
1 \leq n \leq 201≤n≤20
The skill number is a positive integer that does not exceed 100.
Have you met this question in a real interview?

Example
Given arr=[1,1,2,2],n=2.Return 8.

The order is [1, _, _, 1, 2, _, _, 2].So return 8.
Skill 1 is released in the 1st second, in the 2nd second and the 3rd second enters the cooling time,
 and the 4th second releases the second time.
Skill 2 is released in the 5th second, in the 6th second and the 7th second enters the cooling time,
 and the 8th second releases the second time.

Given arr=[1,2,1,2], n=2. Return 5.

The order is [1, 2, _, 1, 2].So return  5.
Skill 1 is released in the 1st second, in the 2nd second and the 3rd second enters the cooling time,
 and the 4th second releases the second time.
Skill 2 is released in the 2nd second, in the 3rd second and the 4th second enters the cooling time,
 and the 5th second releases the second time.
DifficultyMedium
Total Accepted383
Total Submitted758
Accepted Rate50%

'''

'''
public class Solution {
    /**
     * @param arr: The release order
     * @param n: The cooldown
     * @return: Return the time
     */
    public int askForCoolingTime(int[] arr, int n) {
        Map<Integer, Integer> map = new HashMap<>();
        int res = 0;
        for (int i : arr) {
            if (!map.containsKey(i)) {
                res++;
            } else {
                if (res + 1 >= map.get(i)) {
                    res++;
                } else {
                    res = map.get(i);
                }
            }
            map.put(i, res + n + 1);
        }
        return res;
    }

}
'''