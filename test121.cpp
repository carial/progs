/*
 * test121.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

// given a sorted array of size N, adjust the items so that the left part of the array has no repeat items and in increasing order
// the right part do not need to care
// for example: arr=[1, 2, 2, 2, 3, 3, 4, 5, 5, 6, 7, 7, 7, 8, 9, 9], after adjust, arr=[1, 2, 3, 4, 5, 6, 7, 8, 9, ...]
// time complexity O(N), space complexity O(1)
void adjustSort(vector<int>& arr) {
	//use two indexes to track/switch items
	for (int i = 0, j = 1; j < arr.size(); ++j) {
		if (arr[i] < arr[j]) {
			++i;
			if (i < j) {
				//switch arr[i] and arr[j]
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return;
}

//given an array that contains 0, 1, 2 only. sort the array
//equal question: (1) there are 3 color of balls (blue/yellow/white) in an array, sort the array so that white balls are in the left, yellow balls in the middle, blue balls in the right
//(2) given an unsorted array and an integer K, sort the array so that all items smaller than K are in the left, equal to K in the middle, greater than K are in the right
//time complexity O(N), space complexity O(1)
void sortArray(vector<int>& arr) {
	int i, j;
	for (i = arr.size() - 1; i >= 0 && arr[i] != 0; --i); //rightmost 0
	for (j = 0; j < i; ++j) {
		if (arr[j] > arr[i]) {
			//switch arr[j] and arr[i]
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			for (; i >= 0 && arr[i] != 0; --i);
			if (i < 0) {
				//all 0s have been moved to left
				break;
			}
		}
	}
	//do the same thing for 1 and 2
	for (i = arr.size() - 1; i >= 0 && arr[i] != 1; --i); //rightmost 1
	for (j = 0; j < i; ++j) {
		if (arr[j] > arr[i]) {
			//switch arr[j] and arr[i]
			int temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			for (; i >= 0 && arr[i] != 1; --i);
			if (i < 0) {
				//all 1s have been moved to left
				break;
			}
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	//vector<int> arr({1, 2, 2, 2, 3, 3, 4, 5, 5, 6, 7, 7, 7, 8, 9, 9});
	//cout << "adjust array: " << endl;
	//adjustSort(arr);
	vector<int> arr({2, 1, 0, 0, 1, 1, 2, 2, 0, 0, 1});
	cout << "sort array of 0, 1, 2: " << endl;
	sortArray(arr);
	for (auto i : arr) {
		cout << i << ", ";
	}
	cout << endl;
}




