/*
 * test164.cpp
 *
 *  Created on: April 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
using namespace std;

//Given a list of numbers, return all possible permutations.
//You can assume that there is no duplicate numbers in the list.
//Do it without recursion.

class Solution {
public:
    /*
     * @param nums: A list of integers.
     * @return: A list of permutations.
     */
    vector<vector<int>> permute(vector<int> &nums) {
        // write your code here
        vector<int>::size_type len = nums.size();
        if (len == 0) {
            return {{}};
        }
        //@used[i] means if nums[i] has been used
        //@pos[i] means ith position index
        //@res: result
        vector<vector<int>> ret;
        vector<int> used(len, 0), pos(len, -1), res(len);
        //@curPos: current position in @res to be filled
        vector<int>::size_type curPos = 0, i;
            //fill in @res at @curPos
            while (1) {
                for (i = pos[curPos] + 1; i < len; ++i) {
                    if (used[i] == 0) {
                        //not used
                        if (pos[curPos] != -1) {
                            used[pos[curPos]] = 0;
                        }
                        break;
                    }
                }
                if (i == len) {
                    if (curPos == 0) {
                        //finish
                        break;
                    }
                    //not found, reduce @curPos
                    //reset position
                    used[pos[curPos]] = 0;
                    pos[curPos] = -1;
                    --curPos;
                } else {
                    //fill in res[curPos] with nums[i]
                    res[curPos] = nums[i];
                    pos[curPos] = i;
                    used[i] = 1;
                    ++curPos;
                }
                if (curPos == len) {
                    //output res
                    ret.push_back(res);
                    --curPos;
                }
            }
            return ret;
    }
};
