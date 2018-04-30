/*
 * test156.cpp
 *
 *  Created on: April 24, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <queue>
#include <cstdint>
#include <unordered_map>
using namespace std;

//Merge two given sorted integer array A and B into a new sorted integer array.
//Example:
//A=[1,2,3,4]
//B=[2,4,5,6]
//return [1,2,2,3,4,4,5,6]
class Solution {
public:
    /**
     * @param A: sorted integer array A
     * @param B: sorted integer array B
     * @return: A new sorted integer array
     */
    vector<int> mergeSortedArray(vector<int> &A, vector<int> &B) {
        // write your code here
        vector<int> ret(A.size() + B.size());
        int i = 0, j = 0, k = 0;
        while (i < A.size() && j < B.size()) {
                if (A[i] <= B[j]) {
                    ret[k++] = A[i++];
                } else {
                    ret[k++] = B[j++];
                }
        }
        for (; i < A.size(); ret[k++] = A[i++]);
        for (; j < B.size(); ret[k++] = B[j++]);
        return ret;
    }
};
