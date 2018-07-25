/*
 * test186.cpp
 *
 *  Created on: May 9, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int len = lists.size();
        if (len == 0) {
            return nullptr;
        }
        if (len == 1) {
            return lists[0];
        }
        ListNode *head = nullptr, *p;
        p = head;
        //build the heap
        int heapSize = 0;
        vector<ListNode*> smallHeap(len, nullptr);
        for (int i = 0; i < len; ++i) {
            ListNode *q = lists[i];
            if (q) {
                //nullptr will not be put into heap
                smallHeap[heapSize] = q;
                ++heapSize;
                //adjust heap
                moveupHeap(smallHeap, heapSize);
            }
        }
        while (heapSize > 0) {
            //pop the root
            ListNode *q = smallHeap[0];
            if (!head) {
                head = new ListNode(q->val);
                p = head;
            } else {
                p->next = new ListNode(q->val);
                p = p->next;
            }
            if (q->next) {
                //insert q->next to heap, heap size unchanged
                smallHeap[0] = q->next;
                movedownHeap(smallHeap, heapSize);
            } else {
                --heapSize;
                if (heapSize > 0) {
                    //move last one to root
                    smallHeap[0] = smallHeap[heapSize];
                    //adjust heap
                    movedownHeap(smallHeap, heapSize);
                }
            }
        }
        return head;
    }
    private:
    void moveupHeap(vector<ListNode*>& smallHeap, int size) {
        int i = size - 1, up;
        while (1) {
            up = (i - 1) / 2;
            if (up < 0) {
                break;
            }
            //compare i and up
            if (smallHeap[i]->val < smallHeap[up]->val) {
                ListNode *p = smallHeap[up];
                smallHeap[up] = smallHeap[i];
                smallHeap[i] = p;
                i = up;
            } else {
                break;
            }
        }
        return;
    }

    void movedownHeap(vector<ListNode*>& smallHeap, int size) {
        int i = 0, down1, down2;
        while (1) {
            down1 = (i + 1) * 2 - 1;
            down2 = (i + 1) * 2;
            ListNode *p = smallHeap[i];
            if (down1 < size && smallHeap[down1]->val < p->val) {
                p = smallHeap[down1];
            }
            if (down2 < size && smallHeap[down2]->val < p->val) {
                p = smallHeap[down2];
            }
            if (p == smallHeap[i]) {
                break;
            } else if (p == smallHeap[down1]) {
                smallHeap[down1] = smallHeap[i];
                smallHeap[i] = p;
                i = down1;
            } else {
                smallHeap[down2] = smallHeap[i];
                smallHeap[i] = p;
                i = down2;
            }
        }
        return;
    }
};
