/*
 * test141.cpp
 *
 *  Created on: March 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//given a sorted integer array. There may be repeated numbers in the array. The sorted array may have rotated once. find the minimum number in this array
//for example: arr=[1 2 3 4 5 6 7] or arr=[4 5 6 7 1 2 3] the minimum number is 1
//arr=[1 1 2 3 4 4 5 5 6] or arr=[1 2 3 4 4 5 5 6 1] the minimum number is 1
int minRotateArray(const vector<int>& arr) {
	//assuming ordered array is in increasing order, assuming array is non-empty
	//check the middle item with start/end items
	if (arr.size() == 1) {
		return arr[0];
	}
	int start = 0, end = arr.size() - 1, middle;
	while (start <= end) {
		middle = (start + end) / 2;
		if (arr[middle] < arr[start] && arr[middle] < arr[end]) {
			//rotation on left or arr[middle] is minimum
			if (middle == start) {
				return arr[start];
			} else if (arr[middle] >= arr[middle - 1]) {
				end = middle - 1;
			} else {
				return arr[middle];
			}
		} else if ((arr[middle] > arr[start] && arr[middle] <= arr[end]) || (arr[middle] >= arr[start] && arr[middle] < arr[end])) {
			//no rotation, arr[start] is the minimum
			return arr[start];
		} else if (arr[middle] > arr[start] && arr[middle] > arr[end]) {
			//rotation happens, and on the right part, minimum on right part
			start = middle + 1;
		} else if (arr[middle] == arr[start] && arr[middle] == arr[end]) {
			//rotation can happen on left or right or no rotation (all items equal)
			if (middle == start && middle == end) {
				return arr[start];
			} else if (middle == start) {
				start = middle + 1;
			} else if (middle == end) {
				end = middle - 1;
			} else {
				int i;
				for (i = start; i <= middle; ++i) {
					if (arr[i] < arr[start]) {
						return arr[i];
					} else if (arr[i] > arr[start]) {
						break;
					}
				}
				if (i == middle) {
					//all items between start and middle are same
					start = middle + 1;
				} else {
					start = i + 1;
					end = middle;
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
	cout << "minimum integer of array: " << minRotateArray({5, 6, 7, 1, 1, 3, 4}) << endl;
	return 0;
}




