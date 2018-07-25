/*
 * test197.cpp
 *
 *  Created on: May 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

/*
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
determine if s can be segmented into a space-separated sequence of one or more dictionary words.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int len = wordDict.size();
        if (len == 0) {
            return false;
        }
        unordered_set<string> wordSet;
        int i;
        for (i = 0; i < len; ++i) {
            wordSet.insert(wordDict[i]);
        }
        //dynamic programming
        //@posInS[i] means the position that can be segmented by a word
        vector<int> posInS;
        bool found = false;
        for (i = 0; i < s.length(); ++i) {
            found = false;
            //for all position j in @posInS, check if [j+1...i] is a word
            for (int j = 0; j < posInS.size(); ++j) {
                if (wordSet.find(s.substr(posInS[j] + 1, i - posInS[j])) != wordSet.end()) {
                    posInS.push_back(i);
                    found = true;
                    break;
                }
            }
            //always check the sub string from [0...i]
            if (!found && wordSet.find(s.substr(0, i + 1)) != wordSet.end()) {
                posInS.push_back(i);
                found = true;
            }
        }
        return found;
    }
};
