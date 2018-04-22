/*
 * test147.cpp
 *
 *  Created on: April 10, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//Design a function to find the Kth minimum number in 2 sorted arrays
//assuming the arrays are sorted in increasing order
//requirement:
//if array1 size is M, array2 size is N, the time complexity is O(log(min(M, N))), space complexity is O(1)
//for example: arr1=[1 2 3 4 5] arr2=[3 4 5], K = 1, the first minimum number is 1
//assume (1) K is valid (1 <= K <= arr1.size() + arr2.size()) (3) arr1 size is larger or equal to arr2 (if neither array is empty)
int findKthMin(const vector<int>arr1, const vector<int>& arr2, int K) {
	int len1 = arr1.size(), len2 = arr2.size();
	if (len2 == 0) {
		//arr2 is empty, just return Kth in arr1
		return arr1[K - 1];
	}
	//neither array is empty, assume len1 >= len2
	//K can be in the following ranges
	//1 <= K <= len2, len2 < K <= len1, len1 < K <= len1 + len2
	//first check if the Kth minimum element is in arr2
	int start = 0, end = len2 - 1, middle, idx;
	while (1) {
		middle = (start + end) / 2;
		//there are middle numbers before "middle" in arr2, check if there are K - 1 - middle numbers in arr1 before "middle"
		idx = K - 1 - middle;
		if (idx < 0) {
			//more than Kth in arr2, need to lower middle
			end = middle - 1;
		} else if (idx > len1) {
			//less than Kth in arr1, need to higher middle
			start = middle + 1;
		} else if (((idx - 1 >= 0 && arr2[middle] >= arr1[idx - 1]) || (idx - 1 < 0)) && arr2[middle] <= arr1[idx]) {
			return arr2[middle];
		} else if (arr2[middle] > arr1[idx]) {
			//lower middle
			end = middle - 1;
		} else if (arr2[middle] < arr1[idx - 1]) {
			//higher middle
			start = middle + 1;
		}
		if (end < start) {
			break;
		}
	}
	//not found in arr2
	//the possible range in arr1 is max(0, K - len2) to min(len1, K)
	start = (K - 1 - len2) > 0 ? (K - 1 - len2) : 0;
	end = K - 1 < len1 ? K - 1: len1 - 1;
	while (1) {
		middle = (start + end) / 2;
		//there are middle numbers before "middle" in arr1, check if there are K - 1 - middle numbers in arr2 before "middle"
		idx = K - 1 - middle;
		if (((idx - 1 >= 0 && arr1[middle] >= arr2[idx - 1]) || idx - 1 < 0) && arr1[middle] <= arr2[idx]) {
			return arr1[middle];
		} else if (arr1[middle] > arr2[idx]) {
			//lower middle
			end = middle - 1;
		} else if (arr1[middle] < arr2[idx - 1]) {
			//higher middle
			start = middle + 1;
		}
		if (end < start) {
			break;
		}
	}
}

//an example
int main(int argc, char* argv[]) {
	vector<int> arr1({1, 2, 3, 4, 5}), arr2({-1, 0, 5});
	for (int i = 1; i <= arr1.size() + arr2.size(); ++i) {
		cout << findKthMin(arr1, arr2, i) << ", ";
	}
	cout << endl;
	return 0;
}




