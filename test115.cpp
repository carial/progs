/*
 * test115.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given an array, the items can be negative, positive, or zero. write a function to find the maximum sum of all sub arrays. time complexity O(N), space complexity O(1)
int maxSumOfSubArray(const int arr[][3], int row) {
	int maxSum = arr[0][0];
	int (*sum)[3] = new int [row] [3];
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < 3; ++j) {
			sum[i][j] = 0;
		}
	}
	//assume array is not empty
	//calculate by columns
	//sum[i][k] is the max summation from column k to j (0 <= k <= j), time complexity is O(N^3)
	int lineSum = 0;
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < row; ++i) {
			if (i == 0) {
				for (int k = j; k >= 0; --k) {
					sum[i][k] += arr[i][j];
					if (maxSum < sum[i][k]) {
						maxSum = sum[i][k];
					}
				}
			} else {
				lineSum = 0;
				for (int k = j; k >= 0; --k) {
					lineSum += arr[i][k];
					if (sum[i - 1][k] > 0) {
						sum[i][k] = sum[i - 1][k] + lineSum;
					} else {
						sum[i][k] = lineSum;
					}
					if (maxSum < sum[i][k]) {
						maxSum = sum[i][k];
					}
				}
			}
		}
	}
	return maxSum;
}

int main(int argc, char* argv[]) {
	//int arr[3][3] = {{-90, 48, 78}, {64, -40, 64}, {-81, -7, 66}};
	int arr[3][3] = {{-1, -1, -1}, {-1, 2, 2}, {-1, -1, -1}};
	cout << "max sum of subarray: " << maxSumOfSubArray(arr, 3) << endl;
}




