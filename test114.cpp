/*
 * test114.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given an array of size N (N >= 2). write a function to adjust the array so that odd position contains odd number or even position contains even number. time complexity O(N), space complexity O(1)
void adjustOddEven(vector<int>& arr) {
	int numOddNumbers = 0;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] % 2) {
			++numOddNumbers;
		}
	}
	if (numOddNumbers >= arr.size() / 2) {
		//put odd number in odd position
		int temp;
		for (int i = 0, j = 1; j < arr.size(); j += 2) {
			if (!(arr[j] % 2)) {
				//there must be some even position containing odd number
				//find first even position containing odd number
				while (i < arr.size() && !(arr[i] % 2)) {
					i += 2;
				}
				//swap pos i and j
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	} else {
		//put even number in even position
		int temp;
		for (int i = 0, j = 1; i < arr.size(); i += 2) {
			if (arr[i] % 2) {
				//there must be some odd position containing even number
				//find first odd position containing even number
				while (j < arr.size() && (arr[j] % 2)) {
					j += 2;
				}
				//swap pos i and j
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	vector<int> arr({2, 7, 5, 4, 1, 3, 6});
	cout << "adjust odd/even number: " << endl;
	adjustOddEven(arr);
	for (auto i : arr) {
		cout << i << ", ";
	}
	cout << endl;
}




