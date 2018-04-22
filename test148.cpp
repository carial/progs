/*
 * test148.cpp
 *
 *  Created on: April 10, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//Design a function to find the top K biggest sum from two sorted array1 and array2
//restriction: two numbers must one from array1 and another from array2
//assuming the arrays are sorted in increasing order
//requirement:
//the time complexity is O(KlogK)
//for example: arr1=[1 2 3 4 5] arr2=[3 5 7 9 11], K = 4, then output 16 15 14 14
void updateHeap(vector<int>& sumHeap, const vector<int>& arr2IdxToArr1Idx, int heapSize, const vector<int>& arr1, const vector<int> & arr2) {
	int p = 0, q, r, change;
	int len2 = arr2.size();
	while (1) {
		q = (p + 1) * 2 - 1;
		r = (p + 1) * 2;
		if (q >= heapSize) {
			q = -1;
		}
		if (r >= heapSize) {
			r = -1;
		}
		change = p;
		if (q != -1 && (arr2[sumHeap[change]] + arr1[arr2IdxToArr1Idx[len2 - 1 - sumHeap[change]]] <
				arr2[sumHeap[q]] + arr1[arr2IdxToArr1Idx[len2 - 1 - sumHeap[q]]])) {
			change = q;
		}
		if (r != -1 && (arr2[sumHeap[change]] + arr1[arr2IdxToArr1Idx[len2 - 1 - sumHeap[change]]] <
				arr2[sumHeap[r]] + arr1[arr2IdxToArr1Idx[len2 - 1 - sumHeap[r]]])) {
			change = r;
		}
		if (change == p) {
			break;
		} else if (change == q) {
			//switch p and q
			int temp = sumHeap[p];
			sumHeap[p] = sumHeap[q];
			sumHeap[q] = temp;
		} else {
			//switch p and r
			int temp = sumHeap[p];
			sumHeap[p] = sumHeap[r];
			sumHeap[r] = temp;
		}
	}
	return;
}

void findTopKMaxSum(const vector<int>arr1, const vector<int>& arr2, int K) {
	int len1 = arr1.size(), len2 = arr2.size();
	if (len1 == 0 || len2 == 0 || K <= 0) {
		return;
	}
	K = (K < len1 * len2) ? K : len1 * len2;
	int size1 = len2 < K ? len2 : K;
	//@arr1Idx: stores the index in @arr1 for the biggest K (or len2) numbers in @arr2
	//@arr1Idx[i] is the current index in @arr1 corresponding to @arr2[len2 - 1 - i]
	vector<int> arr2IdxToArr1Idx(size1, len1 - 1);
	//construct big heap of K numbers
	vector<int> sumHeap(size1);
	for (int i = 0; i < size1; ++i) {
		//since initially (arr2[len2 - 1 - i] + arr1[arr2IdxToArr1Idx[i]]) is in decreasing order,
		//so it is OK to just add the index to the end of heap
		sumHeap[i] = len2 - 1 - i;
	}
	int totalNums = 0;
	while (totalNums < K) {
		//output the head from heap
		int arr2Idx = sumHeap[0], arr1Idx = arr2IdxToArr1Idx[len2 - 1 - sumHeap[0]];
		cout << (arr2[arr2Idx] + arr1[arr1Idx]) << ", ";
		if (arr1Idx == 0) {
			//no more numbers from @arr1 to add to @arr2[arr2Idx]
			//move last item to heap head and update
			sumHeap[0] = sumHeap[size1 - 1];
			--size1;
			updateHeap(sumHeap, arr2IdxToArr1Idx, size1, arr1, arr2);
		} else {
			--arr2IdxToArr1Idx[len2 - 1 - arr2Idx];
			updateHeap(sumHeap, arr2IdxToArr1Idx, size1, arr1, arr2);
		}
		++totalNums;
	}
	cout << endl;
}

//an example
int main(int argc, char* argv[]) {
	vector<int> arr1({1, 2, 3, 4, 5}), arr2({3, 5, 7, 9, 11});
	findTopKMaxSum(arr1, arr2, 4);
	return 0;
}




