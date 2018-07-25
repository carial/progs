/*
 * test174.cpp
 *
 *  Created on: May 2, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

//Given an array nums of integers and an int k, partition the array (i.e move the elements in "nums") such that:
//All elements < k are moved to the left
//All elements >= k are moved to the right
//Return the partitioning index, i.e the first index i nums[i] >= k.
//Notice
//You should do really partition in array nums instead of just counting the numbers of integers smaller than k.
//If all elements in nums are smaller than k, then return nums.length
//Example
//If nums = [3,2,2,1] and k=2, a valid answer is 1.


class Solution {
public:
    /**
     * @param nums: The integer array you should partition
     * @param k: An integer
     * @return: The index after partition
     */
    int partitionArray(vector<int> &nums, int k) {
        // write your code here
        vector<int>::size_type len = nums.size();
        if (len == 0) {
            return 0;
        }
        vector<int>::size_type i = 0, j = len - 1;
        while (i <= j) {
            for (; i < j + 1 && nums[i] < k; ++i);
            if (i == j + 1) {
                //done
                return (j + 1);
            }
            //nums[i] >= k
            for (; j > i && nums[j] >= k; --j);
            if (j == i) {
                //done
                return i;
            }
            //switch nums[i] and nums[j]
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            ++i;
            --j;
            //[0...(i-1)] all numbers < k, [(j+1)...(len-1)] all numbers >= k
        }
        return i;
    }
};
