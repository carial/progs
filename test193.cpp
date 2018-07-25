/*
 * test193.cpp
 *
 *  Created on: May 14, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
*/

/**
 * Definition for an interval.
 */
 struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };

 /**
  * Definition for an interval.
  * struct Interval {
  *     int start;
  *     int end;
  *     Interval() : start(0), end(0) {}
  *     Interval(int s, int e) : start(s), end(e) {}
  * };
  */
 class Solution {
 public:
     vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
         int len = intervals.size();
         int cur = 0;
         vector<Interval> ret;
         for (; cur < len && intervals[cur].end < newInterval.start; ret.push_back(intervals[cur]), ++cur);
         if (cur == len) {
             //add @newInterval
             ret.push_back(newInterval);
         } else {
             //intervals[cur].end >= newInterval.start
             //intervals[cur - 1].end < newInterval.start or cur == 0
             //compare intervals[cur].start with newInterval.start
             int start = intervals[cur].start <= newInterval.start ? intervals[cur].start : newInterval.start;
             //find the end of the new interval
             for (; cur < len && intervals[cur].start <= newInterval.end; ++cur);
             --cur;
             //compare intervals[cur].end with newInterval.end
             int end = intervals[cur].end <= newInterval.end ? newInterval.end : intervals[cur].end;
             ret.push_back(Interval(start, end));
             ++cur;
             for (; cur < len; ret.push_back(intervals[cur]), ++cur);
         }
         return ret;
     }
 };
