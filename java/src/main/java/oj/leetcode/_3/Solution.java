package oj.leetcode._3;

//Given a string, find the length of the longest substring without repeating cha
//racters.
//
//
// Example 1:
//
//
//Input: "abcabcbb"
//Output: 3
//Explanation: The answer is "abc", with the length of 3.
//
//
//
// Example 2:
//
//
//Input: "bbbbb"
//Output: 1
//Explanation: The answer is "b", with the length of 1.
//
//
//
// Example 3:
//
//
//Input: "pwwkew"
//Output: 3
//Explanation: The answer is "wke", with the length of 3.
//             Note that the answer must be a substring, "pwke" is a subsequence
// and not a substring.
//
//
//
//
// Related Topics Hash Table Two Pointers String Sliding Window
// 👍 10196 👎 600


import java.util.HashMap;
import java.util.Map;

/*
https://www.cnblogs.com/grandyang/p/4480780.html
这道求最长无重复子串的题和之前那道 Isomorphic Strings 很类似，属于 LeetCode 早期经典题目，博主认为是可以跟 Two Sum 媲美的一道题。
给了我们一个字符串，让求最长的无重复字符的子串，注意这里是子串，不是子序列，所以必须是连续的。先不考虑代码怎么实现，如果给一个例子中的例子
"abcabcbb"，让你手动找无重复字符的子串，该怎么找。博主会一个字符一个字符的遍历，比如 a，b，c，然后又出现了一个a，那么此时就应该去掉第
一次出现的a，然后继续往后，又出现了一个b，则应该去掉一次出现的b，以此类推，最终发现最长的长度为3。所以说，需要记录之前出现过的字符，
记录的方式有很多，最常见的是统计字符出现的个数，但是这道题字符出现的位置很重要，所以可以使用 HashMap 来建立字符和其出现位置之间的映射。
进一步考虑，由于字符会重复出现，到底是保存所有出现的位置呢，还是只记录一个位置？我们之前手动推导的方法实际上是维护了一个滑动窗口，窗口内
的都是没有重复的字符，需要尽可能的扩大窗口的大小。由于窗口在不停向右滑动，所以只关心每个字符最后出现的位置，并建立映射。窗口的右边界就是
当前遍历到的字符的位置，为了求出窗口的大小，需要一个变量 left 来指向滑动窗口的左边界，这样，如果当前遍历到的字符从未出现过，那么直接扩
大右边界，如果之前出现过，那么就分两种情况，在或不在滑动窗口内，如果不在滑动窗口内，那么就没事，当前字符可以加进来，如果在的话，就需要先
在滑动窗口内去掉这个已经出现过的字符了，去掉的方法并不需要将左边界 left 一位一位向右遍历查找，由于 HashMap 已经保存了该重复字符最后出
现的位置，所以直接移动 left 指针就可以了。维护一个结果 res，每次用出现过的窗口大小来更新结果 res，就可以得到最终结果啦。
* */

class Solution {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length(), ans = 0;
        Map<Character, Integer> map = new HashMap<>(); // current index of character
        // try to extend the range [i, j]
        for (int right = 0, left = -1; right < n; right++) {
            final Character c = s.charAt(right);
            if (map.containsKey(c)) {
                if (map.get(c) > left)
                    left = map.get(c);
            }
            ans = Math.max(ans, right - left);
            map.put(s.charAt(right), right);
        }
        return ans;
    }

    public static void main(String[] args){
        Solution sln = new Solution();
        int d = sln.lengthOfLongestSubstring("abcabcbb");
        System.out.println(d);
        d = sln.lengthOfLongestSubstring("a");
        System.out.println(d);
    }
}
