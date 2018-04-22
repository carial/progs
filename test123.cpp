/*
 * test123.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// given a unsorted integer array, find the minimum positive integer that does not appear in the array
// for example: arr=[-1 2 10 4], return 1; arr=[1 2 3 4], return 5
// method 1: need to change original array time complexity O(N) and space complexity O(1)
int minPositiveInteger(vector<int>& arr) {
	int ret = 1;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] > 0 && arr[i] <= arr.size()) {
			int j = arr[i] - 1;
			if (arr[i] != i + 1 && arr[j] != arr[i]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
				--i;
			}
		}
	}
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == ret) {
			++ret;
		} else {
			break;
		}
	}
	return ret;
}

//method 2: use a set, time complexity O(N), space complexity O(N)
int minPositiveInteger2(const vector<int>& arr) {
	int ret = 1;
	unordered_set<int> posInt;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] > 0 && arr[i] <= arr.size()) {
			auto it = posInt.find(arr[i]);
			if (it == posInt.end()) {
				posInt.emplace(arr[i]);
			}
		}
	}
	for (int i = 1; i <= arr.size(); ++i) {
		auto it = posInt.find(ret);
		if (it == posInt.end()) {
			break;
		} else {
			++ret;
		}
	}
	return ret;
}

int main(int argc, char* argv[]) {
	//vector<int> arr({-1, 2, 10, 4});
	vector<int> arr({2, 1, 4, 3});
	cout << "min positive integer: " << minPositiveInteger(arr) << endl;
}




