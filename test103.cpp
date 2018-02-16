/*
 * test103.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given a matrix, zig-zag print the matrix
//for example: the matrix
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// zig-zag print:
// 1 2 5 9 6 3 4 7 10 11 8 12
// requirement: space complexity O(1)
void zigzagPrint(int *pArr, int nRows, int nCols) {
	//dir = 0: upper-right, 1: down-left
	int curX = 0, curY = 0, dir = 0;
	while (curX < nCols && curY < nRows) {
		if (dir == 0) {
			//upper-right
			while (curX < nCols && curY >= 0) {
				cout << pArr[curY * nCols + curX] << ", ";
				++curX;
				--curY;
			}
			if (curX >= nCols) {
				--curX;
				++curY;
				++curY;
			} else {
				++curY;
			}
			dir = 1;
		} else {
			//down-left
			while (curX >= 0 && curY < nRows) {
				cout << pArr[curY * nCols + curX] << ", ";
				--curX;
				++curY;
			}
			if (curY >= nRows) {
				++curX;
				++curX;
				--curY;
			} else {
				++curX;
			}
			dir = 0;
		}
	}
	cout << endl;
	return;
}

int main(int argc, char* argv[]) {
	cout << "turn square matrix 90 degrees clockwise: " << endl;
	int nRows = 4, nCols = 3;
	int *pArr = new int [nRows * nCols];
	for (int i = 0; i < nRows * nCols; ++i) {
		pArr[i] = i + 1;
	}
	zigzagPrint(pArr, nRows, nCols);
	delete [] pArr;
    return 0;
}




