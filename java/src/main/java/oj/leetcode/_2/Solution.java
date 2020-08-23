package oj.leetcode._2;

//You are given two non-empty linked lists representing two non-negative integer
//s. The digits are stored in reverse order and each of their nodes contain a sing
//le digit. Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the nu
//mber 0 itself.
//
// Example:
//
//
//Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//Output: 7 -> 0 -> 8
//Explanation: 342 + 465 = 807.
//
// Related Topics Linked List Math
// 👍 8899 👎 2246

import foundation.ListNode;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
// 9 + 5 = 14
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        int sum = 0, carry=0;
        ListNode head = new ListNode();
        final ListNode res = head;
        while(l1!=null || l2!=null){
            sum = (l1==null?0:l1.val) + (l2==null?0:l2.val) + carry;
            if (sum >= 10){
                sum -= 10;
                carry=1;
            }
            final ListNode node = new ListNode(sum);
            head.next = node;
            head = head.next;
            if (l1!=null)
                l1 =l1.next;
            if (l2!=null)
                l2 =l2.next;
        }
        if(carry>0){
            ListNode node = new ListNode(1);
            head.next = node;
            head = head.next;
        }
        return res.next;
    }

    public static void main(String[] args){
        Solution sln = new Solution();
        ListNode r = sln.addTwoNumbers(new ListNode(9),new ListNode(7));
        assert r.val==6: "error";
    }
}
