/*
 * test184.cpp
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
Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true
*/

class Solution {
public:
    bool isValid(string s) {
        int len = s.length();
        if (len == 0) {
            return true;
        }
        stack<char> st;
        for (int i = 0; i < len; ++i) {
            char ch = s.at(i);
            if (ch == '{' || ch == '(' || ch == '[') {
                st.push(ch);
            } else if (!st.empty()) {
                char ch1 = st.top();
                st.pop();
                if ((ch == '}' && ch1 != '{') || (ch == ')' && ch1 != '(') || (ch == ']' && ch1 != '[')) {
                    return false;
                }
            } else {
                return false;
            }
        }
        if (!st.empty()) {
            return false;
        }
        return true;
    }
};
