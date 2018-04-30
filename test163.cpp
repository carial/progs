/*
 * test163.cpp
 *
 *  Created on: April 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//For a given sorted array (ascending order) and a target number,
//find the first index of this number in O(log n) time complexity.
//If the target number does not exist in the array, return -1.
//Note: ask if there are repeated numbers in the array!!!
//This solution assumes there may be repeated numbers in the array

class Solution {
public:
    /**
     * @param nums: The integer array.
     * @param target: Target to find.
     * @return: The first position of target. Position starts from 0.
     */
    int binarySearch(vector<int> &nums, int target) {
        // write your code here
        vector<int>::size_type len = nums.size();
        if (len == 0) {
            return -1;
        }
        vector<int>::size_type start = 0, end = len - 1, middle;
        while (1) {
            middle = (start + end) / 2;
            if (nums[middle] < target) {
                if (middle == end) {
                    return -1;
                } else {
                    start = middle + 1;
                }
            } else if (nums[middle] == target) {
                //check (middle - 1)
                if (middle == start || nums[middle - 1] < target) {
                    return middle;
                } else {
                    end = middle - 1;
                }
            } else {
                //nums[middle] > target
                if (middle == start) {
                    return -1;
                } else {
                    end = middle - 1;
                }
            }
        }
    }
};
