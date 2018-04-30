/*
 * test165.cpp
 *
 *  Created on: April 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>
using namespace std;

//Given a list of numbers, return all possible permutations.
//You can assume that there is no duplicate numbers in the list.
//Do it without recursion.

class Solution {
public:
    /*
     * @param :  A list of integers
     * @return: A list of unique permutations
     */
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        // write your code here
        vector<int>::size_type len = nums.size();
        if (len == 0) {
            return {{}};
        }
        //(1)group same numbers together
        unordered_map<int, int> freq;
        vector<int>::size_type i, j;
        for (i = 0; i < len; ++i) {
            auto it = freq.find(nums[i]);
            if (it == freq.end()) {
                freq.emplace(nums[i], 1);
            } else {
                ++it->second;
            }
        }
        i = j = 0;
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            for (i = 0; i < it->second; ++i, ++j) {
                nums[j] = it->first;
            }
        }
        vector<int>::size_type curPos = 0;
        //change @used. @used[i] means nums[i] is in position used[i]. -1 if not used yet
        vector<int> pos(len, -1), used(len, -1), res(len);
        vector<vector<int>> ret;
        while (1) {
            //fill in numbers for @curPos
            for (i = pos[curPos] + 1; i < len; ++i) {
                if (used[i] == -1) {
                    //nums[i] not used yet.
                    //since numbers may repeat, check if nums[i] can be filled in curPos
                    if ((i == 0) || (nums[i - 1] != nums[i]) || (used[i - 1] > -1 && used[i - 1] < curPos)) {
                        if (pos[curPos] != -1) {
                            //reset
                            used[pos[curPos]] = -1;
                        }
                        break;
                    }
                }
            }
            if (i == len) {
                if (curPos == 0) {
                    break;
                }
                //check if pos[curPos] == -1
                if (pos[curPos] != -1) {
                    //reset
                    used[pos[curPos]] = -1;
                    pos[curPos] = -1;
                    --curPos;
                }
            } else {
                pos[curPos] = i;
                used[i] = curPos;
                res[curPos] = nums[i];
                ++curPos;
            }
            if (curPos == len) {
                //we find a solution
                ret.push_back(res);
                --curPos;
            }
        }
        return ret;
    }
};

int main (int argc, char *argv[]) {
	Solution sol;
	vector<int> arr({1, 2, 2});
	vector<vector<int>> ret;
	ret = sol.permuteUnique(arr);
	return 0;
}
