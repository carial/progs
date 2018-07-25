/*
 * test191.cpp
 *
 *  Created on: May 11, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:
Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:
Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) {
            return {};
        }
        int cols = matrix[0].size();
        if (cols == 0) {
            return {};
        }
        int startc = -1, endc = cols - 1, startr = 0, endr = rows - 1, i = 0, j;
        vector<int> ret(rows * cols, 0);
        while (i < ret.size()) {
            //go right
            ++startc;
            if (startc > endc) {
                break;
            }
            j = startc;
            for (; j <= endc; ++j, ++i) {
                ret[i] = matrix[startr][j];
            }
            //go down
            ++startr;
            if (startr > endr) {
                break;
            }
            j = startr;
            for (; j <= endr; ++j, ++i) {
                ret[i] = matrix[j][endc];
            }
            //go left
            --endc;
            if (startc > endc) {
                break;
            }
            j = endc;
            for (; j >= startc; --j, ++i) {
                ret[i] = matrix[endr][j];
            }
            //go up
            --endr;
            if (startr > endr) {
                break;
            }
            j = endr;
            for (; j >= startr; --j, ++i) {
                ret[i] = matrix[j][startc];
            }
        }
        return ret;
    }
};
