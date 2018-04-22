/*
 * test120.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

// given an array of size N, return an array that each position is the multiply of all items excluding the item at that position
// for example: arr=[2 3 1 4], return ret=[12 8 24 6]
// time complexity O(N), space complexity O(1), cannot use division
void multiplyArray(const vector<int>& arr, vector<int>& ret) {
	int multiply = 1;
	for (int i = 0; i < arr.size(); ++i) {
		ret.push_back(multiply);
		multiply *= arr[i];
	}
	multiply = 1;
	for (int i = arr.size() - 1; i >= 0; --i) {
		ret[i] *= multiply;
		multiply *= arr[i];
	}
	return;
}

int main(int argc, char* argv[]) {
	vector<int> ret;
	cout << "multiply array: " << endl;
	multiplyArray({2, 3, 1, 4}, ret);
	for (auto i : ret) {
		cout << i << ", ";
	}
	cout << endl;
}




