/*
 * test136.cpp
 *
 *  Created on: March 2, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
using namespace std;

//given an integer path array. each item "arr[i]=j" represent i connects to j. where the capitol points to itself and there is only one capitol
//write a function to convert the path array to distance array whose item "arr[i]=j" means there are j cities whose distance to capitol is i.
//adjust on the input path array. O(N) time complexity and O(1) space complexity
//for example: path array [9 1 4 9 0 4 8 9 0 1] the distance array [1 1 3 2 3 0 0 0 0 0]
void convertPathToDistance(vector<int>& arr) {
	if (arr.size() == 0) {
		return;
	}
	if (arr.size() == 1) {
		arr[0] = 1; //only capitol
		return;
	}
	int capital = 0;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == i) {
			capital = i;
			break;
		}
	}
	//use positive to represent next node index, negative to represent distance
	for (int i = 0; i < arr.size(); ++i) {
		int distance = 0, j = i, k;
		if (i != capital && arr[i] >= 0) {
			while (1) {
				k = arr[j];
				if (j == k) {
					//capital
					break;
				} else if (k < 0) {
					distance += k;
					break;
				} else {
					j = k;
					--distance;
				}
			}
			if (distance < 0) {
				int temp = distance; //save final result
				j = arr[i];
				while (j > 0 && distance < 0) {
					k = arr[j];
					arr[j] = ++distance;
					j = k;
				}
				arr[i] = temp;
			}
		}
	}
	for (auto i : arr) {
		cout << i << ", ";
	}
	cout << endl;

	//count all distance
	//use positive number to represent counts
	int j, k;
	for (int i = 0; i < arr.size(); ) {
		j = arr[i]; //negative j: distance, positive j: counts
		if (j <= 0) {
			if (-j == i) {
				//turn arr[i] to counts
				arr[i] = 1;
				++i;
			} else {
				//count j
				k = arr[-j]; //negative k: distance, positive k: counts
				if (k > 0) {
					//counts, just increase by 1
					++arr[-j];
					++i;
				} else {
					arr[-j] = 1;
					//put k into position i, turn arr[j] into counts
					if (-j > i) {
						arr[i] = k;
					} else {
						++i;
					}
				}
			}
		} else {
			++i;
		}
	}
	//turn all negative numbers 0
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] < 0) {
			arr[i] = 0;
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	cout << "convert path array to distance statistic array: " << endl;
	vector<int> arr({9, 1, 4, 9, 0, 4, 8, 9, 0, 1});
	convertPathToDistance(arr);
	for (auto i : arr) {
		cout << i << ", ";
	}
	cout << endl;
	return 0;
}




