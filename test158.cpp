/*
 * test158.cpp
 *
 *  Created on: April 25, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
using namespace std;

//Given a string and an offset, rotate string by offset. (rotate from left to right)
//Examples:
//Given "abcdefg"
//offset=0 => "abcdefg"
//offset=1 => "gabcdef"
//offset=2 => "fgabcde"
//offset=3 => "efgabcd"
class Solution {
public:
    /**
     * @param str: An array of char
     * @param offset: An integer
     * @return: nothing
     */
    void rotateString(string &str, int offset) {
        // write your code here
        if (offset < 0) {
            return;
        }
        int len = str.length();
        if (len == 0) {
            return;
        }
        int offset1 = offset % len;
        if (offset1 == 0) {
            return;
        }
        int numExChanges = 0, start = 0, next, nextnext;
        char temp;
        while (numExChanges < len) {
            next = (start + offset1) % len;
            temp = str.at(start);
            while (next != start) {
                //switch temp and str.at(next)
                char temp2 = temp;
                temp = str.at(next);
                str.at(next) = temp2;
                ++numExChanges;
                next = (next + offset1) % len;
            }
            //put temp into str.at(start)
            str.at(start) = temp;
            ++numExChanges;
            ++start;
        }
        return;
    }
};
