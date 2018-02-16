/*
 * test93.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//given an positive integer N
//find the sum of all elements in all subsets of N
//for example: N=2, output 6 ({1}, {2}, {1, 2} are all subsets)
//for example: N=3, output 24 ({1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3} are all subsets)
size_t subSetSum(size_t N) {
    //use dynamic programming
    size_t preSum = 0;
    size_t nPreSubsets = 0;
    for (size_t i = 1; i <= N; ++i) {
    		//there is new subset that only contains this integer
    		//for all other subset, there is corresponding subset that this integer is in (or not, which is the old subset)
    		preSum = i + preSum * 2 + i * nPreSubsets;
    		nPreSubsets = nPreSubsets * 2 + 1;
    }
    return preSum;
}

int main(int argc, char* argv[]) {
	for (size_t i = 0; i < 10; ++i) {
		cout << "totals for " << i << ": " << subSetSum(i) << endl;
	}
    return 0;
}




