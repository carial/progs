/*
 * test107.cpp
 *
 *  Created on: Feb 13, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>

using namespace std;

void quickSort(vector<int>& arr1, vector<int>& idx, int start, int end) {
	if (end - start <= 0) {
		return;
	} else if (end - start == 1) {
		if (arr1[start] > arr1[end]) {
			int temp = arr1[end];
			arr1[end] = arr1[start];
			arr1[start] = temp;
			temp = idx[end];
			idx[end] = idx[start];
			idx[start] = temp;
		}
		return;
	}
	//more than 2 integers
	//find median
	int i = start, j = end;
	int k = (i + j) / 2;
	while (i < k || j > k) {
		for (; i < k && arr1[i] <= arr1[k]; ++i);
		for (; j > k && arr1[j] > arr1[k]; --j);
		if (i < k && j > k) {
			//find arr1[i] > arr1[k] and arr1[j] <= arr1[k]
			int temp = arr1[i];
			arr1[i] = arr1[j];
			arr1[j] = temp;
			temp = idx[i];
			idx[i] = idx[j];
			idx[j] = temp;
			++i;
			--j;
		} else if (i < k && j == k) {
			//all right are greater than arr1[k].swap arr1[i] and arr1[k]
			int temp = arr1[i];
			arr1[i] = arr1[k];
			arr1[k] = temp;
			temp = idx[i];
			idx[i] = idx[k];
			idx[k] = temp;
			j = k - 1;
			k = i;
		} else if (i == k && j > k) {
			int temp = arr1[j];
			arr1[j] = arr1[k];
			arr1[k] = temp;
			temp = idx[j];
			idx[j] = idx[k];
			idx[k] = temp;
			i = k + 1;
			k = j;
		}
	}
	quickSort(arr1, idx, start, k - 1);
	quickSort(arr1, idx, k + 1, end);
	return;
}

//given an integer array with no order, find the maximum length of the integral subarray
//for all items in an subarray, if after sorting, neighboring two integers are apart by one, it is integral subarray
int findLengthOfLongestIntegralSubarray(const vector<int>& arr) {
	if (arr.size() == 0 || arr.size() == 1) {
		return 0;
	}
	if (arr.size() == 2) {
		if (arr[0] - arr[1] == 1 || arr[0] - arr[1] == -1) {
			return 2;
		} else {
			return 0;
		}
	}
	//@numRepeats: number of total repeated integers in range [i, j]
	//@minNum and @maxNum: minimum and maximum integer in range [i, j]
	int minNum, maxNum, maxLength = 0;
	unordered_map<int, int> numItems;
	for (int i = 0; i < arr.size() - 1; ++i) {
		int bottom = i * arr.size();
		//initialize @minNum, @maxNum, @numRepeats, @numItems
		auto it = numItems.find(arr[i]);
		if (it == numItems.end()) {
			numItems.emplace(arr[i], bottom + 1);
		} else {
			it->second = bottom + 1;
		}
		minNum = maxNum = arr[i];
		int start = (maxLength == 0) ? i + 1 : i + maxLength;
		for (int j = start; j < arr.size(); ++j) {
			//update @minNum, @maxNum, @numRepeats, @numItems
			if (arr[j] > maxNum) {
				maxNum = arr[j];
			}
			if (arr[j] < minNum) {
				minNum = arr[j];
			}
			it = numItems.find(arr[j]);
			if (it == numItems.end()) {
				numItems.emplace(arr[j], bottom + 1);
			} else {
				if (it->second >= bottom + 1) {
					break;
				} else {
					it->second = bottom + 1;
				}
			}
			//no repeats
			if (maxNum - minNum == j - i && maxLength < j - i + 1) {
				maxLength = j - i + 1;
			}
		}
	}
	return maxLength;
}

int main(int argc, char* argv[]) {
	cout << "longest integral subarray length is: " << findLengthOfLongestIntegralSubarray({5, 5, 3, 2, 6, 4, 3}) << endl;
    return 0;
}




