/*
 * test140.cpp
 *
 *  Created on: March 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//given an integer (positive or negative), find if it is palindrome
bool isPalindrome(int N) {
	if (N > -10 && N < 10) {
		return true;
	}
	//!!!need to consider minimum value of negative integer, there is no absolute value corresponding to it!!!
	//check separately
	if (N == INT32_MIN) {
		return false;
	}
	N = N > 0 ? N : -N;
	//find how many digits N has
	int i = N, numTens = 1;
	while (i) {
		i /= 10;
		numTens *= 10;
	}
	numTens /= 10;
	i = N;
	while (i) {
		//check for palindrome
		if ((i / numTens) != (i % 10)) {
			return false;
		}
		i -= (i / numTens) * numTens;
		i = i / 10;
		numTens /= 10;
	}
	return true;
}

int main(int argc, char* argv[]) {
	int i = 1056;
	cout << "check " << i << " for palindrome: " << (isPalindrome(i) ? "true" : "false") << endl;
	return 0;
}




