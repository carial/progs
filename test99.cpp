/*
 * test99.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: yinqingzhao
 */
#include <iostream>

using namespace std;

//given one 32 bit integer a, can be positive/negative/zero, count how many 1's in it
int countOnes(int a) {
	int c = 0;
	while (a) {
		a = a & (a - 1);
		++c;
	}
	return c;
}

int main(int argc, char* argv[]) {
	int a = 0x80000000;
	cout << "one bit count: " << countOnes(a) << endl;

    return 0;
}




