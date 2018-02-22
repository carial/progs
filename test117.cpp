/*
 * test117.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//given an double array, the items can be negative, zero, or positive. find the maximum multiplication of the subarray
//for example: arr=[-2.5, 4, 0, 3, 0.5, 8, -1], the max multiplication is 12 from [3, 0.5, 8]
int maximumMultiply(const vector<double> arr) {
	//assume array is not empty
	double maxMultiply = arr[0];
	//use dynamic programming
	//@greatest is the max multiply value till arr[i], @smallest is the min multiply value till arr[i]
	//save @smallest is because the future items may be negative
	double greatest = 1.0, smallest = 1.0;
	for (int i = 0; i < arr.size(); ++i) {
		double temp1, temp2, maxValue;
		temp1 = greatest * arr[i];
		temp2 = smallest * arr[i];
		//three choices: temp1, temp2, arr[i]
		maxValue = temp2;
		if (temp1 < arr[i] && temp2 < arr[i]) {
			maxValue = arr[i];
			if (temp1 < temp2) {
				smallest = temp1;
			} else {
				smallest = temp2;
			}
		} else if (temp2 < temp1 && arr[i] < temp1) {
			maxValue = temp1;
			if (temp2 < arr[i]) {
				smallest = temp2;
			} else {
				smallest = arr[i];
			}
		} else {
			if (temp1 < arr[i]) {
				smallest = temp1;
			} else {
				smallest = arr[i];
			}
		}
		if (maxMultiply < maxValue) {
			maxMultiply = maxValue;
		}
		greatest = maxValue;
	}
	return maxMultiply;
}

int main(int argc, char* argv[]) {
	cout << "maximum multiply of array: " << maximumMultiply({-2.5, 4, 0, 3, 0.5, 8, -1}) << endl;
}




