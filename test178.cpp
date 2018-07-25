/*
 * test178.cpp
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

//Reverse a linked list from position m to n.
//Given m, n satisfy the following condition: 1 ≤ m ≤ n ≤ length of list.
//Example
//Given 1->2->3->4->5->NULL, m = 2 and n = 4, return 1->4->3->2->5->NULL.

/**
 * Definition of singly-linked-list:
 */
 class ListNode {
 public:
     int val;
     ListNode *next;
     ListNode(int val) {
        this->val = val;
        this->next = NULL;
     }
 };

class Solution {
public:
    /**
     * @param head: ListNode head is the head of the linked list
     * @param m: An integer
     * @param n: An integer
     * @return: The head of the reversed ListNode
     */
    ListNode * reverseBetween(ListNode * head, int m, int n) {
        // write your code here
        if (!head || !head->next || m <= 0 || n <= 0 || m == n) {
            return head;
        }
        ListNode *p = head, *q, *r, *s = nullptr;
        int i;
        for (i = 1; i < m; ++i) {
            s = p;
            p = p->next;
        }
        //@p is the start
        q = p->next;
        r = q->next;
        for (; i < n; ++i) {
            q->next = p;
            p = q;
            q = r;
            if (r) {
                r = r->next;
            }
        }
        if (s) {
           s->next->next = q;
           s->next = p;
           return head;
        } else {
            head->next = q;
            return p;
        }
    }
};
