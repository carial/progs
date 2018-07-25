/*
 * test185.cpp
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
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if (n <= 0) {
            return {};
        }
        int numLeft = n, numRight = n;
        //there are 2*n positions that each position could take either '(' or ')'
        //@numLeft is '(' left, @numRight is ')' left
        //restrictions: @numLeft must not be greater than @numRight
        int cur = 0;
        vector<int> p(2 * n, 0);
        string res(2 * n, ' ');
        vector<string> ret;
        //@p[i] = 0 means '(' at @i, @p[i] = 1 means ')' at @i
        while (1) {
            if (p[cur] == 2) {
                p[cur] = 0;
                --cur;
                if (cur == 0) {
                    break;
                }
                if (p[cur] == 0) {
                    ++numLeft;
                } else {
                    ++numRight;
                }
                ++p[cur];
            } else {
                //check p[cur]
                if (p[cur] == 0) {
                    if (numLeft > 0) {
                        res.at(cur) = '(';
                        --numLeft;
                        ++cur;
                    } else {
                        ++p[cur];
                    }
                } else if (p[cur] == 1 && numRight > 0 && numLeft < numRight) {
                    res.at(cur) = ')';
                    --numRight;
                    ++cur;
                } else {
                    //no choice
                    p[cur] = 0;
                    --cur;
                    if (cur == 0) {
                        break;
                    }
                    if (p[cur] == 0) {
                        ++numLeft;
                    } else {
                        ++numRight;
                    }
                    ++p[cur];
                }
                if (cur == 2 * n) {
                    //got a solution
                    ret.push_back(res);
                    --cur;
                    //last position must be ')'
                    ++numRight;
                    ++p[cur];
                }
            }
        }
        return ret;
    }
};
