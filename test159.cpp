/*
 * test159.cpp
 *
 *  Created on: April 25, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
using namespace std;

//Given number n. Print number from 1 to n. But:
//when number is divided by 3, print "fizz".
//when number is divided by 5, print "buzz".
//when number is divided by both 3 and 5, print "fizz buzz".
//Restriction:
//only use one "if" condition

class Solution {
public:
    /**
     * @param n: An integer
     * @return: A list of strings.
     */
    vector<string> fizzBuzz(int n) {
        // write your code here
        if (n <= 0) {
            return {};
        }
        vector<string> ret;
        vector<string> pattern({"fizz buzz", "buzz", "buzz", "fizz", "", "", "fizz", "", "", "fizz", "", "", "fizz", "", ""});
        for (int i = 1; i <= n; ++i) {
            int j = i % 3, k = (i % 5) * 3;
            if (pattern[j + k] == "") {
                ret.push_back(std::to_string(i));
            } else {
                ret.push_back(pattern[j + k]);
            }
        }
        return ret;
    }
};
