/*
 * test152.cpp
 *
 *  Created on: April 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
using namespace std;

//given an array @arr1, @arr1[i] means the one dimensional position of a resident and total number of post offices
//restriction: assume post office can only be on those resident position and resident goes to the nearest post office
//Design a algorithm to find positions for those post office so that the minimum total distance for all residents is the smallest
//return the total distance
//Example:
//arr1=[1 2 3 4 5 1000], K = 2 (2 post offices):
//put one post office on "3", second on "1000", total distance is 6, which is minimum, return 6
int findMinDistance(int preTotal, int start, int last, int totalPO, const vector<int>& arr1, vector<int>& arr2) {
	//@totalPO is the remaining offices, @start is the next position for office, @preTotal is the distance till last offices
	//@last is the last pole position
	int len = arr1.size();
	if (totalPO > 0) {
		int end = len - totalPO, total = INT32_MAX, preTotal2 = 0;
		for (int i = start; i <= end; ++i) {
			//update preTotal
			if (last == -1) {
				//first office
				if (i > 0) {
					preTotal2 += (arr1[i] - arr1[i - 1]) * i;
				}
			} else {
				preTotal2 = preTotal;
				for (int j = last + 1; j < i; ++j) {
					preTotal2 += ((arr1[j] - arr1[last] < arr1[i] - arr1[j]) ? arr1[j] - arr1[last] : arr1[i] - arr1[j]);
				}
			}

			//cout << "preTotal: " << preTotal << ", preTotal2: " << preTotal2 << ", start: " << i + 1 << ", last: " << i << ", totalPO: " << totalPO << endl;

			int ret = findMinDistance(preTotal2, i + 1, i, totalPO - 1, arr1, arr2);

			//cout << "ret: " << ret << endl;
			//cout << endl;

			if (total > ret) {
				total = ret;
				arr2[totalPO - 1] = i;
			}
		}
		return total;
	} else {
		//calculate total distance
		int total = 0;
		for (int i = len - 1; i > last; --i) {
			total += arr1[i] - arr1[last];
		}
		return (total + preTotal);
	}
}

int minPODistance(const vector<int>& arr1, int K) {
	int len = arr1.size();
	if (len == 0 || K <= 0) {
		return -1;
	}
	if (K >= len) {
		//put one post office on each resident
		return 0;
	}
	//using recursive operations
	vector<int> arr2(K);
	int ret = findMinDistance(0, 0, -1, K, arr1, arr2);
	for (auto i : arr2) {
		cout << i << ", ";
	}
	cout << endl;
	return ret;
}

int minPODistance2(const vector<int>& arr1, int K) {
	int len = arr1.size();
	if (len == 0 || K <= 0) {
		return -1;
	}
	if (K >= len) {
		return 0;
	}
	//use dynamic programming
	//for office i (0<=i<=K-1), the start position is i, end postion is (len+i-K), total (len+1-K) positions
	//each office only uses last office's information
	vector<vector<int>> distance(2, vector<int>(len + 1 - K, 0));
	//@distance[i][j] is the minimum total distance when office i is at pos j
	//@distance[i+1][j] = min(distance[i][j - 1], distance[i][j - 2]...,distance[i][i])
	//final minimum distance is min(distance[K-1][K-1], distance[K-1][K]...)
	//initialize for first office
	for (int i = 1; i <= len - K; ++i) {
		distance[0][i] += distance[0][i - 1] + (arr1[i] - arr1[i - 1]) * i;
	}

	for (int i = 1; i < K; ++i) {
		//for offices of 2, 3, ..., K
		//start position is i, end position is (len+i-K) (positions after end position is meaningless)
		for (int j = i; j <= len + i - K; ++j) {
			//for each position j, the previous office could be at (i-1) to (j-1)
			distance[i % 2][j - i] = INT32_MAX;
			for (int k = i - 1; k < j; ++k) {
				int total = distance[(i - 1) % 2][k - (i - 1)];
				for (int l = k + 1; l < j; ++l) {
					int t = (arr1[l] - arr1[k] < arr1[j] - arr1[l] ? arr1[l] - arr1[k] : arr1[j] - arr1[l]);
					total += t;
				}
				if (distance[i % 2][j - i] > total) {
					distance[i % 2][j - i] = total;
				}
			}
		}
	}
	//calculate for last office K
	//office K - 1 can be on pos (K - 1) to (len - 1)
	int ret = INT32_MAX;
	for (int i = K - 1; i < len; ++i) {
		int total = distance[(K - 1) % 2][i - (K - 1)];
		for (int j = i + 1; j < len; ++j) {
			total += arr1[j] - arr1[i];
		}
		if (ret > total) {
			ret = total;
		}
	}
	return ret;
}

//an example
int main(int argc, char* argv[]) {
	cout << "minimum distance: " << minPODistance2({1, 2, 3, 4, 5, 1000}, 3) << endl;
	return 0;
}




