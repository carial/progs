/*
 * test188.cpp
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
Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it is able to trap after raining.

Example:
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
*/

class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len == 0) {
            return 0;
        }
        deque<int> bars;
        //@bars.front() keeps the index of current heighest bar
        //push next bar from end
        //if next bar is taller or equal to than @bars.front(), pop @bars.front() and all bars following it until the next bar
        //in the process, compute the volumn for each bar
        //if no more bar, pop from the end
        int volumn = 0;
        for (int i = 0; i < len; ++i) {
            //push @i into @bars
            if (bars.empty() || height[i] < height[bars.front()]) {
                bars.push_back(i);
            } else {
                //pop from beginning
                int j = bars.front();
                bars.pop_front();
                while (!bars.empty()) {
                    volumn += height[j] - height[bars.front()];
                    bars.pop_front();
                }
                bars.push_back(i);
            }
        }
        int i = bars.back();
        bars.pop_back();
        while (!bars.empty()) {
            if (height[i] <= height[bars.back()]) {
                i = bars.back();
                bars.pop_back();
            } else {
                volumn += height[i] - height[bars.back()];
                bars.pop_back();
            }
        }
        return volumn;
    }
};
