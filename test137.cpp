/*
 * test137.cpp
 *
 *  Created on: March 2, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

//given a positive integer array, find the minimum unreachable sum
//assume the sum of all subset of the array is between the range [min max]
//if there is a number in that range that is not a sum of the subset of array, it is the minimum unreachable sum
//if no such number, than max+1 is the minimum unreachable sum
//for example: arr=[3, 2, 5], the range is [2 10], 4 is the minimum in that range that is not a sum of a subset
//arr=[1, 2, 4], the range is [1 7], all numbers in that range is a sum of subset, so return 8
int minUnreachableSum(const vector<int> arr) {
	if (arr.size() == 1) {
		return arr[0] + 1;
	}
	unordered_set<int> sums;
	//put sums of subarray to set
	//partialSum stores all sums of sub sets with last element is i (i = 0, 1, 2, 3,...)
	vector<int> partialSum;
	partialSum.push_back(arr[0]);
	sums.insert(partialSum[0]);
	int nextNum = arr[0];
	for (int i = 1; i < arr.size(); ++i) {
		if (nextNum > arr[i]) {
			nextNum = arr[i];
		}
	}
	for (int i = 1; i < arr.size(); ++i) {
		//update partialSum with i as maximum index
		partialSum.push_back(arr[i]);
		sums.insert(arr[i]);
		int j = partialSum.size() - 1;
		for (int k = 0; k < j; ++k) {
			int temp = partialSum[k] + arr[i];
			partialSum.push_back(temp);
			sums.insert(temp);
		}
		while (sums.find(nextNum) != sums.end()) {
			++nextNum;
		}
	}
	return nextNum;
}

int main(int argc, char* argv[]) {
	cout << "minimum unreachable sum of all sub sets: " << minUnreachableSum({3, 2, 5}) << endl;
	return 0;
}




