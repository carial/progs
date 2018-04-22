/*
 * test127.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given a positive integer N, find how many trailing zeros its factorial
int getFives(int& num) {
	int ret = 0;
	while(!(num % 5)) {
		++ret;
		num /= 5;
	}
	return ret;
}

int numTrailingZeros(int N) {
	//count how many 2's and 5's in each number
	int numFives = 0;
	for (int i = 1; i <= N; ++i) {
		int num = i;
		numFives += getFives(num);
	}
	return numFives;
}

int numTrailingZeros2(int N) {
	//count how many 5's in number N, how many 5^2 in number N, ...
	int numFives = 0;

	for (int i = 5; i <= N; i *= 5) {
		numFives += N / i;
	}
	return numFives;
}

int main(int argc, char* argv[]) {
	int N = 1000000000;
	cout << "number of zeros of factorial of " << N << ": " << numTrailingZeros2(N) << endl;
	return 0;
}




