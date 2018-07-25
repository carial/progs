/*
 * test189.cpp
 *
 *  Created on: May 10, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
Note:

s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:

Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:

Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:

Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:

Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:

Input:
s = "acdcb"
p = "a*c?b"
Output: false
*/

class Solution {
public:
    bool isMatch(string s, string p) {
        int len1 = s.length(), len2 = p.length();

        if (len1 == 0 && len2 == 0) {
            return true;
        }
        //use dynamic programming
        vector<vector<bool>> match(len1 + 1, vector<bool>(len2 + 1, false));
        //both empty is matching
        match[0][0] = true;
        //@match[i][j] means if s[0...(i-1)] matches p[0...(j-1)]
        //if i==0 or j==0, means s or p is empty
        //if p is empty (j==0), if s is not empty, no match
        for (int i = 0; i < len1; ++i) {
            match[i + 1][0] = false;
        }
        for (int j = 0; j < len2; ++j) {
            for (int i = -1; i < len1; ++i) {
                //solve match[i][j]
                char chs, chp = p.at(j);
                if (i == -1) {
                    //s is empty
                    chs = 0;
                } else {
                    chs = s.at(i);
                }
                if (chs != chp) {
                    if (chs) {
                        //s not empty string
                        if (chp == '?') {
                            //match
                            match[i + 1][j + 1] = match[i][j];
                        } else if (chp == '*') {
                            //match
                            match[i + 1][j + 1] = match[i][j + 1] || match[i][j];
                        } else {
                            //not match
                            match[i + 1][j + 1] = false;
                        }
                    } else {
                        //s is empty string
                        if (chp == '*') {
                            //match
                            match[i + 1][j + 1] = match[i + 1][j];
                        } else {
                            //not match
                            match[i + 1][j + 1] = false;
                        }
                    }
                } else {
                    //match
                    match[i + 1][j + 1] = match[i][j];
                }
            }
        }
        return match[len1][len2];
    }
};
