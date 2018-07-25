/*
 * test169.cpp
 *
 *  Created on: April 30, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

//Given a list, each element in the list can be a list or integer.
//flatten it into a simply list with integers.

// Notice
//If the element in the given list is a list, it can contain list too.

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 */
class NestedInteger {
  public:
    // Return true if this NestedInteger holds a single integer,
    // rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds,
    // if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds,
    // if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution {
public:
    // @param nestedList a list of NestedInteger
    // @return a list of integer
    vector<int> flatten(vector<NestedInteger> &nestedList) {
        // Write your code here
        vector<NestedInteger>::size_type len = nestedList.size();
        if (len == 0) {
            return {};
        }
        vector<NestedInteger>::size_type i;
        std::stack<NestedInteger> stack1;
        vector<int> ret;
        for (i = 0; i < len; ++i) {
            stack1.push(nestedList[i]);
            while (!stack1.empty()) {
                NestedInteger ni = stack1.top();
                stack1.pop();
                if (ni.isInteger()) {
                    ret.push_back(ni.getInteger());
                } else {
                    const vector<NestedInteger> &vni = ni.getList();
                    for (vector<NestedInteger>::size_type j = vni.size(); j > 0; --j) {
                        stack1.push(vni[j - 1]);
                    }
                }
            }
        }
        return ret;
    }
};
