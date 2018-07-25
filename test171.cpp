/*
 * test171.cpp
 *
 *  Created on: May 1, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

//Write an efficient algorithm that searches for a value in an m x n matrix.
//This matrix has the following properties:
//Integers in each row are sorted from left to right.
//The first integer of each row is greater than the last integer of the previous row.
//requirement: time complexity O(log(n) + log(m))
//Example
//Consider the following matrix:
//[
//    [1, 3, 5, 7],
//    [10, 11, 16, 20],
//    [23, 30, 34, 50]
//]
//Given target = 3, return true.

class Solution {
public:
    /**
     * @param matrix: matrix, a list of lists of integers
     * @param target: An integer
     * @return: a boolean, indicate whether matrix contains target
     */
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        // write your code here
        vector<vector<int>>::size_type len1 = matrix.size();
        if (len1 == 0) {
            return false;
        }
        vector<int>::size_type len2 = matrix[0].size();
        if (len2 == 0) {
            return false;
        }

        vector<vector<int>>::size_type start = 0, end = len1 - 1, middle;
        while (1) {
            middle = (start + end) / 2;
            //compare matrix[middle][0] with target
            if (matrix[middle][0] == target) {
                return true;
            } else if (matrix[middle][0] < target) {
                //check @(middle+1)
                if (middle + 1 < len1 && matrix[middle + 1][0] > target) {
                    break;
                }
                start = middle + 1;
            } else {
                if (middle == 0) {
                    return false;
                } else {
                    end = middle - 1;
                }
            }
            if (end < start) {
                break;
            }
        }
        //end < start, check middle
        if (matrix[middle][0] < target) {
            //binary search at row @middle
            vector<int>::size_type start2 = 0, end2 = len2 - 1, middle2;
            while (1) {
                middle2 = (start2 + end2) / 2;
                if (matrix[middle][middle2] == target) {
                    return true;
                } else if (matrix[middle][middle2] > target) {
                    if (middle2 == 0) {
                        return false;
                    } else {
                        end2 = middle2 - 1;
                    }
                } else {
                    start2 = middle2 + 1;
                }
                if (start2 > end2) {
                    return false;
                }
            }
        } else {
            return false;
        }
    }
};
