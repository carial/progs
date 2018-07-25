/*
 * test175.cpp
 *
 *  Created on: May 2, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

//Given a string source and a string target,
//find the minimum window in source which will contain all the characters in target.
//Notice
//If there is no such window in source that covers all characters in target, return the emtpy string "".
//If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in source.
//Clarification
//Should the characters in minimum window has the same order in target?
//Not necessary.
//Example
//For source = "ADOBECODEBANC", target = "ABC", the minimum window is "BANC"

class Solution {
public:
    /**
     * @param source : A string
     * @param target: A string
     * @return: A string denote the minimum window, return "" if there is no such a string
     */
    string minWindow(string &source , string &target) {
        // write your code here
        int len1 = source.length(), len2 = target.length();
        if (len1 == 0) {
            //source is empty
            return "";
        }
        if (len2 == 0) {
            //target is empty
            return "";
        }
        if (len1 < len2) {
            return "";
        }
        unordered_map<char, int> freq;
        int i, j, total = 0, cur = 0;
        for (i = 0; i < len2; ++i) {
            char ch = target.at(i);
           auto it1 = freq.find(ch);
           if (it1 == freq.end()) {
               freq.emplace(ch, 1);
           } else {
               ++it1->second;
           }
           ++total;
        }
        i = 0;
        j = 1;
        int start = -1, end = -1;
        char ch2 = source.at(i);
        auto it2 = freq.find(ch2);
        if (it2 != freq.end()) {
            --it2->second;
            ++cur;
        }
        //current sub string is [i...(j-1)], j points to next position
        while (j < len1 || (cur == total && i < len1)) {
            //check if current sub string contains target
            if (cur < total) {
                //check next position
                char ch3 = source.at(j);
                ++j;
                auto it3 = freq.find(ch3);
                if (it3 != freq.end()) {
                    //update statistics
                    if (it3->second > 0) {
                        ++cur;
                    }
                    --it3->second;
                }
            } else {
                //find one solution
                if (start == -1 || (end - start + 1 > j - i)) {
                    start = i;
                    end = j - 1;
                }
                //move @i to next character
                it2 = freq.find(source.at(i));
                if (it2 != freq.end()) {
                    if (it2->second >= 0) {
                        --cur;
                    }
                    ++it2->second;
                }
                ++i;
            }
        }
        if (start != -1) {
            return source.substr(start, end - start + 1);
        } else {
            return "";
        }
    }
};
