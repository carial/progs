/*
 * test162.cpp
 *
 *  Created on: April 26, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//For a given source string and a target string, you should output the first index(from 0)
//of target string in source string.
//If target does not exist in source, just return -1.

class Solution {
public:
    /*
     * @param source: source string to be scanned.
     * @param target: target string containing the sequence of characters to match
     * @return: a index to the first occurrence of target in source, or -1  if target is not part of source.
     */
    int strStr(const char *source, const char *target) {
        // write your code here
        if (!source || !target) {
            return -1;
        }
        int len1 = strlen(source), len2 = strlen(target);
        if ((len1 == 0 && len2 != 0) || len2 > len1) {
            return -1;
        }
        if ((len1 == 0 && len2 == 0) || (len1 != 0 && len2 == 0)) {
            return 0;
        }
        //use KMP method, first generate @matchIndex for each position at @target
        //for @target, there are @matchNum[i] characters from [0...(i-2)] matches with [1...(i-1)]
        vector<int> matchNum(len2);
        matchNum[0] = 0;
        if (len2 >= 2) {
            matchNum[1] = 0;
        }
        for (int i = 2; i < len2; ++i) {
            int j = matchNum[i - 1];
            if (j == 0) {
                if (target[i - 1] == target[j]) {
                    matchNum[i] = 1;
                } else {
                    matchNum[i] = 0;
                }
            } else {
                while (1) {
                    if (target[i - 1] == target[j]) {
                        matchNum[i] = j + 1;
                        break;
                    } else {
                        j = matchNum[j];
                        if (j == 0) {
                            if (target[i - 1] == target[0]) {
                                matchNum[i] = 1;
                            } else {
                                matchNum[i] = 0;
                            }
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0, j = 0; i <= (len1 - len2); ) {
            //compare
            int k;
            for (k = 0; k < len2 - j; ++k) {
                if (source[i + k] != target[j + k]) {
                    //first differs at position (j + k)
                    if (j + k == 0) {
                        j = 0;
                        ++i;
                    } else {
                        j = matchNum[j + k];
                        i = i + k;
                    }
                    break;
                }
            }
            if (k == len2 - j) {
                return (i - j);
            }
        }
        return -1;
    }
};
