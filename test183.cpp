/*
 * test183.cpp
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
Given a string containing digits from 2-9 inclusive,
return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.
Note that 1 does not map to any letters.

Example:
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        int len = digits.length();
        if (len == 0) {
            return {};
        }
        vector<vector<char>> digitToChar({{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}, {'j', 'k', 'l'}, {'m', 'n', 'o'},
                                          {'p', 'q', 'r', 's'}, {'t', 'u', 'v'}, {'w', 'x', 'y', 'z'}});
        vector<int> pos(len, 0);
        int cur = 0;
        vector<string> ret;
        string res(len, ' ');
        while (1) {
            int i = digits.at(cur) - '0';
            if (pos[cur] == digitToChar[i - 2].size()) {
                //reach the end
                if (cur == 0) {
                    break;
                } else {
                    pos[cur] = 0;
                    --cur;
                    ++pos[cur];
                }
            } else {
                res.at(cur) = digitToChar[i - 2][pos[cur]];
                ++cur;
                if (cur == len) {
                    ret.push_back(res);
                    --cur;
                    ++pos[cur];
                }
            }
        }
        return ret;
    }
};
