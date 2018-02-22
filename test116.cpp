/*
 * test116.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given an array, find the local minimum
//local mininum: arr[0] if array size is 1
//if array size is N (N > 1), if arr[0] < arr[1], arr[0] is local minimum; if arr[N-1] < arr[N-2], arr[N-1] is local minimum
//for 1<=i<=N-2, if arr[i] < arr[i - 1] and arr[i] < arr[i + 1], arr[i] is local minimum
//assume all adjacent items are different, find the position of any one local minimum
int localMinimumPos(const vector<int> arr) {
	if (arr.size() == 0) {
		return -1;
	}
	if (arr.size() == 1) {
		return 0;
	}
	int pos = -1;
	for (int i = 0; i < arr.size(); ++i) {
		//find arr[i] < arr[i - 1]
		if (arr[i] < arr[i + 1]) {
			pos = i;
			break;
		}
	}
	if (pos == -1) {
		pos = arr.size() - 1;
	}
	return pos;
}

int main(int argc, char* argv[]) {
	cout << "local minimum position of array: " << localMinimumPos({-90, 48, 78, 64, -40, 64, -81, -7, 66}) << endl;
}




