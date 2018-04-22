/*
 * test151.cpp
 *
 *  Created on: April 13, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
using namespace std;

//given an array @arr1, @arr1[i] means the time to finish one painting, also given the number of painters
//restriction: each painter cannot work on the same painting, each painter can only work on consecutive paintings
//Design a algorithm to achieve the minimum time to finish all paintings
//Example:
//arr1=[3 1 4], K = 2: then painter 1 works on first and second painting, painter 2 works on the third one. minimum time is 4
//arr1=[1 1 1 4 3], K = 3: then painter 1 works on the first 3 painting, painter 2 works on fourth one, painter 3 works on the fifth one, minimum time is 4
int minPaintingHours(const vector<int>& arr1, int K) {
	int len = arr1.size();
	if (len == 0 || K <= 0) {
		return -1;
	}
	//use dynamic programming
	//@timeArr records the painting time
	//@timeArr[start][i] stores the minimum time for i painters painting paintings [start (len-1)]
	//@totalHours is @timeArr[0][K]
	vector< vector<int> > timeArr(len + 1, vector<int>(K));
	//initialize with 1 painter
	timeArr[len][0] = 0;
	for (int i = len - 1; i >= 0; --i) {
		timeArr[i][0] = timeArr[i + 1][0] + arr1[i];
	}
	//if only one painting, set to one painter's time
	for (int i = 1; i < K; ++i) {
		timeArr[len - 1][i] = timeArr[len - 1][0];
	}
	//fill in for more than 1 painter
	//timeArr[...][0] is for 1 painter
	for (int i = 1; i < K; ++i) {
		for (int j = len - 2; j >= 0; --j) {
			int total = INT32_MAX, total1 = 0, total2;
			for (int k = j; k <= len - 2; ++k) {
				total1 += arr1[k];
				total2 = total1 > timeArr[k + 1][i - 1] ? total1 : timeArr[k + 1][i - 1];
				if (total > total2) {
					total = total2;
				}
			}
			timeArr[j][i] = total;
		}
	}
	return timeArr[0][K - 1];
}

//an example
int main(int argc, char* argv[]) {
	cout << "minimum hours: " << minPaintingHours({1, 1, 1, 4, 3}, 3) << endl;
	return 0;
}




