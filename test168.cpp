/*
 * test168.cpp
 *
 *  Created on: April 30, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//Throw n dices, the sum of the dices' faces is S.
//Given n, find the all possible value of S along with its probability.
//Example:
//Given n = 1, return [ [1, 0.17], [2, 0.17], [3, 0.17], [4, 0.17], [5, 0.17], [6, 0.17]].

class Solution {
public:
    /**
     * @param n an integer
     * @return a list of pair<sum, probability>
     */
    vector<pair<int, double>> dicesSum(int n) {
        // Write your code here
        if (n <= 0) {
            return {};
        }
        //@prob[0|1][i] is the probability of number i
        vector<vector<double>> prob(2, vector<double>(6 * n, 0));
        vector<vector<double>>::size_type cur = 0;
        vector<double>::size_type j;
        for (j = 0; j < 6; ++j) {
            prob[cur][j] = (double)1 / 6;
        }
        int end1, start2 = -1, end2 = -1;
        for (int i = 1; i < n; ++i) {
            //dynamic programming
            cur = 1 - cur;
            //current number range (index) is [i...(i*6+5)]
            end1 = (i + 1) * 6, start2 = i - 1, end2 = i * 6 - 1;
            prob[cur] = std::move(vector<double>(6 * n, 0));
            for (int j = i; j < end1; ++j) {
                //j can be (j-1)+1, (j-2)+2, (j-3)+3...(j-6)+6
                //last number range (index) is [(i-1)...(i*6-1)]
                for (int k = j - 6; k < j; ++k) {
                    if (k >= start2 && k <= end2) {
                        prob[cur][j] += prob[1 - cur][k] / 6;
                    }
                }
            }
        }
        //output
        ++start2;
        end2 += 6;
        vector<pair<int, double>> ret(end2 - start2 + 1);
        for (int i = 0; i < ret.size(); ++i) {
            ret[i] = std::make_pair(start2 + i + 1, prob[cur][start2 + i]);
        }
        return ret;
    }
};
