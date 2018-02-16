/*
 * test94.cpp
 *
 *  Created on: Jan 11, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <deque>

using namespace std;

//given two arrays of length m and n to represent 2 large numbers
//for example: {3, 4, 6, 5} and {9, 1, 2, 5, 8, 3} means 3465 and 912583
//given another integer K, 1 <= K <= (m + n)
//select K numbers from the two arrays to create an integer of length K that has the maximum value
//restriction: if two numbers are from the same array, they must keep the same order
//return this value in terms of K length array
int findMaximumArrayofLengthK(const vector<int>& num1, const vector<int>& num2, int K, vector<int>& maxNum) {
	size_t len1 = num1.size(), len2 = num2.size();
	if (K < 1 || K > len1 + len2) {
		return -1;
	}
	//next number could be chosen in range [start1, end1] or [start2, end2]
	int start1 = 0, start2 = 0, end1, end2, lastEnd1 = start1 - 1, lastEnd2 = start2 - 1;
	deque<int> queue1, queue2;
	for (int i = K; i > 0; --i) {
		//find @end1, @end2
		end1 = (i - 1 <= len2 - start2) ? len1 - 1 : (len1 - (i - (len2 - start2)));
		end2 = (i - 1 <= len1 - start1) ? len2 - 1 : (len2 - (i - (len1 - start1)));
		//clean queue1 and queue2
		while (!queue1.empty() && queue1.front() < start1) {
			queue1.pop_front();
		}
		while (!queue2.empty() && queue2.front() < start2) {
			queue2.pop_front();
		}
		//find max number in the range [start1 end1] [start2 end2] in num1 and num2
		for (int j = lastEnd1 + 1; j <= end1; ++j) {
			while (!queue1.empty() && num1[queue1.back()] < num1[j]) {
				queue1.pop_back();
			}
			queue1.push_back(j);
		}
		for (int j = lastEnd2 + 1; j <= end2; ++j) {
			while (!queue2.empty() && num2[queue2.back()] < num2[j]) {
				queue2.pop_back();
			}
			queue2.push_back(j);
		}
		lastEnd1 = end1;
		lastEnd2 = end2;
		//queue1.front() and queue2.front() is the maximum in range [start1 end1] [start2 end2]
		if (!queue1.empty() && !queue2.empty()) {
			if (num1[queue1.front()] > num2[queue2.front()]) {
				maxNum.push_back(num1[queue1.front()]);
				start1 = queue1.front() + 1;
			} else {
				maxNum.push_back(num2[queue2.front()]);
				start2 = queue2.front() + 1;
			}
		} else if (!queue1.empty()) {
			maxNum.push_back(num1[queue1.front()]);
			start1 = queue1.front() + 1;
		} else {
			maxNum.push_back(num2[queue2.front()]);
			start2 = queue2.front() + 1;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	vector<int> maxNum;
	findMaximumArrayofLengthK({3, 4, 6, 5}, {9, 1, 2, 5, 8, 3}, 5, maxNum);
	for (auto& it : maxNum) {
		cout << it << ", ";
	}
	cout << endl;
    return 0;
}




