/*
 * test110.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//given a positive unsorted integer array and an integer K, the items in array can be positive, negative, or zero. find the maximum length of the subarray in which all elements add to K
//time complexity O(N^2), space complexity O(1)
int maxLengthArrayAddToK(const vector<int>& arr, int K) {
	if (arr.size() == 0) {
		return -1;
	}
	//@dir 0: from left to right, 1: from right to left
	int maxLength = 0, sum = 0, dir;
	for (int i = 0; i < arr.size(); ++i) {
		sum += arr[i];
	}
	if (sum == K) {
		return arr.size();
	}
	dir = 1; //from right to left
	int i;
	for (int length = arr.size() - 1; length > 0; --length) {
		if (dir == 1) {
			sum -= arr[length];
		} else {
			sum -= arr[arr.size() - 1 - length];
		}
		dir = 1 - dir;
		if (dir) {
			i = arr.size() - 1;
		} else {
			i = 0;
		}
		while(1) {
			if (sum == K) {
				return length;
			}
			if (dir) {
				--i;
				if ( i - length + 1 >= 0) {
					sum -= arr[i + 1];
					sum += arr[i - length + 1];
				} else {
					break;
				}
			} else {
				++i;
				if (i + length <= arr.size()) {
					sum += arr[i + length - 1];
					sum -= arr[i - 1];
				} else {
					break;
				}
			}
		}
	}
	return maxLength;
}

//method2: time complexity O(N), space complexity O(N)
int maxLengthArrayAddToK2(const vector<int>& arr, int K) {
	//@sum is the total from 0 to i
	int maxLength = 0, sum = 0;
	//@pos is the leftmost position that [0...i] total is sum
	unordered_map<int, int> pos;
	//to handle single item value equals to K, 0 always appears and in pos -1
	pos.emplace(0, -1);
	for (int i = 0; i < arr.size(); ++i) {
		sum += arr[i];
		//check if sum - K has appeared before
		auto it = pos.find(sum - K);
		if (it != pos.end()) {
			if (maxLength < i - it->second) {
				maxLength = i - it->second;
			}
		}
		it = pos.find(sum);
		if (it == pos.end()) {
			pos.emplace(sum, i);
		}
	}
	return maxLength;
}

int main(int argc, char* argv[]) {
	int K = 3;
	cout << "maximum length of array add to " << K << " :" << maxLengthArrayAddToK2({1, -1, -2, 6, 3, 1, 1}, K) << endl;
}




