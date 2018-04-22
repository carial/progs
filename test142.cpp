/*
 * test142.cpp
 *
 *  Created on: March 20, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//given an integer array. Each item shows the score of a child. find a solution to assign candy to each child
//rules: (1) each child gets at least 1 candy no matter what the score, (2) for two adjacent children, if one has higher score, she will get more candies
//find the minimum total candies needed
//for example: score array arr=[1 2 2], the candy array [1 2 1] has the minimum total candies
//time complexity O(N), space complexity O(1), N is the size of score array (total number of children)
int minTotalCandies(vector<int>& arr) {
	if (arr.size() == 0) {
		return 0;
	}
	if (arr.size() == 1) {
		return 1;
	}
	//find "local minimum" of the score array, set the local minimum to "-1"
	int localMinPos = -1;
	for (int i = 0; i < arr.size(); ++i) {
		if (i == 0 && arr[i] <= arr[i + 1]) {
			localMinPos = i;
		} else if (i == arr.size() - 1 && arr[i] <= arr[i - 1]) {
			if (localMinPos != -1) {
				arr[localMinPos] = -1;
			}
			localMinPos = i;
		} else if (arr[i] <= arr[i - 1] && arr[i] <= arr[i + 1]) {
			if (localMinPos != -1) {
				arr[localMinPos] = -1;
			}
			localMinPos = i;
		}
	}
	if (localMinPos != -1) {
		arr[localMinPos] = -1;
	}

	//find first local minimum position
	int j = 0, i;
	for (; j < arr.size(); ++j) {
		if (arr[j] == -1) {
			break;
		}
	}
	if (j > 0) {
		//down slope from 0 to j
		i = j - 1;
		for (; i >= 0; --i) {
			arr[i] = arr[i + 1] - 1;
		}
	}

	int k, temp1, temp2, temp3, top;
	while (1) {
		k = j + 1;
		for (; k < arr.size(); ++k) {
			if (arr[k] == -1) {
				break;
			}
		}
		if (k == arr.size()) {
			break;
		}
		//for each local minimum [j...k]
		top = -1;
		for (i = j + 1; i < k; ++i) {
			if (i - 1 == j) {
				temp1 = arr[i];
				arr[i] = arr[j] - 1;
			} else if (arr[i] > temp1) {
				temp1 = arr[i];
				arr[i] = arr[i - 1] - 1;
			} else if (arr[i] == temp1) {
				//since i != k, so i and i - 1 both are top
				top = i;
				break;
			} else if (arr[i] < temp1) {
				//i - 1 is top
				top = i - 1;
				break;
			}
		}
		//temp1 is the value of top
		if (top != -1) {
			for (i = k - 1; i >= top; --i) {
				if (i + 1 == k || arr[i] > temp3) {
					temp2 = arr[i + 1] - 1;
					temp3 = arr[i];
				}
				if (i == top) {
					if (arr[i] > 0 || (arr[i] < 0 && arr[i] > temp2)) {
						arr[i] = temp2;
						break;
					}
				} else {
					arr[i] = temp2;
				}
			}
		}
		j = k;
	}
	if (j < arr.size() - 1) {
		//up hill from j to arr.size() - 1
		for (i = j + 1; i < arr.size(); ++i) {
			arr[i] = arr[i - 1] - 1;
		}
	}

	int totalCandies = 0;
	for (i = 0; i < arr.size(); ++i) {
		totalCandies += arr[i];
	}
	return -totalCandies;
}

//second question: now require if adjacent children have the same amount score, they will have the same candies
//time complexity O(N), space complexity O(1)
int minTotalCandies2(vector<int> arr) {
	if (arr.size() == 0) {
		return -1;
	} else if (arr.size() == 1) {
		return 1;
	} else if (arr.size() == 2) {
		if (arr[0] == arr[1]) {
			return 2;
		} else {
			return 3;
		}
	}

	//find local minimum
	int start = 0, i, j, k, l;
	for (i = 1; i < arr.size(); ++i) {
		if (arr[i] == arr[i - 1]) {
		} else if (arr[i] < arr[i - 1]) {
			start = i;
		} else {
			for (j = start; j >= 0 && j <= i - 1; ++j) {
				arr[j] = -1;
			}
			start = -1;
		}
	}
	for (j = start; j >= 0 && j <= i - 1; ++j) {
		arr[j] = -1;
	}
	for (i = 0; i < arr.size(); ++i) {
		if (arr[i] == -1) {
			break;
		}
	}
	//i is index of local minimum
	if (i > 0) {
		int temp = arr[i];
		for (j = i - 1; j >= 0; --j) {
			if (arr[j] > temp) {
				temp = arr[j];
				arr[j] = arr[j + 1] - 1;
			} else {
				arr[j] = arr[j + 1];
			}
		}
	}
	while (1) {
		int temp, temp2;
		for (j = i + 1; j < arr.size(); ++j) {
			if (arr[j] == -1) {
				break;
			}
		}
		if (j == arr.size()) {
			temp = arr[i];
			for (k = i + 1; k < arr.size(); ++k) {
				if (arr[k] > temp) {
					temp = arr[k];
					arr[k] = arr[k - 1] - 1;
				} else {
					arr[k] = arr[k - 1];
				}
			}
			break;
		}
		//find maximum index between [i...j]
		start = -1;
		temp = arr[i];
		for (k = i + 1; k < j; ++k) {
			if (arr[k] > temp) {
				temp = arr[k];
				arr[k] = arr[k - 1] - 1;
				start = k;
			} else if (arr[k] == temp) {
				arr[k] = arr[k - 1];
			} else {
				//[start...(k-1)] is maximum index, temp is the maximum value
				break;
			}
		}
		//from j to (k-1)
		temp2 = arr[k - 1];
		arr[k - 1] = temp;
		temp = arr[j];
		for (l = j - 1; l >= k - 1; --l) {
			if (arr[l] > temp) {
				temp = arr[l];
				arr[l] = arr[l + 1] - 1;
			} else if (arr[l] == temp) {
				arr[l] = arr[l + 1];
			}
		}
		temp2 = temp2 < arr[k - 1] ? temp2 : arr[k - 1];
		for (l = start; l <= k - 1; ++l) {
			arr[l] = temp2;
		}
		i = j;
	}
	int totals = 0;
	for (i = 0; i < arr.size(); ++i) {
		totals += arr[i];
	}
	return -totals;
}

int main(int argc, char* argv[]) {
	vector<int> arr({1, 2, 2});
	cout << "minimum total candies: "<< minTotalCandies2(arr) << endl;
	return 0;
}




