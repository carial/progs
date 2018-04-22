/*
 * test126.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//write one line code to get GCD of integer M and N
int getGCD(int M, int N) {
	return (M % N == 0 ? N : getGCD(N, M % N));
}

int main(int argc, char* argv[]) {
	int M = 6, N = 91;
	cout << "GCD of " << M << " and " << N << ": " << getGCD(M, N) << endl;
	return 0;
}




