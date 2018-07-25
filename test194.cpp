/*
 * test194.cpp
 *
 *  Created on: May 14, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Given a non-empty array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list,
and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

Example 1:

Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
Example 2:

Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
*/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int len = digits.size(), i;
        for (i = len - 1; i >= 0 && digits[i] == 9; --i);
        if (i < 0) {
            //all 9s
            vector<int> ret(len + 1, 0);
            ret[0] = 1;
            return ret;
        } else {
            vector<int> ret(len, 0);
            ret[i] = digits[i] + 1;
            for (i = i - 1; i >= 0; ret[i] = digits[i], --i);
            return ret;
        }
    }
};
