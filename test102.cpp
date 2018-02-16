/*
 * test102.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given a square matrix, turn it 90 degrees clockwise
//for example: the matrix
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 13 14 15 16
// after turning it 90 degrees clockwise:
// 13 9 5 1
// 14 10 6 2
// 15 11 7 3
// 16 12 8 4
// requirement: space complexity O(1)
void turn90Clockwise(int *pArr, int nRows) {
	//90 degrees clockwise:
	//(nRows - 1, 0) -> (0, 0), (r, c) -> (c, nRows - 1 - r)
	//original position: (r, c) -> r * nCols + c, new position: c * nCols + nRows - 1 - r
	//turn 90 degrees from outside circle to inner circle
	int ulRow = 0, drRow = nRows - 1;
	while (ulRow < drRow) {
		for (int i = ulRow; i < drRow; ++i) {
			//(ulRow, i) -> (i, nRows - 1 - ulRow) -> (nRows - 1 - ulRow, nRows - 1 - i) -> (nRows - 1 - i, ulRow) -> (ulRow, i)
			int temp = pArr[i * nRows + nRows - 1 - ulRow];
			pArr[i * nRows + nRows - 1 - ulRow] = pArr[ulRow * nRows + i];
			pArr[ulRow * nRows + i] = pArr[(nRows - 1 - i) * nRows + ulRow];
			pArr[(nRows - 1 - i) * nRows + ulRow] = pArr[(nRows - 1 - ulRow) * nRows + nRows - 1 - i];
			pArr[(nRows - 1 - ulRow) * nRows + nRows - 1 - i] = temp;
		}
		++ulRow;
		--drRow;
	}
	cout << endl;
	return;
}

int main(int argc, char* argv[]) {
	cout << "turn square matrix 90 degrees clockwise: " << endl;
	int nRows = 4;
	int *pArr = new int [nRows * nRows];
	for (int i = 0; i < nRows * nRows; ++i) {
		pArr[i] = i + 1;
	}
	turn90Clockwise(pArr, nRows);
	for (int i = 0; i < nRows * nRows; ++i) {
		cout << pArr[i] << ", ";
	}
	cout << endl;
	delete [] pArr;
    return 0;
}




