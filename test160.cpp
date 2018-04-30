/*
 * test160.cpp
 *
 *  Created on: April 25, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
using namespace std;

//Given two values k1 and k2 (where k1 < k2) and a root pointer to a Binary Search Tree.
//Find all the keys of tree in range k1 to k2. i.e. print all x such that k1<=x<=k2 and
//x is a key of given BST. Return all the keys in ascending order.
/**
 * Definition of TreeNode:
 */
class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};


class Solution {
public:
    /**
     * @param root: param root: The root of the binary search tree
     * @param k1: An integer
     * @param k2: An integer
     * @return: return: Return all keys that k1<=key<=k2 in ascending order
     */
    vector<int> searchRange(TreeNode * root, int k1, int k2) {
        // write your code here
        //in-order traverse the tree and print out the number if it is between k1 and k2
        if (!root) {
            return {};
        }
        vector<int> ret;
        stack<TreeNode *> nodeStack;
        TreeNode *p = root;
        while (p) {
            nodeStack.push(p);
            p = p->left;
        }
        while (!nodeStack.empty()) {
            p = nodeStack.top();
            //leftmost node
            if (p->val >= k1 && p->val <= k2) {
                ret.push_back(p->val);
            }
            nodeStack.pop();
            p = p->right;
            while (p) {
                nodeStack.push(p);
                p = p->left;
            }
        }
        return ret;
    }
};
