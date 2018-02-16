/*
 * test94.cpp
 *
 *  Created on: Jan 14, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

bool sameSign(int num1, int num2) {
	return (num1 ^ num2) > 0;
}
//given an array of positive/negative numbers, arrange so that the positive and negative numbers are interleaved
//restrictions: arrange on the array
//for example: {-1, -2, -3, 1, 2, 3} -> {-1, 1, -2, 2, -3, 3}
void interleaveNumbers(vector<int>& arr) {
	size_t len = arr.size();
	if (len == 0) {
		return;
	}
	//start at the first number
	size_t idx1 = 0, idx2 = 1;
	while (1) {
		//find next number which is not same sign as current number
		while (idx2 < len && sameSign(arr[idx1], arr[idx2])) {
			++idx2;
		}
		if (idx2 == len) {
			break;
		} else {
			if (idx2 == idx1 + 1) {
				idx1 = idx2;
				++idx2;
			} else {
				//switch idx1 + 1 with idx2
				int temp = arr[idx1 + 1];
				arr[idx1 + 1] = arr[idx2];
				arr[idx2] = temp;
				++idx1;
				idx2 = idx1 + 1;
			}
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	vector<int> num1({-1, -2, 1, -3, 2, 3});
	interleaveNumbers(num1);
	for (auto& it : num1) {
		cout << it << ", ";
	}
	cout << endl;
    return 0;
}




