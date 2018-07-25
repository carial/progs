/*
 * test177.cpp
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

//Reverse a linked list.

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
     * @param head: n
     * @return: The new head of reversed linked list.
     */
    ListNode * reverse(ListNode * head) {
        // write your code here
        if (!head || !head->next) {
            return head;
        }
        ListNode *p = head, *q, *r;
        q = p->next;
        r = q->next;
        p->next = nullptr;
        while (r) {
            q->next = p;
            p = q;
            q = r;
            r = r->next;
        }
        q->next = p;
        return q;
    }
};
