/*
 * test95.cpp
 *
 *  Created on: Jan 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//given an array @nums, nums[i] is the point of a balloon at position i.
//if balloon i is blown out, one can get the point of nums[left] * nums[i] * nums[right], "left" is the balloon on the left, "right" is the balloon on the right
//when balloon i is blown out, the left balloon and right balloon become neighbor.
//write a function to find the maximum points one can get after blow out all balloons
//for example:  nums=[4, 1, 5, 10], output=270
int maxNumber(const vector<int>& nums) {
	size_t len = nums.size();
	if (len == 0) {
		return 0;
	}
	//use dynamic programming.
	//@pointMap is a map from @sig to point of the set
	unordered_map<string, int> pointMap1, pointMap2;
	//for @sig that no balloon is left, the point is 0
	pointMap1.emplace(string(len, '0'), 0);
	int points, left, right;
	string sig;
	for (size_t i = 1; i <= len; ++i) {
		for (auto it1 = pointMap1.begin(); it1 != pointMap1.end(); ++it1) {
			//for each previous balloon set of size (i - 1)
			left = right = -1;
			for (size_t j = 0; j < len; ++j) {
				if (it1->first.at(j) == '0') {
					if (right == -1 || j > right) {
						size_t k;
						for (k = j + 1; k < len; ++k) {
							if (it1->first.at(k) == '1') {
								break;
							}
						}
						right = k;
					}
					points = nums[j];
					if (left != -1) {
						points *= nums[left];
					}
					if (right < len) {
						points *= nums[right];
					}
					points += it1->second;
					sig = it1->first;
					sig.replace(j, 1, 1, '1');
					auto it2 = pointMap2.find(sig);
					if (it2 != pointMap2.end() && it2->second < points) {
						it2->second = points;
					} else {
						pointMap2.emplace(move(sig), points);
					}
				} else {
					left = j;
				}
			}
		}
		pointMap1.swap(pointMap2);
		pointMap2.clear();
	}
	auto it3 = pointMap1.find(string(len, '1'));
	if (it3 != pointMap1.end()) {
		points = it3->second;
	} else {
		points = -1;
	}
	return points;
}

int main(int argc, char* argv[]) {
	cout << "maximum points: " << maxNumber({4, 1, 5, 10}) << endl;
    return 0;
}




