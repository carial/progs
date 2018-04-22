/*
 * test135.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
using namespace std;

//given an integer K and a random function that can generate a number in [0 1) with equal probability, the probability of the number less than x is x
//write a function to generate a number in [0 1) with the probability that the number less than x be x^K
//random function that generates a number with equal probability in [0 1) (placeholder)
double randomNum() {
	return 0;
}

double randomNumGen(int K) {
	//with cumulative probability to be x^K, the probability density function (PDF) is K*x^K
	int i, j, success = 0;
	double x, y;
	while (!success) {
		x = random();
		for (i = 0; i < K; ++i) {
			for (j = 0; j < K - 1; ++j) {
				y = random();
				if (y > x) {
					break;
				}
			}
			if (j == K - 1) {
				success = 1;
				break;
			}
		}
	}
	return x;
}

int main(int argc, char* argv[]) {
	return 0;
}




