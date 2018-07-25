/*
 * test192.cpp
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

/**
 * Definition for an interval.
 */
 struct Interval {
     int start;
     int end;
     Interval() : start(0), end(0) {}
     Interval(int s, int e) : start(s), end(e) {}
 };

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        int len = intervals.size();
        if (len == 0 || len == 1) {
            return intervals;
        }
        vector<Interval> ret;
        //@cur: current interval
        //no assumption that the start of intervals are aligned in non-decreasing order
        //sort the start of each interval
        std::sort(intervals.begin(), intervals.end(), m_compFunc);
        int cur = 0, start = intervals[cur].start, end = intervals[cur].end;
        while (1) {
            ++cur;
            if (cur == len) {
                ret.push_back(Interval(start, end));
                break;
            }
            //compare @cur and @next
            if (end < intervals[cur].start) {
                //output previous @start/@end
                ret.push_back(Interval(start, end));
                start = intervals[cur].start;
                end = intervals[cur].end;
            } else if (end <= intervals[cur].end) {
                end = intervals[cur].end;
            }
        }
        return ret;
    }
    private:
    struct CompFunc {
        public:
        bool operator()(const Interval& first, const Interval& second) {
            return first.start <= second.start;
        }
    };
    CompFunc m_compFunc;
};
