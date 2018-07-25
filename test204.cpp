/*
 * test204.cpp
 *
 *  Created on: May 25, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

/*
Implement an iterator over a binary search tree (BST).
Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and
uses O(h) memory, where h is the height of the tree.
*/


/**
 * Definition for binary tree
 */
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class BSTIterator {
public:
    BSTIterator(TreeNode *root) : m_root(root) {
        //find the leftmost element
        TreeNode *p = m_root;
        while (p) {
            m_stack.push(p);
            p = p->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !m_stack.empty();
    }

    /** @return the next smallest number */
    int next() {
        if (!m_stack.empty()) {
            TreeNode *p = m_stack.top();
            m_stack.pop();
            TreeNode *q = p->right;
            while (q) {
                m_stack.push(q);
                q = q->left;
            }
            return p->val;
        }
        return -1;
    }
    private:
    TreeNode *m_root;
    stack<TreeNode*> m_stack;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
