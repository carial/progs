/*
 * test195.cpp
 *
 *  Created on: May 14, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
Your algorithm should run in O(n) complexity.
Example:
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int len = nums.size();
        int longestLength = 0;
        struct Sequence {
            public:
            int m_start;
            int m_end;
            Sequence(int start, int end) : m_start(start), m_end(end) {};
        };
        unordered_map<int, Sequence*> startToSequencePtr;
        unordered_map<int, Sequence*> endToSequencePtr;
        for (int i = 0; i < len; ++i) {
            if (startToSequencePtr.find(nums[i]) != startToSequencePtr.end() || endToSequencePtr.find(nums[i]) != endToSequencePtr.end()) {
                //@nums[i] belongs to some sequence
                continue;
            }
            //find if @nums[i] is the start point of some sequence
            unordered_map<int, Sequence*>::iterator it1 = startToSequencePtr.find(nums[i] + 1);
            //find if @nums[i] is the end point of some sequence
            unordered_map<int, Sequence*>::iterator it2 = endToSequencePtr.find(nums[i] - 1);
            if (it1 != startToSequencePtr.end() && it2 != endToSequencePtr.end()) {
                int start = it2->second->m_start, end = it1->second->m_end, length = end - start + 1;
                if (length > longestLength) {
                    longestLength = length;
                }
                unordered_map<int, Sequence*>::iterator it3 = startToSequencePtr.find(it2->second->m_start);
                unordered_map<int, Sequence*>::iterator it4 = endToSequencePtr.find(it1->second->m_end);
                it3->second->m_end = end;
                startToSequencePtr.erase(it1);
                delete it4->second;
                endToSequencePtr.erase(it2);
                it4->second = it3->second;
            } else if (it1 != startToSequencePtr.end()) {
                //add @nums[i] to seq
                Sequence *seq = it1->second;
                seq->m_start = nums[i];
                int length = seq->m_end - seq->m_start + 1;
                if (longestLength < length) {
                    longestLength = length;
                }
                startToSequencePtr.erase(it1);
                startToSequencePtr.emplace(nums[i], seq);
            } else if (it2 != endToSequencePtr.end()) {
                //add @nums[i] to seq
                Sequence *seq = it2->second;
                seq->m_end = nums[i];
                int length = seq->m_end - seq->m_start + 1;
                if (longestLength < length) {
                    longestLength = length;
                }
                endToSequencePtr.erase(it2);
                endToSequencePtr.emplace(nums[i], seq);
            } else {
                //add new sequence, both start/end are nums[i]
                if (longestLength < 1) {
                    longestLength = 1;
                }
                Sequence *seq = new Sequence(nums[i], nums[i]);
                startToSequencePtr.emplace(nums[i], seq);
                endToSequencePtr.emplace(nums[i], seq);
            }
        }
        for (auto i : startToSequencePtr) {
            delete i.second;
        }
        return longestLength;
    }
};
