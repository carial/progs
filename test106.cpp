/*
 * test106.cpp
 *
 *  Created on: Feb 11, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

//given an integer array with no order, find the integer that appears more than half the size of array
//if no such integer, print some information
void findIntegerAppearsMoreThanHalf(const vector<int>& arr) {
	//delete 2 different numbers each time. If a number appears more than half the size of array, it will be left in the end
	int nums = 0, val;
	for (int i = 0; i < arr.size(); ) {
		if (nums == 0) {
			//find 2 different numbers
			val = arr[i];
			++nums;
			++i;
			while (i < arr.size() && arr[i] == val) {
				++nums;
				++i;
			}
			if (i == arr.size()) {
				//the rest numbers are all same
				break;
			}
			//find arr[i] != val, remove (val, arr[i]) pair
			--nums;
			++i;
		}
	}
	if (nums == 0) {
		//no numbers appears more than half the size of array
		cout << "no number appears more than half the size of array" << endl;
	} else {
		//still need to check again to make sure this number appears more than half the size of array
		nums = 0;
		for (int i = 0; i < arr.size(); ++i) {
			if (arr[i] == val) {
				++nums;
			}
		}
		if (nums > (arr.size() / 2)) {
			cout << "the number appears more than half the size of array: " << val << endl;
		} else {
			cout << "no number appears more than half the size of array" << endl;
		}
	}
	return;
}

//given an unsorted integer array of size N, for an integer K, find the integers that appears more than N/K times in the array
//if no such integer, print some information
void findIntegerAppearsMoreThanNK(const vector<int>& arr, int K) {
	//the ideal is to "remove" K different integers at a time until there are less than K integers
	//if an integer appears more than N/K times, it will remain till the last
	//use an array to store the current K different integers
	vector<int> nums(K), val(K);
	for (int i = 0; i < arr.size(); ++i) {
		//for current integer arr[i], find a slot in @nums and update
		int idxNum = -1;
		for (int j = 0; j < K; ++j) {
			if (nums[j] == 0 && idxNum == -1) {
				//first empty slot
				idxNum = j;
			} else if (nums[j] != 0 && val[j] == arr[i]) {
				//find same integer
				idxNum = j;
				break;
			}
		}
		if (idxNum != -1) {
			++nums[idxNum];
			val[idxNum] = arr[i];
		} else {
			//all slots are full, remove K different integers
			for (int j = 0; j < K; ++j) {
				--nums[j];
			}
			--i;
		}
	}
	//check all integers left
	bool found = false;
	for (int i = 0; i < K; ++i) {
		if (nums[i] > 0) {
			nums[i] = 0;
			for (int j = 0; j < arr.size(); ++j) {
				if (arr[j] == val[i]) {
					++nums[i];
				}
			}
			if (nums[i] > arr.size() / K) {
				cout << "item " << val[i] << " appears more than " << arr.size() / K << endl;
				found = true;
			}
		}
	}
	if (!found) {
		cout << "no item appears more than " << arr.size() / K << endl;
	}
	return;
}

int main(int argc, char* argv[]) {
	//findIntegerAppearsMoreThanHalf({4});
	findIntegerAppearsMoreThanNK({4, 2, 2, 7, 6, 3, 4, 10, 7}, 5);
    return 0;
}




