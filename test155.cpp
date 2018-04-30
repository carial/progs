/*
 * test155.cpp
 *
 *  Created on: April 23, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <queue>
#include <cstdint>
#include <unordered_map>
using namespace std;

//Find K-th largest element in an array.
//Example:
//In array [9,3,2,4,8], the 3rd largest element is 4.
//In array [1,2,3,4,5], the 1st largest element is 5, 2nd largest element is 4, 3rd largest element is 3 and etc.
//Note: you can swap the array
//complexity: O(N), N is array size
class Solution {
public:
    /*
     * @param n: An integer
     * @param nums: An array
     * @return: the Kth largest element
     */
    int kthLargestElement(int n, vector<int> &nums) {
        // write your code here
        if (n <= 0 || nums.size() < n) {
            return -1;
        }
        int start = 0, end = nums.size() - 1, middle, i, j, temp;
        while (1) {
           middle = (start + end) / 2;
           i = start;
           j = end;
           while (1) {
               for (; i < middle && nums[i] >= nums[middle]; ++i);
               for (; j > middle && nums[j] < nums[middle]; --j);
               if (i == middle && j == middle) {
                   break;
               } else if (i < middle && j > middle) {
                   //swap nums[i] and nums[j]
                   temp = nums[i];
                   nums[i] = nums[j];
                   nums[j] = temp;
                   ++i;
                   --j;
               } else if (i == middle && j > middle) {
                   //swap nums[i] and nums[j]
                   temp = nums[i];
                   nums[i] = nums[j];
                   nums[j] = temp;
                   ++i;
                   middle = j;
               } else {
                   //swap nums[i] and nums[j]
                   temp = nums[i];
                   nums[i] = nums[j];
                   nums[j] = temp;
                   --j;
                   middle = i;
               }
           }
           //now all numbers before @middle are larger than num[middle], all numbers after @middle are smaller than num[middle]
           if (middle == n - 1) {
               return nums[middle];
           } else if (middle < n - 1) {
               // search [middle + 1, end]
               start = middle + 1;
           } else {
               // search [start, middle - 1]
               end = middle - 1;
           }
        }
    }
};
