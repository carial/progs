/*
 * test118.cpp
 *
 *  Created on: Feb 21, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//given N sorted arrays in increasing order, print top K largest integers (if K is larger than total number of integers of N arrays, print all in decreasing order)
//for example: 219 405 538 845 971 / 148 558 / 52 99 348 691 with K=5 print out 971 845 691 558 538
//time complexity O(KlogN)
void updateHeap(const vector<vector<int>>& arr, const vector<int>& idx, vector<int>& heapN, int heapSize) {
	int i = 0;
	while (1) {
		int j = i * 2 + 1, k = i * 2 + 2;
		//compare i with j and k
		if (k < heapSize) {
			int idx1 = heapN[i], idx2 = heapN[j], idx3 = heapN[k];
			int num1 = arr[idx1][idx[idx1]], num2 = arr[idx2][idx[idx2]], num3 = arr[idx3][idx[idx3]];
			if (num1 < num2 && num3 < num2) {
				//switch idx1 and idx2
				heapN[i] = idx2;
				heapN[j] = idx1;
				i = j;
			} else if (num1 < num3 && num2 < num3) {
				//switch idx1 and idx3
				heapN[i] = idx3;
				heapN[k] = idx1;
				i = k;
			} else {
				break;
			}
		} else if (j < heapSize) {
			int idx1 = heapN[i], idx2 = heapN[j];
			int num1 = arr[idx1][idx[idx1]], num2 = arr[idx2][idx[idx2]];
			if (num1 < num2) {
				//switch idx1 and idx2
				heapN[i] = idx2;
				heapN[j] = idx1;
				i = j;
			} else {
				break;
			}
		} else {
			break;
		}
	}
	return;
}

void printTopK(const vector<vector<int>>& arr, int K) {
	//build heap of N integers, each integer is the largest of its array
	if (arr.size() == 0) {
		return;
	}
	//build heap of size N
	vector<int> heapN(arr.size());
	vector<int> idx(arr.size());
	int heapSize = arr.size();
	for (int i = 0; i < arr.size(); ++i) {
		idx[i] = arr[i].size() - 1;
		heapN[i] = i;
		//adjust
		int j = i;
		while (j >= 1) {
			int idx1 = heapN[j], idx2 =heapN[(j - 1) / 2];
			if ((arr[idx1])[idx[idx1]] > (arr[idx2])[idx[idx2]]) {
				heapN[j] = idx2;
				heapN[(j - 1) / 2] = idx1;
				j = (j - 1) / 2;
			} else {
				break;
			}
		}
	}
	//update heap. heap size may change, output K greatest integers
	for (int i = 0; i < K; ++i) {
		if (heapSize > 0) {
			//output the head
			int idx1 = heapN[0];
			cout << arr[idx1][idx[idx1]] << ", ";
			if (idx[idx1] > 0) {
				--idx[idx1];
				updateHeap(arr, idx, heapN, heapSize);
			} else {
				//no more items from array idx1, heap size shrink 1, move last one to top and update heap
				heapN[0] = heapN[heapSize - 1];
				--heapSize;
				if (heapSize > 0) {
					updateHeap(arr, idx, heapN, heapSize);
				}
			}
		} else {
			break;
		}
	}
	cout << endl;
}

int main(int argc, char* argv[]) {
	int K = 12;
	cout << "top " << K << " of arrays: " << endl;
	printTopK({{219, 405, 538, 845, 971}, {148, 558}, {52, 99, 348, 691}}, K);
}




