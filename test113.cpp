/*
 * test113.cpp
 *
 *  Created on: Feb 16, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//natural number sorting:
//given an array of size N containing natural number [1...N]. sort the array in increasing order. time complexity O(N), space complexity O(1)
void naturalSort(vector<int>& arr) {
	int temp;
	for (int i = 0; i < arr.size(); ) {
		if (arr[i] != i + 1) {
			temp = arr[arr[i] - 1];
			//arr[i] should be put to arr[i] - 1
			arr[arr[i] - 1] = arr[i];
			arr[i] = temp;
		} else {
			++i;
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	vector<int> arr({2, 7, 5, 4, 1, 3, 6});
	cout << "sort natural number: " << endl;
	naturalSort(arr);
	for (auto i : arr) {
		cout << i << ", ";
	}
	cout << endl;
}




