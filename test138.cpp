/*
 * test138.cpp
 *
 *  Created on: March 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//given a character array, each character is different
//for example: arr=['A','B','C'], then A<->1, B<->2, C<->3,AA<->4,AB<->5,AC<->6...CCC<->39
//write two functions to convert between character string and integer
int convertCharArrayToInt(const vector<char>& arr, const string& input) {
	unordered_map<char, int> charToIndex;
	for (int i = 0; i < arr.size(); ++i) {
		charToIndex.emplace(arr[i], i + 1);
	}
	int ret = 0;
	for (int i = 0; i < input.size(); ++i) {
		auto it = charToIndex.find(input.at(i));
		ret *= arr.size();
		ret += it->second;
	}
	return ret;
}

void convertIntToCharArray(const vector<char>& arr, int input, string& ret) {
	if (arr.size() == 0 || input <= 0) {
		return;
	}
	int idx;
	while (input) {
		idx = input % arr.size();
		input = input / arr.size();
		if (idx == 0) {
			idx = arr.size() - 1;
			--input;
		} else {
			--idx;
		}
		ret.insert(ret.end(), arr[idx]);
	}
	return;
}

int main(int argc, char* argv[]) {
	//vector<char> arr({'A', 'B', 'C', 'D', 'E', 'F'});
	vector<char> arr(26);
	for (int i = 0; i < arr.size(); ++i) {
		arr[i] = 'A' + i;
	}
	string str("ZZZ"), str2;
	int i = 702;
	cout << "convert string " << str << " to integer: " << convertCharArrayToInt(arr, str) << endl;
	cout << "convert integer " << i << " to string: ";
	convertIntToCharArray(arr, i, str2);
	cout << str2 << endl;
	return 0;
}




