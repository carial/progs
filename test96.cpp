/*
 * test96.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//given an array @intervals containing pairs of airplane takeoff/land time
//find the maximum airplanes in the sky at one time
//landing takes priority than takeoff
//for example: intervals={{1,10}, {2,3},{5,8},{4,7}}, output 3
int maxPlanes(const vector<pair<int, int>>& intervals) {
	size_t len = intervals.size();
	if (len == 0) {
		return 0;
	}
	//(1) put takeoff time into an array @takeOff, put landing time into an array @landing
	//(2) sort @takeOff and @landing
	//(3) use two indexes to iterate @takeOff and @landing, count how many planes in current intervals
	vector<int> takeOff(len, 0), landing(len, 0);
	for (size_t i = 0; i < len; ++i) {
		takeOff[i] = intervals[i].first;
		landing[i] = intervals[i].second;
	}
	sort(takeOff.begin(), takeOff.end());
	sort(landing.begin(), landing.end());
	int numPlanes = 0, maxPlanes = 0;
	for (size_t i = 0, j = 0; i < len; ) {
		//count how many planes takeoff
		//both takeoff and landing possible
		if (takeOff[i] < landing[j]) {
			++numPlanes;
			++i;
		} else {
			--numPlanes;
			++j;
		}
		if (numPlanes > maxPlanes) {
			maxPlanes = numPlanes;
		}
	}
	return maxPlanes;
}

int main(int argc, char* argv[]) {
	vector<pair<int, int>> intervals(4);
	intervals[0] = pair<int, int>(1, 10);
	intervals[1] = pair<int, int>(2, 3);
	intervals[2] = pair<int, int>(5, 8);
	intervals[3] = pair<int, int>(4, 7);
	cout << "maximum planes: " << maxPlanes(intervals) << endl;
    return 0;
}




