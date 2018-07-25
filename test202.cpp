/*
 * test202.cpp
 *
 *  Created on: May 23, 2018
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
Given a sorted integer array nums, where the range of elements are in the inclusive range [lower, upper],
return its missing ranges.

Example:

Input: nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99,
Output: ["2", "4->49", "51->74", "76->99"]
*/

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        if (lower > upper) {
            return {};
        }
        int len = nums.size();
        if (len == 0) {
            if (lower == upper) {
                return {std::to_string(lower)};
            } else {
                return {std::to_string(lower) + "->" + std::to_string(upper)};
            }
        }
        vector<string> ret;
        int cur = lower, start, end, i = 0;
        while (i < nums.size()) {
            if (nums[i] > cur) {
                start = cur;
                end = nums[i] - 1;
                if (start == end) {
                    ret.push_back(std::to_string(start));
                } else {
                    ret.push_back(std::to_string(start) + "->" + std::to_string(end));
                }
                if (nums[i] < INT32_MAX) {
                    cur = nums[i] + 1;
                } else {
                    cur = nums[i];
                }
                ++i;
            } else if (nums[i] == cur) {
                if (nums[i] < INT32_MAX) {
                    ++cur;
                }
                ++i;
            } else {
                ++i;
            }
        }
        if (nums[len - 1] < upper - 1) {
            ret.push_back(std::to_string(nums[len - 1] + 1) + "->" + std::to_string(upper));
        } else if (nums[len - 1] == upper - 1) {
            ret.push_back(std::to_string(upper));
        }
        return ret;
    }
};
