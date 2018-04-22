/*
 * test122.cpp
 *
 *  Created on: Feb 24, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// given an array of size MxN containing only 0 and 1 to represent a network. 0 means nodes are not connected, 1 means nodes are connected
// find the minimum length of the route from upperleft node to downright node
// for example:
// 1 0 1 1 1
// 1 0 1 0 1
// 1 1 1 0 1
// 0 0 0 0 1
// the minimum route from upperleft to downright is 12
void updateNeighbor(const vector<vector<int>>& arr, vector<vector<int>>& length, int nCurRow, int nCurCol, int nNeiRow, int nNeiCol, queue<pair<int, int>>& nextNodes) {
	if ((nNeiRow >= 0) && (nNeiRow < arr.size()) && (nNeiCol >= 0) && (nNeiCol < arr[0].size()) &&
			arr[nNeiRow][nNeiCol] && (length[nNeiRow][nNeiCol] == -1 || length[nNeiRow][nNeiCol] > length[nCurRow][nCurCol] + 1)) {
		length[nNeiRow][nNeiCol] = length[nCurRow][nCurCol] + 1;
		nextNodes.emplace(nNeiRow, nNeiCol);
	}
	return;
}

int minLengthOfRoute(const vector<vector<int>>& arr) {
	//assume arr is not empty, and a rectangular matrix
	int nCols = arr[0].size(), nRows = arr.size();
	//saves the next nodes to visit
	queue<pair<int,int>> nextNodes;
	vector<vector<int>> length(nRows, vector<int>(nCols, -1));
	nextNodes.emplace(0, 0); //push upperleft node
	length[0][0] = 1;
	while (!nextNodes.empty()) {
		pair<int, int> pos = nextNodes.front();
		nextNodes.pop();
		if (arr[pos.first][pos.second]) {
			//connected, check 4 neighbors
			updateNeighbor(arr, length, pos.first, pos.second, pos.first - 1, pos.second, nextNodes);
			updateNeighbor(arr, length, pos.first, pos.second, pos.first + 1, pos.second, nextNodes);
			updateNeighbor(arr, length, pos.first, pos.second, pos.first, pos.second - 1, nextNodes);
			updateNeighbor(arr, length, pos.first, pos.second, pos.first, pos.second + 1, nextNodes);
		}
	}
	return length[nRows - 1][nCols - 1];
}

int main(int argc, char* argv[]) {
	cout << "min length of route: " << minLengthOfRoute({{1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1}}) << endl;
}




