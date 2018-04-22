/*
 * test146.cpp
 *
 *  Created on: April 9, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//Design a function to find the upper median number in two sorted arrays of the same size
//assuming the arrays are sorted in increasing order
//requirement:
//if array size is N, the time complexity is O(logN), space complexity is O(1)
//for example: arr1=[1 2 3 4] arr2=[3 4 5 6] the upper median is 3 (4th smallest number)
//assume the array is not empty

int findIdx(const vector<int>arr, int num, bool isLowIdx) {
	int len = arr.size();
	if (isLowIdx) {
		//find the highest index that is smaller than num
		int start = 0, end = len - 1, middle = (start + end) / 2;
		while (1) {
			if (arr[middle] < num) {
				if (arr[middle + 1] >= num) {
					return middle + 1;
				} else {
					//arr[middle + 1] < num, search [middle + 1, end]
					start = middle + 1;
				}
			} else {
				end = middle - 1;
			}
			if (end < start) {
				//all index are larger or equal to than num
				return 0;
			} else {
				middle = (start + end) / 2;
			}
		}
	} else {
		//find the lowest index that is bigger than num
		int start = 0, end = len - 1, middle = (start + end) / 2;
		while (1) {
			if (arr[middle] > num) {
				if (arr[middle - 1] <= num) {
					return middle - 1;
				} else {
					//arr[middle - 1] > num, search [start, middle - 1]
					end = middle - 1;
				}
			} else {
				start = middle + 1;
			}
			if (end < start) {
				//all index are smaller or equal to than num
				return len - 1;
			} else {
				middle = (start + end) / 2;
			}
		}
	}
}

int findUpperMedian(const vector<int>& arr1, const vector<int>& arr2) {
	//check if two arrays have overlap
	int len = arr1.size();
	if (arr1[0] >= arr2[len - 1]) {
		return arr2[len - 1];
	} else if (arr2[0] >= arr1[len - 1]) {
		return arr1[len - 1];
	}
	//arr1 and arr2 has overlap
	int middle1 = (len - 1) / 2, middle2 = (len - 1) / 2, start, end, idx, idx2;
	if (arr1[middle1] > arr2[middle2]) {
		//median is between arr2[middle2] and arr1[middle1]
		//search from middle2 to 0 in arr2
		end = middle2;
		start = 0;
		idx = end;
		while (1) {
			//idx2 is how many numbers in arr1 that is smaller or equal to arr2[idx]
			idx2 = len - 1 - idx;
			if (((idx2 - 1 >= 0 && arr2[idx] >= arr1[idx2 - 1]) || (idx2 - 1 < 0)) && arr2[idx] <= arr1[idx2]) {
				return arr2[idx];
			} else if (arr2[idx] > arr1[idx2]) {
				//lower idx
				end = idx - 1;
			} else {
				//higher idx
				start = idx + 1;
			}
			if (end < start) {
				break;
			}
			idx = (start + end) / 2;
		}
		//search from middle1 to len - 1 in arr1
		start = middle1;
		end = len - 1;
		idx = start;
		while (1) {
			//idx2 is how many numbers in arr2 that is smaller or equal to arr1[idx]
			idx2 = len - 1 - idx;
			if (((idx2 - 1 >= 0 && arr1[idx] >= arr2[idx2 - 1]) || (idx2 - 1 < 0)) && arr1[idx] <= arr2[idx2]) {
				return arr1[idx];
			} else if (arr1[idx] > arr2[idx2]) {
				//lower idx
				end = idx - 1;
			} else {
				//higher idx
				start = idx + 1;
			}
			if (end < start) {
				break;
			}
			idx = (start + end) / 2;
		}
	} else if (arr1[middle1] < arr2[middle2]) {
		//median is between arr1[middle1] and arr2[middle2]
		//first search in arr1 from middle1 to len - 1
		start = middle1;
		end = len - 1;
		idx = start;
		while (1) {
			idx2 = len - 1 - idx;
			if (((idx2 - 1 >= 0 && arr1[idx] >= arr2[idx2 - 1]) || (idx2 - 1 < 0)) && arr1[idx] <= arr2[idx2]) {
				return arr1[idx];
			} else if (arr1[idx] > arr2[idx2]) {
				//lower idx
				end = idx - 1;
			} else {
				//higher idx
				start = idx + 1;
			}
			if (end < start) {
				break;
			}
			idx = (start + end) / 2;
		}
		//search in arr2 from 0 to middle2
		start = 0;
		end = middle2;
		idx = end;
		while (1) {
			idx2 = len - 1 - idx;
			if (((idx2 - 1 >= 0 && arr2[idx] >= arr1[idx2 - 1]) || (idx2 - 1 < 0)) && arr2[idx] <= arr1[idx2]) {
				return arr2[idx];
			} else if (arr2[idx] > arr1[idx2]) {
				//lower idx
				end = idx - 1;
			} else {
				//higher idx
				start = idx + 1;
			}
			if (end < start) {
				break;
			}
			idx = (start + end) / 2;
		}
	} else {
		return arr1[middle1];
	}
}

//an example
int main(int argc, char* argv[]) {
	vector<int> arr1({0, 1, 2}), arr2({3, 4, 5});
	cout << findUpperMedian(arr1, arr2);
	return 0;
}




