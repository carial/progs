/*
 * test180.cpp
 *
 *  Created on: May 3, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Given a string, find the length of the longest substring without repeating characters.
Examples:
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        if (len == 0) {
            return 0;
        }
        unordered_set<char> charSet;
        int i = 0, j = 0, maxLen = -1;
        while (1) {
            //check substring [i...j]
            auto it1 = charSet.find(s.at(j));
            if (it1 == charSet.end()) {
                //add char
                charSet.emplace(s.at(j));
                if (maxLen < (j - i) + 1) {
                    maxLen = j - i + 1;
                }
                ++j;
            } else {
                //character already in the substring
                //advance i until that character not in the substring
                //note that i must not be greater than j
                for (; s.at(i) != s.at(j); ++i) {
                   charSet.erase(s.at(i));
                }
                ++i;
                ++j;
            }
            if (j == len) {
                break;
            }
        }
        return maxLen;
    }
};
