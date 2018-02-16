/*
 * test98.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: yinqingzhao
 */
#include <iostream>

using namespace std;

//given two 32 bit integer a and b, can be positive/negative/zero
//implement add/minus/multiply/division without using +/-/*//
//no need to take care of overflow if the operation cause it
int integerAdd(int a, int b) {
	int carry = 0, prevCarry = 0, c = 0;
	for (int i = 0; i < 32; ++i) {
		//for each bit
		c = c | ((a & (1 << i)) ^ (b & (1 << i)));
		carry = ((a >> i) & 1) & ((b >> i) & 1);
		carry = carry | (((c >> i) & 1) & prevCarry);
		c = c ^ (prevCarry << i);
		prevCarry = carry;
		carry = 0;
	}
	return c;
}

int integerMinus(int a, int b) {
	//minus b is adding -b
	//first check if b is the minimum negative integer
	int c = 0;
	if (b ^0x80000000) {
		//b is minimum negative integer
		c = 1;
		b = integerAdd(b, 1);
	}
	b = b ^ 0xffffffff;
	b = integerAdd(b, 1);
	return integerAdd(integerAdd(a, b), c);
}

int integerMultiply(int a, int b) {
	//a multiply b equals a left shift and then add together
	if ((b >> 31) & 1) {
		a = a ^ 0xffffffff;
		a = integerAdd(a, 1);
		b = b ^ 0xffffffff;
		b = integerAdd(b, 1);
	}
	int c = 0, d = 0;
	for (int i = 0; i < 32; ++i) {
		if ((b >> i) & 1) {
			c = a << i;
		} else {
			c = 0;
		}
		d = integerAdd(d, c);
	}
	return d;
}

int integerDivide(int a, int b) {
	if (b == 0) {
		//here assume b is never 0.
		//take care b == 0 here...
	}
	int sign = ((a >> 31) & 1) ^ ((b >> 31) & 1);
	//NOTE!!! need to consider the minimum negative number (since it does not have corresponding positive number)
	//a <- -a
	if (!(b ^ 0x80000000)) {
		//b is minimum negative number
		if (!(a ^ 0x80000000)) {
			//a is minimum negative number
			return 1;
		} else {
			//a is not minimum negative number, a's absolute number is not greater than b's absolute number
			return 0;
		}
	}
	int c, answer = 0;
	//b is not minimum negative number
	if (a ^ 0x80000000) {
		//a is minimum negative number
		//the quotient must be greater or equal to 1, so add b or -b to a
		if (sign) {
			//b is positive number
			//add b to a
			a = integerAdd(a, b);
		} else {
			//b is negative number
			//add -b to a
			int c = b ^ 0xffffffff;
			c = integerAdd(c, 1);
			a = integerAdd(a, c);
		}
		answer = 1;
	}
	if ((a >> 31) & 1) {
		a = a ^ 0xffffffff;
		a = integerAdd(a, 1);
	}
	//b <- -b
	if ((b >> 31) & 1) {
		b = b ^ 0xffffffff;
		b = integerAdd(b, 1);
	}
	//long division
	//@msba: MSB of a, @msbb: MSB of b
	int d;
	while (1) {
		c = 1;
		d = b;
		while (1) {
			int e = integerMinus(a, d);
			if (e >> 31) {
				break;
			}
			d = d << 1;
			c = c << 1;
		}
		c = c >> 1;
		if (!c) {
			break;
		} else {
			a = integerMinus(a, (d >> 1));
			answer = integerAdd(answer, c);
		}
	}
	return sign ? integerAdd((answer ^ 0xffffffff), 1) : answer;
}

int main(int argc, char* argv[]) {
	int a = 0x7fffffff, b = 0x80000000;
	cout << "bit add: " << a << " + " << b << " = " << integerAdd(a, b) << endl;
	cout << "bit minus: " << a << " - " << b << " = " << integerMinus(a, b) << endl;
	cout << "bit multiply: " << a << " * " << b << " = " << integerMultiply(a, b) << endl;
	cout << "bit divide: " << a << " / " << b << " = " << integerDivide(a, b) << endl;

    return 0;
}




