/*
 * test108.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>

using namespace std;

//given a sorted integer array and an integer K, print all pairs in the array that add to K in non-decreasing order of first item
//for example: arr = [-8 -4 -3 0 1 2 4 5 8 9], K = 10
//output (1 9) (2 8)
void findPairsAddToK(const vector<int>& arr, int K, vector<pair<int, int>>& pairs) {
	if (arr.size() < 2) {
		return;
	}
	for (int i = 0, j = arr.size() - 1; i < j; ) {
		if (arr[i] + arr[j] < K) {
			//need to increase
			++i;
		} else if (arr[i] + arr[j] > K) {
			//need to decrease
			--j;
		} else {
			pairs.push_back(std::make_pair(arr[i], arr[j]));
			int prev = i;
			++i;
			while (i < j && arr[prev] == arr[i]) {
				prev = i;
				++i;
			}
		}
	}
	return;
}

//given a sorted integer array and an integer K, print all 3-tuples in the array that add to K in non-decreasing order of first item
//for example: arr = [-8 -4 -3 0 1 2 4 5 8 9], K = 10
//output (-4 5 9) (-3 4 9) (-3 5 8) (0 1 9) (0 2 8) (1 4 5)
void find3TuplesAddToK(const vector<int>& arr, int K, vector<tuple<int, int, int>>& tuples) {
	if (arr.size() < 3) {
		return;
	}
	int start = 0, end = arr.size() - 1;
	for (int i = 0; i < arr.size() - 2; ++i) {
		//for each i, find other two numbers that add to (K - arr[i])
		//@remains decreases
		int remains = K - arr[i];
		start = max(i + 1, start);
		end = min(arr.size() - 1, size_t(end));
		int set = 0;
		for (int j = start, k = end; j < k; ) {
			if (arr[j] + arr[k] > remains) {
				--k;
			} else if (arr[j] + arr[k] < remains) {
				if (set == 0) {
					start = j;
					end = k;
					set = 1;
				}
				++j;
			} else {
				tuples.push_back(make_tuple(arr[i], arr[j], arr[k]));
				int prev = j;
				++j;
				while (j < k && arr[j] == arr[prev]) {
					prev = j;
					++j;
				}
			}
		}
	}

}

int main(int argc, char* argv[]) {
	//vector<pair<int, int>> pairs;
	//findPairsAddToK({-8, -4, -3, 0, 1, 1, 4, 5, 8, 8, 8, 11, 11}, 12, pairs);
	vector<tuple<int, int, int>> tuples;
	find3TuplesAddToK({-8, -4, -3, 0, 1, 2, 4, 5, 8, 9}, 10, tuples);
	for (auto i : tuples) {
		cout << get<0>(i) << ":" << get<1>(i) << ":" << get<2>(i) << endl;
	}
    return 0;
}




