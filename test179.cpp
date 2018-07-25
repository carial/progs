/*
 * test179.cpp
 *
 *  Created on: May 3, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

/*
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order and each of their nodes contain a single digit.
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
*/
/**
 * Definition for singly-linked list.
 */
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int carry = 0;
        ListNode *head = nullptr, *p = l1, *q = l2, *r;
        int num;
        while (p || q) {
            num = 0;
            if (p) {
                num += p->val;
                p = p->next;
            }
            if (q) {
                num += q->val;
                q = q->next;
            }
            num += carry;
            carry = num / 10;
            num = num % 10;
            if (!head) {
                head = new ListNode(num);
                r = head;
            } else {
                r->next = new ListNode(num);
                r = r->next;
            }
        }
        if (carry) {
            r->next = new ListNode(carry);
        }
        return head;
    }
};
