/*
 * test203.cpp
 *
 *  Created on: May 24, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

Example 1:

Input: numerator = 1, denominator = 2
Output: "0.5"
Example 2:

Input: numerator = 2, denominator = 1
Output: "2"
Example 3:

Input: numerator = 2, denominator = 3
Output: "0.(6)"
*/

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        int64_t n = numerator, d = denominator;
        //check some corner cases
        if (d == 0) {
            return "NAN";
        }
        if (d == 1) {
            return std::to_string(n);
        }
        if (d == -1) {
            return std::to_string(-n);
        }
        if (n == 0) {
            return "0";
        }
        if (n == d) {
            return "1";
        }
        if (n == -d) {
            return "-1";
        }

        //for normal cases
        string ret;
        if ((n > 0 && d < 0) || (n < 0 && d > 0)) {
            ret = "-";
        }
        n = std::abs(n), d = std::abs(d);
        unordered_map<int, int> rToPosMap;
        if (n > d) {
            ret += std::to_string(n / d);
            n = n % d;
        } else {
            ret += "0";
        }
        if (n == 0) {
            return ret;
        }
        ret += ".";
        while (n != 0) {
            auto it = rToPosMap.find(n);
            if (it == rToPosMap.end()) {
                rToPosMap.emplace(n, ret.length());
                n = n * 10;
                ret.append(1, n / d + '0');
                n = n % d;
            } else {
                //insert '(' before it->second
                ret.insert(it->second, 1, '(');
                ret.append(1, ')');
                return ret;
            }
        }
        return ret;
    }
};
