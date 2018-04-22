/*
 * test153.cpp
 *
 *  Created on: April 22, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
using namespace std;

//Count the number of k's between 0 and n. k can be 0 - 9.
//Example: if k = 1, n = 12. There are 5 "1"s in [0,1,2,3,...10,11,12]
class Solution {
public:
    /*
     * @param : An integer
     * @param : An integer
     * @return: An integer denote the count of digit k in 1..n
     */
    int digitCounts(int k, int n) {
        // write your code here
        if (n < 0) {
            return -1;
        }
        if (n == 0) {
            if (k == 0) {
                return 1;
            } else {
                return 0;
            }
        }
        //n > 0
        //find how many digits the integer has
        int totalDigits = 0, numK = 0;
        for (int i = n; i; i /= 10, ++totalDigits);
        int leftNum = n / 10, num = n, rightNum = 0;
        for (int i = 0, j = 1; i < totalDigits; ++i, leftNum /= 10, num /= 10, j *= 10) {
            //for each digits (from LSB to MSB)
            //@leftNum is the left part [(totalDigits-1)...(i+1)]
            //the number of right digits is i
            //@digit is the ith digit
            int digit = num % 10;

            if (digit > k) {
                numK += ((k == 0 && i > 0) ? leftNum : (leftNum + 1)) * j;
            } else if (digit < k) {
                numK += leftNum * j;
            } else { //digit == k
                //if k == 0, [1,2,...,(leftNum-1)] 0 ...; (leftNum) 0 ...
                //if k != 0, [0,1,2,...(leftNum-1)] k ...; (leftNum) k ...
                numK += (k == 0 ? (leftNum > 0 ? leftNum - 1 : 0) : leftNum) * j;
                numK += rightNum + 1;
            }
            rightNum += digit * j;
        }
        return numK;
    }
};




