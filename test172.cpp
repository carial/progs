/*
 * test172.cpp
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

//Given three strings: s1, s2, s3, determine whether s3 is formed by the interleaving of s1 and s2.
//Example
//For s1 = "aabcc", s2 = "dbbca"
//When s3 = "aadbbcbcac", return true.
//When s3 = "aadbbbaccc", return false.

class Solution {
public:
    /**
     * @param s1: A string
     * @param s2: A string
     * @param s3: A string
     * @return: Determine whether s3 is formed by interleaving of s1 and s2
     */
    bool isInterleave(string &s1, string &s2, string &s3) {
        // write your code here
        int len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
        if (len1 == 0) {
            if (s2 == s3) {
                return true;
            } else {
                return false;
            }
        }
        if (len2 == 0) {
            if (s1 == s3) {
                return true;
            } else {
                return false;
            }
        }
        if (len3 == 0) {
            return false;
        }
        //s1/s2/s3 not empty string
        if (len3 != len1 + len2) {
            return false;
        }
        vector<int> from(len3, 0);
        int idx1 = 0, idx2 = 0, idx3 = 0;
        while (idx3 < len3) {
            if (idx1 < len1 && from[idx3] == 0 && s1.at(idx1) == s3.at(idx3)) {
                from[idx3] = 1;
                ++idx1;
                ++idx3;
            } else if (idx2 < len2 && from[idx3] <= 1 && s2.at(idx2) == s3.at(idx3)) {
                if (from[idx3] == 1) {
                    --idx1;
                }
                from[idx3] = 2;
                ++idx2;
                ++idx3;
            } else {
                //no choice
                if (from[idx3] == 0) {
                    --idx3;
                } else if (from[idx3] == 1) {
                    from[idx3] = 0;
                    --idx3;
                    --idx1;
                } else {
                    from[idx3] = 0;
                    --idx3;
                    --idx2;
                }
                if (idx3 < 0) {
                    return false;
                }
            }
        }
        return true;
    }
};
