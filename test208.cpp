/*
 * test208.cpp
 *
 *  Created on: June 1, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

/*
Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it.
Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"
*/

class Solution {
public:
    string shortestPalindrome(string s) {
        int len = s.length();
        if (len == 0 || len == 1) {
            return s;
        }
        //insert special character 'a' into s, so all original palindromes are odd numbered
        //old mapping new: i -> 2 * i + 1; i / 2 <- i
        //start from right end, stop when find first palindrome that reaches left end
        //if center position is c in new string, patch characters in old string starting from c (c c+1...len-1)
        //@leftPos stores for each position i as center of palindrome, the left index
        int len2 = 2 * len + 1;
        vector<int> leftPos(len2, len2);
        //@left the current most left index, @center is corresponding center
        int left = len2, center, i, j, k;
        for (i = len2 - 1; i >= 1; --i) {
            //for each position in string
            if (i < left) {
                //currrent character is outside left most position, search each character
                for (j = i - 1, k = i + 1; j >= 0 && k < len2; --j, ++k) {
                    char ch1 = (j % 2) ? s.at(j / 2) : 'a';
                    char ch2 = (k % 2) ? s.at(k / 2) : 'a';
                    if (ch1 != ch2) {
                        break;
                    }
                }
                left = j + 1;
                center = i;
                leftPos[i] = left;
            } else {
                int i_co = 2 * center - i;
                int right = 2 * center - left;
                int right_co = 2 * i_co - leftPos[i_co];
                //compare right_co with right
                if (right_co < right) {
                    leftPos[i] = 2 * center - right_co;
                } else if (right_co > right) {
                    leftPos[i] = left;
                } else {
                    //right_co == right
                    for (j = left - 1, k = 2 * i - left + 1; j >= 0 && k < len2; --j, ++k) {
                        char ch1 = (j % 2) ? s.at(j / 2) : 'a', ch2 = (k % 2) ? s.at(k / 2) : 'a';
                        if (ch1 != ch2) {
                            break;
                        }
                    }
                    leftPos[i] = j + 1;
                    if (left > j + 1) {
                        left = j + 1;
                        center = i;
                    }
                }
            }
            if (left == 0) {
                break;
            }
        }
        string ret(s.length() + len - center, 0);
        for (i = 0; i < len - center; ++i) {
            ret.at(i) = s.at(len - 1 - i);
        }
        for (j = 0; j < len; ++j) {
            ret.at(i + j) = s.at(j);
        }
        return ret;
    }
};
