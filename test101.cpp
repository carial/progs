/*
 * test101.cpp
 *
 *  Created on: Feb 6, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given a matrix, print the items from outmost to innermost circularly
//for example: the matrix
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 13 14 15 16
// print out in the following order: 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10
// requirement: space complexity O(1)
void circularPrint(int *pArr, int nCols, int nRows) {
	//dirx: 0 (left to right), 1 (right to left); diry: 0 (up to down), 1 (down to up)
	int startx = 0, endx = nCols - 1, starty = 0, endy = nRows - 1, print = 1;
	while (print) {
		print = 0;
		//print row, left to right
		if (startx <= endx && starty <= endy) {
			for (int i = startx; i <= endx; ++i) {
				cout << pArr[starty * nCols + i] << ", ";
			}
			print = 1;
		}
		//print right col, up to down
		++starty;
		if (startx <= endx && starty <= endy) {
			for (int i = starty; i <= endy; ++i) {
				cout << pArr[i * nCols + endx] << ", ";
			}
			print = 1;
		}
		//print down row, right to left
		--endx;
		if (startx <= endx && starty <= endy) {
			for (int i = endx; i >= startx; --i) {
				cout << pArr[endy * nCols + i] << ", ";
			}
			print = 1;
		}
		//print left col, down to up
		--endy;
		if (startx <= endx && starty <= endy) {
			for (int i = endy; i >= starty; --i) {
				cout << pArr[i * nCols + startx] << ", ";
			}
			print = 1;
		}
		++startx;
	}
	cout << endl;
	return;
}

int main(int argc, char* argv[]) {
	cout << "circular printing array: " << endl;
	int nCols = 1, nRows = 1;
	int *pArr = new int [nRows * nCols];
	for (int i = 0; i < nRows * nCols; ++i) {
		pArr[i] = i;
	}
	circularPrint(pArr, nCols, nRows);

	delete [] pArr;
    return 0;
}




