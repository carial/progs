/*
 * test166.cpp
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

//Given a set of distinct integers, return all possible subsets.
//Notice
//Elements in a subset must be in non-descending order.
//The solution set must not contain duplicate subsets.

class Solution {
public:
    /**
     * @param nums: A set of numbers
     * @return: A list of lists
     */
    vector<vector<int>> subsets(vector<int> &nums) {
        // write your code here
        vector<int>::size_type len = nums.size();
        if (len == 0) {
            return {{}};
        }
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        vector<int> res;
        vector<vector<int>>::size_type size = 0, j;
        vector<int>::size_type i = 0;
        for (i = 0; i < len; ++i) {
            //for each element in @nums
            for (j = 0; j < size; ++j) {
                //insert j into each current set
                res = ret[j];
                res.push_back(nums[i]);
                ret.push_back(std::move(res));
            }
            ret.push_back(std::move(vector<int>(1, nums[i])));
            size += (size + 1);
        }
        ret.push_back({});
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
