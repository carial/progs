/*
 * test167.cpp
 *
 *  Created on: April 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//Given a set of integers, return all possible subsets.
//Notice
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.
//integers in the set may repeat

class Solution {
public:
    /**
     * @param nums: A set of numbers.
     * @return: A list of lists. All valid subsets.
     */
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        // write your code here
        vector<int>::size_type len = nums.size();
        if (len == 0) {
            return {{}};
        }
        std::sort(nums.begin(), nums.end());
        vector<vector<int>>::size_type size, i;
        vector<int> res, start(len, 0);
        vector<int>::size_type j;
        vector<vector<int>> ret;
        ret.push_back({});
        res.push_back(nums[0]);
        ret.push_back(std::move(res));
        start[0] = 1;
        for (j = 1; j < len; ++j) {
            //@size is the current total size of @ret
            size = ret.size();
            if (nums[j - 1] != nums[j]) {
                //insert nums[j] from 0 to size
                i = 0;
            } else {
                i = start[j - 1];
            }
            for (; i < size; ++i) {
                res = ret[i];
                res.push_back(nums[j]);
                ret.push_back(std::move(res));
            }
            start[j] = size;
        }
        return ret;
    }
};
#if 0
int main (int argc, char *argv[]) {
	Solution sol;
	vector<int> arr({1, 2, 2});
	vector<vector<int>> ret;
	ret = sol.permuteUnique(arr);
	return 0;
}
#endif
