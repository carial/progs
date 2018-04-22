/*
 * test130.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;
//there is a machine that output a ball at one time, starting from 1, 2, 3, ..., N
//the balls drop to the basket that can hold at most K balls when N > K
//write a function that when N > K, all the balls from 1 to N has probability K/N to be held in the basket
//generate a random number on [1...N] with equal probability, for compiling purpose
int randomN(int N) {
	return 0;
}
void chooseKBalls(int N, int K) {
	if (K <= 0 || N <= K) {
		return;
	}
	vector<int> basket(K); //@basket to hold at most K balls, basket[i] holds ball #i
	for (int i = 0; i < K; ++i) {
		basket[i] = i + 1;
	}
	for (int i = K + 1; i <= N; ++i) {
		//each time ball #i drop to the basket
		int j = randomN(i);
		if (j <= K) {
			//replace #j with #i
			basket[j - 1] = i;
		}
		//else no change to basket
	}
	return;
}

int main(int argc, char* argv[]) {
	cout << "print crease direction from top to down: " << endl;
	printCreaseDirection(4);
	return 0;
}




