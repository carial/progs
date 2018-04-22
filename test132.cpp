/*
 * test132.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
using namespace std;

//given an unsorted array, for all the left/right partition, find the max absolute difference between maximum number in left and maximum number in right
//method1: time complexity O(N), space complexity O(1)
int maxAbsDiff(const vector<int>& arr) {
	if (arr.empty()) {
		return -1;
	}
	int idx = 0, maxNum = arr[0];
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] > maxNum) {
			maxNum = arr[i];
			idx = i;
		}
	}
	int maxDiff = 0;
	//case 1: maxNum in the right part, find left part maximum
	if (idx > 0 && maxDiff < maxNum - arr[0]) {
		maxDiff = maxNum - arr[0];
	}
	//case 2: maxNum in the left part, find right part maximum
	if (idx < arr.size() - 1 && maxDiff < maxNum - arr[arr.size() - 1]) {
		maxDiff = maxNum - arr[arr.size() - 1];
	}
	return maxDiff;
}

int main(int argc, char* argv[]) {
	cout << "max absolute difference between maximum of left part and maximum of right part: " << maxAbsDiff({2, 7, 3, 1, 1}) << endl;
	return 0;
}




