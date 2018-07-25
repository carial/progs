/*
 * test201.cpp
 *
 *  Created on: May 16, 2018
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
Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.

Example 1:

Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.
Example 2:

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.
*/

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int len = s.length();
        if (len == 0) {
            return 0;
        }
        //@nDistinctChar stores the distinct characters in substring [i...j]
        int nDistinctChar = 0;
        unordered_map<char, int> charToFreqMap;
        int i = 0, j = -1, maxLength = 0;
        while (1) {
            if (nDistinctChar <= 2) {
                //find one substring [i...j]
                if (j - i + 1 > maxLength) {
                    maxLength = j - i + 1;
                }
                ++j;
                if (j == len) {
                    break;
                }
                //current substring [i...j]
                char ch = s.at(j);
                auto it1 = charToFreqMap.find(ch);
                if (it1 == charToFreqMap.end()) {
                    //add new character into map
                    charToFreqMap.emplace(ch, 1);
                    ++nDistinctChar;
                } else {
                    //update frequency
                    if (it1->second == 0) {
                        ++nDistinctChar;
                    }
                    ++it1->second;
                }
            } else {
                //remove s.at(i)
                auto it2 = charToFreqMap.find(s.at(i));
                --it2->second;
                if (it2->second == 0) {
                    --nDistinctChar;
                }
                ++i;
            }
        }
        return maxLength;
    }
};
