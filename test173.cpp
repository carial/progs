/*
 * test173.cpp
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

/*
Given a non-overlapping interval list which is sorted by start point.
Insert a new interval into it, make sure the list is still in order and non-overlapping
(merge intervals if necessary).
Example
Insert (2, 5) into [(1,2), (5,9)], we get [(1,9)].
Insert (3, 4) into [(1,2), (5,9)], we get [(1,2), (3,4), (5,9)].
*/
/**
 * Definition of Interval:
 */
class Interval {
public:
    int start, end;
    Interval(int start1, int end1) {
        start = start1;
        end = end1;
    }
};


class Solution {
public:
    /**
     * @param intervals: Sorted interval list.
     * @param newInterval: new interval.
     * @return: A new interval list.
     */
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // write your code here
        vector<Interval>::size_type len = intervals.size();
        if (len == 0) {
            return vector<Interval>(1, newInterval);
        }
        vector<Interval> ret;
        vector<Interval>::size_type i = 0;
        while (i < len && intervals[i].end < newInterval.start) {
             ret.push_back(intervals[i]);
             ++i;
        }
        if (i == len) {
            ret.push_back(newInterval);
            return ret;
        }
        int nextStart;
        if (intervals[i].start > newInterval.end) {
            ret.push_back(newInterval);
        } else if (intervals[i].start == newInterval.end) {
            ret.push_back(Interval(newInterval.start, intervals[i].end));
            ++i;
        } else {
            if (intervals[i].start <= newInterval.start) {
                nextStart = intervals[i].start;
            } else {
                nextStart = newInterval.start;
            }
            while (i < len && intervals[i].end < newInterval.end) {
                ++i;
            }
            if (i == len) {
                ret.push_back(Interval(nextStart, newInterval.end));
            } else {
                if (intervals[i].start > newInterval.end) {
                    ret.push_back(Interval(nextStart, newInterval.end));
                } else {
                    ret.push_back(Interval(nextStart, intervals[i].end));
                    ++i;
                }
            }
        }
        for (; i < len; ++i) {
            ret.push_back(intervals[i]);
        }
        return ret;
    }
};
