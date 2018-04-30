/*
 * test154.cpp
 *
 *  Created on: April 22, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <queue>
#include <cstdint>
#include <unordered_map>
using namespace std;

//Ugly number is a number that only have factors 2, 3 and 5.
//Design an algorithm to find the nth ugly number. The first 10 ugly numbers are 1, 2, 3, 4, 5, 6, 8, 9, 10, 12...
//Example:
//If n=9, return 10
class Solution {
public:
    /**
     * @param n: An integer
     * @return: the nth prime number as description.
     */
    int nthUglyNumber(int n) {
        // write your code here
        //build 3 priority queues with multiplying 2, 3 or 5
        if (n == 1) {
            return 1;
        }
        //more than 1
        std::queue<int> queue2, queue3, queue5;
        queue2.push(2);
        queue3.push(3);
        queue5.push(5);
        int ret;
        for (int i = 1; i < n; ++i) {
            int num2 = queue2.front(), num3 = queue3.front(), num5 = queue5.front();
            ret = num2;
            if (ret > num3) {
                ret = num3;
            }
            if (ret > num5) {
                ret = num5;
            }
            if (ret == num2) {
                queue2.pop();
            }
            if (ret == num3) {
                queue3.pop();
            }
            if (ret == num5) {
                queue5.pop();
            }
            //insert into 3 queues
            queue2.push(ret * 2);
            queue3.push(ret * 3);
            queue5.push(ret * 5);
        }
        return ret;
    }
};

