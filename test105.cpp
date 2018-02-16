/*
 * test105.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

//given an integer array with no order, find the smallest length of the array that needs sorting
//for example: @arr=[1 5 3 4 2 6 7], return 4. the array of smallest length that needs sorting is [5 3 4 2]
int findSmallestLengthOfSorting(const vector<int>& arr) {
	//find the first element at not in the sorted place (either increasing or decreasing) and the last element not in the sorted place
	vector<int> arr1(arr);
	sort(arr1.begin(), arr1.end());
	int start = -1, end = -1;
	for (int i = 0; i < arr1.size(); ++i) {
		if (arr1[i] != arr[i]) {
			start = i;
			for (int j = arr1.size() - 1; j >= start; --j) {
				if (arr1[j] != arr[j]) {
					end = j;
					break;
				}
			}
			break;
		}
	}
	if (start == -1) {
		return 0;
	} else {
		return end - start + 1;
	}
}

//improved method: O(N) time complexity, O(1) space complexity
int findSmallestLengthOfSorting2(const vector<int>& arr) {
	//traverse from right to left, record the minimum item of all scanned items, compare current item with the minimum item. if arr[i] > min, min must at least
	//move to left of arr[i], update the index with i. when scan finishes, index stores the left boundary that the array needs to sort
	//use the same method to find right boundary
	int index1 = -1, index2 = -1, min, max;
	for (int i = arr.size() - 1; i >= 0; --i) {
		if (i == arr.size() - 1) {
			min = arr[arr.size() - 1];
		} else if (arr[i] > min) {
			index1 = i;
		} else {
			min = arr[i];
		}
	}
	if (index1 != -1) {
		for (int i = 0; i < arr.size(); ++i) {
			if (i == 0) {
				max = arr[i];
			} else if (arr[i] < max) {
				index2 = i;
			} else {
				max = arr[i];
			}
		}
	}
	if (index1 == -1) {
		return 0;
	} else {
		return index2 - index1 + 1;
	}
}

int main(int argc, char* argv[]) {
	cout << "length of the smallest array that needs sorting: " << findSmallestLengthOfSorting2({1, 5, 3, 4, 2, 6, 7}) << endl;
    return 0;
}




