/*
 * test104.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

//given an integer array with no order, find the smallest K integers among them (total number of integers is N, N >= K)
// requirement: time complexity O(NlogK) or O(N)
void modifyHeap(vector<int>& smallK, int val, int idx, int K) {
	if (idx < K) {
		//insert val to heap, smallK[0] is the largest
		smallK[idx] = val;
		int i = idx;
		while (i) {
			//parent is (i - 1) / 2
			int parent = (i - 1) / 2;
			if (smallK[parent] < val) {
				int temp = smallK[parent];
				smallK[parent] = val;
				smallK[i] = temp;
				i = parent;
			} else {
				break;
			}
		}
	} else {
		//modify heap
		if (val < smallK[0]) {
			int i = 0;
			//replace smallK[0] with val
			smallK[0] = val;
			while ((i + 1) * 2 < K || (i + 1) * 2 - 1 < K) {
				//compare with two children
				int val1, val2;
				if ((i + 1) * 2 < K) {
					val1 = smallK[(i + 1) * 2];
				} else {
					val1 = INT32_MIN;
				}
				if ((i + 1) * 2 - 1 < K) {
					val2 = smallK[(i + 1) * 2 - 1];
				} else {
					val2 = INT32_MIN;
				}
				if (val >= val1 && val >= val2) {
					break;
				} else if (val < val1 && val >= val2) {
					smallK[i] = val1;
					smallK[(i + 1) * 2] = val;
					i = (i + 1) * 2;
				} else if (val >= val1 && val < val2) {
					smallK[i] = val2;
					smallK[(i + 1) * 2 - 1] = val;
					i = (i + 1) * 2 - 1;
				} else if (val < val1 && val < val2) {
					if (val1 >= val2) {
						smallK[i] = val1;
						smallK[(i + 1) * 2] = val;
						i = (i + 1) * 2;
					} else {
						smallK[i] = val2;
						smallK[(i + 1) * 2 - 1] = val;
						i = (i + 1) * 2 - 1;
					}
				}
			}
		}
	}
	return;
}

void findKSmallest1(const vector<int>& vec, int K, vector<int>& smallK) {
	//O(NlogK) method: build heap of K elements
	if (K >= vec.size()) {
		smallK = vec;
	} else {
		smallK.resize(K);
		//read each item in @vec, build/modify heap, the root of heap is the largest integer of the K smallest integers
		for (int i = 0; i < vec.size(); ++i) {
			modifyHeap(smallK, vec[i], i, K);
		}
	}
	return;
}

// quickSelect changes input @vec so that vec[K] is the Kth largest integer in @vec
// items in @vec is unsorted
int quickSelectKthLargest(vector<int>& vec, int K, int start, int end) {
	if (K <= 0 || K > (end - start + 1)) {
		return -1;
	}
	if (end == start && K == 1) {
		return start;
	}
	if ((end - start) == 1) {
		if ((vec[start] > vec[end] && K == 1) || (vec[start] < vec[end] && K == 2)) {
			return start;
		} else {
			return end;
		}
	}
	//pick the median of (start, start+end/2, end)
	int val1 = vec[start], val2 = vec[(start + end) / 2], val3 = vec[end];
	if ((val1 < val2 && val1 > val3) || (val1 > val2 && val1 < val3)) {
		//val1 is median
		vec[start] = val2;
		vec[(start + end) / 2] = val1;
	} else if ((val3 < val2 && val3 > val1) || (val3 > val2 && val3 < val1)) {
		//val3 is median
		vec[end] = val2;
		vec[(start + end) / 2] = val3;
	}
	int k = start, l = end, m = (start + end) / 2;
	while (k < m || l > m) {
		//move all numbers larger than vec[(start + end) / 2] to its left, all numbers smaller than vec[(start + end) / 2] to its right
		for (; vec[k] >= vec[m] && k < m; ++k);
		for (; vec[l] < vec[m] && l > m; --l);
		if (k < m && l > m) {
			//switch vec[k] and vec[l]
			int temp = vec[k];
			vec[k] = vec[l];
			vec[l] = temp;
			++k;
			--l;
		} else if (k == m && l > m) {
			//switch vec[m] and vec[l]
			int temp = vec[m];
			vec[m] = vec[l];
			vec[l] = temp;
			k = m + 1;
			m = l;
		} else if (k < m && l == m) {
			//switch vec[m] and vec[k]
			int temp = vec[m];
			vec[m] = vec[k];
			vec[k] = temp;
			l = m - 1;
			m = k;
		}
	}
	if (m - start == K - 1) {
		return m;
	} else if (m - start < K - 1) {
		//search right side
		return quickSelectKthLargest(vec, (K - 1 - m + start), m + 1, end);
	} else if (m - start > K - 1) {
		//search left side
		return quickSelectKthLargest(vec, K, start, m - 1);
	}
}

void findKSmallest2(const vector<int>& vec, int K, vector<int>& smallK) {
	//O(N) method, first find the number that is exactly Kth smallest in the array.
	//traverse the array to find all numbers smaller and equal to Kth smallest number (takes O(N) time)
	vector<int> vec1(vec);
	int pos = quickSelectKthLargest(vec1, vec.size() + 1 - K, 0, vec.size() - 1);
	for (auto item : vec1) {
		if (item <= vec1[pos]) {
			smallK.push_back(item);
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	int K = 1;
#if 1
	cout << "find smallest " << K << " integers in unsorted array:" << endl;
	vector<int> vec;
	findKSmallest2({3, 4, -2, 7, 1, -10, 20, 15, -3, 14}, K, vec);
	for (auto& it : vec) {
		cout << it << ", ";
	}
	cout << endl;
#endif
#if 0
	//test quickSelect
	vector<int> vec({3, 4, -2, 7, 1, -10, 20, 15, -3, 14});
	int pos = quickSelectKthLargest(vec, vec.size() + 1 - K, 0, vec.size() - 1);
	cout << "quick select " << K << "th smallest number position is: " << pos << " number is: " << vec[pos] << endl;
#endif
    return 0;
}




