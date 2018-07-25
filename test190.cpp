/*
 * test190.cpp
 *
 *  Created on: May 10, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
Implement pow(x, n), which calculates x raised to the power n (x^n).

Example 1:

Input: 2.00000, 10
Output: 1024.00000
Example 2:

Input: 2.10000, 3
Output: 9.26100
Example 3:

Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25
Note:

-100.0 < x < 100.0
n is a 32-bit signed integer, within the range [−231, 231 − 1]
*/

class Solution {
public:
    double myPow(double x, int n) {
        if (x == 0.0 && n <= 0) {
            return -1;
        }
        if (x == 0.0) {
            return 0.0;
        }
        double res = 1;
        int remain = 0, absn;
        if (n != INT32_MIN) {
            absn = n >= 0 ? n : -n;
        } else {
            remain = 1;
            absn = INT32_MAX;
        }
        vector<double> res1(32, 1);
        res1[1] = x;
        if (absn & 1) {
            res = x;
        }
        for (int i = 1; i < 31; ++i) {
            res1[i + 1] = res1[i] * res1[i];
            if (absn & (0x1 << i)) {
                res *= res1[i + 1];
            }
        }
        if (remain) {
            res *= x;
        }
        if (n < 0) {
            return 1 / res;
        } else {
            return res;
        }
    }
};

int main(int argc, char *argv[]) {
	Solution sol;
	double ret = sol.myPow(-13.62, 3);
	cout << ret << endl;
	return 0;
}
