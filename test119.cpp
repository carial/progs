/*
 * test119.cpp
 *
 *  Created on: Feb 23, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given NxN matrix which contains only 0 or 1. find the side length of the largest square who's boundary is all "1"
//for example:
// 0 1 1 1 1
// 1 1 1 0 1
// 1 1 1 0 1
// 1 1 1 1 1
// 0 1 0 1 1
// the side length of the largest square who's boundary is all "1" is 4, so return 4
void findMaxSide(const vector<int>& sum1, const vector<int>& sum2, int& maxSide, int height) {
	//find if there is square with side length equals height
	//find pattern (height+1,....height+1) in sum1, (2,...,2) in sum2
	if (height == 0) {
		for (int i = 0; i < sum1.size(); ++i) {
			if (sum1[i] == 1 && maxSide < 1) {
				maxSide = 1;
			}
		}
	} else {
		int start = -1, end = -1;
		for (int i = 0; i < sum1.size(); ++i) {
			if (sum1[i] == (height + 1) && (i + height) < sum1.size() && sum1[i + height] == (height + 1)) {
				start = i;
				if (sum2[start] == 2) {
					if (end < start) {
						end = i;
					}
					//find end that [start...end] all equals to 2
					for (; end < sum2.size() && sum2[end] == 2; ++end);
					if (end >= i + height && maxSide < height + 1) {
						maxSide = height + 1;
						break;
					}
				}
			}
		}
	}
	return;
}

int maxSideOfSquare(const vector<vector<int>>& arr) {
	int maxSide = -1;
	vector<int> sum1(arr.size()), sum2(arr.size());
	//assume matrix is square and is not empty
	//start from 1st row, consider matrix height from 1 to arr.size() (square matrix)
	for (int i = 0; i < arr.size(); ++i) {
		//(i+height) is the last row
		for (int height = 0; i + height < arr.size(); ++height) {
			//@sum1 is rows [i...(i+height)] of array added together, @sum2 is rows i and (i+height) added togeter
			if (height == 0) {
				sum1 = arr[i];
			} else {
				for (int j = 0; j < sum1.size(); ++j) {
					sum1[j] += arr[i + height][j];
					sum2[j] = arr[i][j] + arr[i + height][j];
				}
			}
			findMaxSide(sum1, sum2, maxSide, height);
		}
	}
	return maxSide;
}

int main(int argc, char* argv[]) {
	cout << "max side length of square who's boundary are all \"1\": " << maxSideOfSquare({{0, 1, 1, 1, 1}, {1, 1, 1, 0, 1}, {1, 1, 1, 0, 1}, {1, 1, 1, 1, 1}, {0, 1, 0, 1, 1}}) << endl;
}




