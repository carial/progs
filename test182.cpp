/*
 * test182.cpp
 *
 *  Created on: May 8, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Given an input string (s) and a pattern (p), implement regular expression matching with support for '.' and '*'.
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Note:
s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like . or *.

Example 1:
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:
Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

Example 4:
Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".

Example 5:
Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
*/

class Solution1 {
public:
    bool isMatch(string s, string p) {
        //assume p is good pattern
        int len1 = s.length(), len2 = p.length();
        return isMatchSub(s, p, 0, 0);
    }
    private:
    bool isMatchSub(const string& s, const string& p, int start1, int start2) {
        int len1 = s.length() - start1, len2 = p.length() - start2;
        if (len1 == 0 && len2 == 0) {
            return true;
        }
        for (int i = start1, j = start2; ;) {
            //@i index in s, @j index in p
            char ch1, ch2, ch3;
            if (i < s.length()) {
                ch1 = s.at(i);
            } else {
                ch1 = 0;
            }
            if (j + 1 < p.length()) {
                ch2 = p.at(j);
                ch3 = p.at(j + 1);
            } else if (j < p.length()) {
                ch2 = p.at(j);
                ch3 = 0;
            } else {
                ch2 = ch3 = 0;
            }
            if (!ch1) {
                if (!ch2) {
                    return true;
                } else if (!ch3 || ch3 != '*') {
                    return false;
                } else {
                    //ch3 == '*';
                    j += 2;
                }
            } else {
                // @ch1 is not zero
                if (!ch2) {
                    return false;
                }
                //compare @ch1 and @ch2
                if (ch1 == ch2 || ch2 == '.') {
                    //match
                    ++i;
                    if (ch3 != '*') {
                        ++j;
                    } else {
                        //@ch3 is '*'
                        bool ret = isMatchSub(s, p, i, j);
                        if (ret) {
                            return ret;
                        } else {
                            //try remove '*'
                            return isMatchSub(s, p, i, j + 2);
                        }
                    }
                } else if (ch1 != ch2 && ch3 == '*') {
                    //match
                    j += 2;
                } else {
                    return false;
                }
            }
        }
    }
};

class Solution2 {
public:
    bool isMatch(string s, string p) {
        int len1 = s.length(), len2 = p.length();
        if (len1 == 0 && len2 == 0) {
            return true;
        }
        //use dynamic programming
        vector<vector<bool>> res(len1 + 1, vector<bool>(len2 + 1, false));
        //res[i][j] means if s[0...i] matches with p[0...j]
        res[0][0] = true;
        int i, j;
        for (i = 1; i < len1 + 1; ++i) {
            res[i][0] = false;
        }
        char ch1, ch2, ch3;
        for (i = 0; i < len1 + 1; ++i) {
            if (i == 0) {
                ch1 = 0;
            } else {
                ch1 = s.at(i - 1);
            }
            for (j = 1; ;) {
                if (j < len2) {
                    ch2 = p.at(j - 1);
                    ch3 = p.at(j);
                } else if (j < len2 + 1) {
                    ch2 = p.at(j - 1);
                    ch3 = 0;
                } else {
                    break;
                }
                if (ch1 == ch2 || (ch1 && ch2 == '.')) {
                    if (ch3 == '*') {
                        //consider ch2ch3 as unit
                        //ch2ch3 can be removed or not
                        res[i][j + 1] = res[i - 1][j - 1] || res[i - 1][j + 1];
                        j += 2;
                    } else {
                        res[i][j] = res[i - 1][j - 1];
                        j += 1;
                    }
                } else {
                    if (ch3 == '*') {
                        res[i][j + 1] = res[i][j - 1];
                        j += 2;
                    } else {
                        //no match
                        res[i][j] = false;
                        j += 1;
                    }
                }
            }
        }
        return res[len1][len2];
    }
};
