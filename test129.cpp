/*
 * test129.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;
//given an integer N, print the crease direction (up/down) from the top to bottom after a paper slip has been folded N times
//for example: N = 1, print: down; N = 2, print: down, down, up
//method 1: time complexity O(NlogN)
void printCreaseDirection(int N) {
	//fold N times, there will be (2^N - 1) creases
	int total = (1 << N) - 1;
	for (int i = 1; i <= total; ++i) {
		//i = 2^j*(2*K+1), even K down crease, odd K up crease.find K
		//line 20 to 23 is to test if i = x...x110000 or x...x010000 (i.e. if there is "1" or "0" adjacent to the rightmost "1")
		unsigned int j = (i - 1) ^ i;
		unsigned int k = (j << 1) + 1;
		j = j | (i & k);
		if (j == k) {
			cout << "up" << endl;
		} else {
			cout << "down" << endl;
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	cout << "print crease direction from top to down: " << endl;
	printCreaseDirection(4);
	return 0;
}




