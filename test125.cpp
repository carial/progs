/*
 * test125.cpp
 *
 *  Created on: Feb 26, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//sample function to make compile OK
int genRandom5(void) {
	return 0;
}

// given a function "genRandom5" that can generate a random number from [1,2,3,4,5] with equal probability
// write a function to generate a random number from [1,2,3,4,5,6,7] with equal probability
int genRandom1To7(void) {
	// keeps calling "genRandom5" and check combination of (num1, num2)
	while (1) {
		int num1 = genRandom5(), num2 = genRandom5();
		if (num1 == 1 && num2 <= 3) {
			return 1;
		} else if ((num1 == 1 && num2 <= 5) || (num1 == 2 && num2 == 1)) {
			return 2;
		} else if (num1 == 2 && num2 <= 4) {
			return 3;
		} else if ((num1 == 2 && num2 == 5) || (num1 == 3 && num2 <= 2)) {
			return 4;
		} else if (num1 == 3 && num2 <= 5) {
			return 5;
		} else if (num1 == 4 && num2 <= 3) {
			return 6;
		} else if ((num1 == 4 && num2 <= 5) || (num1 == 5 && num2 == 1)) {
			return 7;
		}
	}
}

//given a function "rand01P" that generates 0 in probability of P, and generates 1 in probability of (1-P)
//write a function to generate a random number from [1,2,3,4,5,6] with equal probability
//sample function to make compile successful
int rand01P(void) {
	return 0;
}

int genRandom1To6(void) {
	//01 and 10 are generated in equal probability P*(1-P) and (1-P)*P
	//for other combination, ignore and continue to generate
	int num = 0; //how many times 01 or 10 have been generated
	int res = 0;
	while (1) {
		//generate twice
		int i = rand01P(), j = rand01P();
		if (i == 0 && j == 1) {
			res <<= 1;
			++num;
		} else if (i == 1 && j == 0) {
			res = (res << 1) & 1;
			++num;
		}
		if (num == 3) {
			//have enough samples
			if (res < 6) {
				return (res + 1);
			} else {
				//re-start
				num = 0;
				res = 0;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	return 0;
}




