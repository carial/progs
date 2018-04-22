/*
 * test139.cpp
 *
 *  Created on: March 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
using namespace std;

//given an integer N, return how many "1" appears in number series from 1 to N
//for example: N = 1, return 1; N = 5, 1 appears once from 1, 2, 3, 4, 5; N = 11, 1 appears 4 times from 1, 2, ..., 10, 11, return 4
int countOnes(int N) {
	if (N <= 0) {
		return 0;
	}
	int K = 0, i = N;
	//how many digits N has
	while (i) {
		++K;
		i = i / 10;
	}
	//@numOnesOnDigits[i]: how many 1s appears from 1 to 9...9 ((i + 1) digits)
	vector<int> numOnesOnDigits(K, 0);
	int numTens = 1;
	for (int j = 1; j < K; ++j) {
		numOnesOnDigits[j] = (numTens + numOnesOnDigits[j - 1]) + 8 * numOnesOnDigits[j - 1];
		numTens *= 10;
	}
	int numOnes = 0, q, r;
	while (N) {
		//check each digits
		q = N / numTens;
		if (q == 0) {
			numTens /= 10;
			--K;
		} else {
			r = N % numTens;
			if (K > 1) {
				if (q == 1) {
					numOnes += numOnesOnDigits[K - 1] + (r + 1);
				} else if (q > 1) {
					numOnes += (q - 1) * numOnesOnDigits[K - 1] + numTens + numOnesOnDigits[K - 1];
				}
			} else {
				numOnes += 1;
			}
			numTens /= 10;
			N = r;
			--K;
		}
	}
	return numOnes;
}

int main(int argc, char* argv[]) {
	int i = 1056;
	cout << "count ones for integer " << i << ": " << countOnes(i) << endl;
	return 0;
}




