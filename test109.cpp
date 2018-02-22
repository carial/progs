/*
 * test110.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

//given a positive unsorted integer array and an integer K, find the maximum length of the subarray in which all elements add to K
//for example: @arr=[1 2 1 1 1], K = 3, return 3 since subarray [1 1 1] all elements add to 3 and is the longest subarray
int maxLengthArrayAddToK(const vector<int>& arr, int K) {
	if (arr.size() == 0) {
		return -1;
	}
	vector<int> sum2(arr.size());
	sum2[0] = arr[0];
	for (int i = 1; i < sum2.size(); ++i) {
		sum2[i] = sum2[i - 1] + arr[i];
	}
	int sum, maxLength = 0, j;
	for (int i = 0; i < arr.size(); ++i) {
		if (i + maxLength < arr.size()) {
			j = i + maxLength;
		} else {
			break;
		}
		for (; j < arr.size(); ++j) {
			sum = sum2[j] - sum2[i] + arr[i];
			if (sum > K) {
				break;
			} else if (sum == K) {
				if (maxLength < j - i + 1) {
					maxLength = j - i + 1;
				}
				break;
			}
		}
	}
	return maxLength;
}

//method2: time complexity O(N)
int maxLengthArrayAddToK2(const vector<int>& arr, int K) {
	int i = 0, j = 0;
	int sum = arr[0], maxLength = 0;
	if (arr.size() == 0) {
		return 0;
	}
	for (; j < arr.size(); ) {
		//check range [i...j]
		if (sum == K) {
			if (maxLength < j - i + 1) {
				maxLength = j - i + 1;
			}
			if (i == j) {
				++i;
				++j;
				if (j < arr.size()) {
					sum = arr[i];
				}
			} else {
				//since all array items are positive, [i...j] equals K, [i...j j+1] must greater than K
				++i;
				sum -= arr[i];
			}
		} else if (sum < K) {
			++j;
			if (j < arr.size()) {
				sum += arr[j];
			}
		} else {
			//sum > K
			if (i < j) {
				++i;
				sum -= arr[i];
			} else {
				++j;
				++i;
				if (j < arr.size()) {
					sum = arr[j];
				}
			}
		}
	}
	return maxLength;
}

int main(int argc, char* argv[]) {
	int K = 3;
	cout << "maximum length of array add to " << K << " :" << maxLengthArrayAddToK2({1, 2, 1, 1, 1}, K) << endl;
}




