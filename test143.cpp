/*
 * test143.cpp
 *
 *  Created on: March 20, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_set>
using namespace std;

//A source outputs numbers from 1 to N in random order. Design a function that receives the number one by one and print out those numbers in order.
//for example:
//the numbers from 1 to 10 is output in the following order:
//2 1 6 4 5 3 10 8 7 9
//the function will print when receiving each number: () (1, 2) () () () (3, 4, 5, 6) () () () (7, 8, 9, 10)
void printNumbers(const vector<int>& arr) {
	int nextNum = 1;
	unordered_set<int> numPool;
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == nextNum) {
			cout << "(" << nextNum;
			++nextNum;
			while (1) {
				auto it = numPool.find(nextNum);
				if (it != numPool.end()) {
					cout << " " << *it;
					++nextNum;
				} else {
					break;
				}
			}
			cout << "), ";
		} else {
			numPool.insert(arr[i]);
		}
	}
	cout << endl;
	return;
}

int main(int argc, char* argv[]) {
	vector<int> arr({2, 1, 6, 4, 5, 3, 10, 8, 7, 9});
	printNumbers(arr);
	return 0;
}




