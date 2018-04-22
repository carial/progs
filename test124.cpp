/*
 * test124.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// given an unsorted integer array, find the maximum difference between two adjacent items after sorting
// time complexity: O(N)
// for example: arr=[9 3 1 10], the maximum difference after sort is 6
// arr=[5 5 5 5], the maximum difference after sort is 0
int maxSortedDifference(const vector<int>& arr) {
	int diff = 0;
	//use the idea of bucket sorting: key is to choose number of bucket such that at least there are one bucket empty (number of bucket should be greater than total items in the array)
	//since all items in one bucket the max difference cannot be greater than bucket length, the max difference must happen for items in different bucket
	//keep (min, max) pair for each bucket and check min[i+1]-max[i] and find the max value
	if (arr.size() == 1) {
		return -1;
	}
	int minItem = arr[0], maxItem = arr[0];
	for (int i = 1; i < arr.size(); ++i) {
		if (arr[i] < minItem) {
			minItem = arr[i];
		}
		if (arr[i] > maxItem) {
			maxItem = arr[i];
		}
	}
	vector<pair<int, int>> bucketMinMax(arr.size() + 1, make_pair(maxItem + 1, minItem - 1));
	bucketMinMax[arr.size()] = make_pair(maxItem, maxItem);
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] != maxItem) {
			//put arr[i] to bucket
			int j = (arr[i] - minItem) * arr.size() / (maxItem - minItem);
			if (bucketMinMax[j].first > arr[i]) {
				bucketMinMax[j].first = arr[i];
			}
			if (bucketMinMax[j].second < arr[i]) {
				bucketMinMax[j].second = arr[i];
			}
		}
	}
	int i = 0, j = 0;
	while (1) {
		while (bucketMinMax[i].first == maxItem + 1) {
			++i;
		}
		if (i == arr.size()) {
			break;
		}
		j = i + 1;
		while (bucketMinMax[j].first == maxItem + 1) {
			++j;
		}
		if (diff < bucketMinMax[j].first - bucketMinMax[i].second) {
			diff = bucketMinMax[j].first - bucketMinMax[i].second;
		}
		++i;
	}
	return diff;
}

int main(int argc, char* argv[]) {
	cout << "max sorted difference: " << maxSortedDifference({5, 5, 5, 5}) << endl;
}




