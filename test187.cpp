/*
 * test187.cpp
 *
 *  Created on: May 9, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
The replacement must be in-place and use only constant extra memory.
Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) {
            return;
        }
        //if all numbers are the same, return
        int i;
        for (i = 0; i < len; ++i) {
            if (nums[i] != nums[0]) {
                break;
            }
        }
        if (i == len) {
            return;
        }
        //traverse from end
        int start;
        for (i = len - 2; i >= 0; --i) {
            //find the @start that nums[start] < nums[start + 1]
            if (nums[i] < nums[i + 1]) {
                break;
            }
        }
        if (i >= 0) {
            start = i;
            //find first number that is greater than nums[start]
            for (i = len - 1; i >= start + 1; --i) {
                if (nums[i] > nums[start]) {
                    break;
                }
            }
            //switch @nums[i] with @nums[start]
            int temp = nums[i];
            nums[i] = nums[start];
            nums[start] = temp;
            //reverse [start+1...len-1]
            int j;
            for (i = start + 1, j = len - 1; i < j; ++i, --j) {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        } else {
            //the numbers are in decreasing order, switch to increasing order
            for (i = 0; i < len / 2; ++i) {
                int temp = nums[i];
                nums[i] = nums[len - 1 - i];
                nums[len - 1 - i] = temp;
            }
        }
        return;
    }
};
