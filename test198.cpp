/*
 * test198.cpp
 *
 *  Created on: May 16, 2018
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
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
add spaces in s to construct a sentence where each word is a valid dictionary word.
Return all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
*/

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int len = wordDict.size();
        if (len == 0) {
            return {};
        }
        //add words into set
        unordered_set<string> wordSet;
        int i;
        for (i = 0; i < len; ++i) {
            wordSet.insert(wordDict[i]);
        }
        //@posInS stores all the position so far that it is a word in @wordSet
        vector<int> posInS(s.length(), 0);
        vector<string> ret;
        i = 0;
        int size = 0;
        while(1) {
            if (size == 0 && i == s.length()) {
                break;
            } else if (size > 0 && posInS[size - 1] == s.length() - 1) {
                //solution
            		cout << "here1" << endl;
                string str(s.substr(0, posInS[0] + 1));
                for (int j = 1; j < size; ++j) {
                    str += " ";
                    str += s.substr(posInS[j - 1] + 1, posInS[j] - posInS[j - 1]);
                }
                ret.push_back(str);
                --size;
                if (size > 0) {
                		--size;
                    i = posInS[size] + 1;
                } else {
                    i = s.length();
                }
            } else if (i == s.length()) {
                //not found
                --size;
                i = posInS[size] + 1;
            } else {
                //check either [0...i] or [posInS[posInS.size()-1]+1...i] is a word
                if (size == 0) {
                    if (wordSet.find(s.substr(0, i + 1)) != wordSet.end()) {
                        posInS[size] = i;
                        cout << size << ", " << i << endl;
                        ++size;
                        ++i;
                    } else {
                        ++i;
                    }
                } else {
                    if (wordSet.find(s.substr(posInS[size - 1] + 1, i - posInS[size - 1])) != wordSet.end()) {
                        posInS[size] = i;
                        cout << size << ", " << i << endl;
                        ++size;
                        ++i;
                    } else {
                        ++i;
                    }
                }
            }
        }
        return ret;
    }
};

class Solution1 {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int len = wordDict.size();
        if (len == 0) {
            return {};
        }
        unordered_set<string> wordSet;
        int i;
        for (i = 0; i < len; ++i) {
            wordSet.insert(wordDict[i]);
        }
        stack<int> posInS;
        vector<string> ret;
        //@pos stores the words starting from the end of @s
        vector<int> pos;
        vector<int> up;
        string str;
        //use depth first traverse
        i = 0;
        int last;
        //check the last word start pos and push into stack
        int slength = s.length();
        for (i = slength - 1; i >= 0; --i) {
            if (wordSet.find(s.substr(i, string::npos)) != wordSet.end()) {
                posInS.push(i);
                posInS.push(slength);
            }
        }
        while (!posInS.empty()) {
        		last = posInS.top();
        		posInS.pop();
            i = posInS.top();
            posInS.pop();
            pos.push_back(i);
            up.push_back(last);
            if (i == 0) {
                //found one solution
                str = s.substr(pos[0], string::npos);
                for (int j = 1; j < pos.size(); ++j) {
                    str.insert(0, " ");
                    str.insert(0, s.substr(pos[j], pos[j - 1] - pos[j]));
                }
                ret.push_back(str);
                if (!posInS.empty()) {
                		while (posInS.top() != up.back()) {
                			up.pop_back();
                			pos.pop_back();
                		}
                		up.pop_back();
                		pos.pop_back();
                }
            } else {
                bool found = false;
                for (int j = i - 1; j >= 0; --j) {
                    if (wordSet.find(s.substr(j, i - j)) != wordSet.end()) {
                        found = true;
                        posInS.push(j);
                        posInS.push(i);
                    }
                }
                if (!found) {
                    //no word after i
                		if (!posInS.empty()) {
                			while (posInS.top() != up.back()) {
                				up.pop_back();
                				pos.pop_back();
                			}
                			up.pop_back();
                			pos.pop_back();
                		}
                }
            }
        }
        return ret;
    }
};

int main (int argc, char *argv[]) {
	string s("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	//string s("aaaaaaaaaaaaaaaaaaabaaaaa");
	//string s("aaaaaaaa");
	vector<string> d({"a", "aa","aaa","aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"}), ret;
	Solution1 sol;
	ret = sol.wordBreak(s, d);
	for (auto i : ret) {
		cout << i << endl;
	}
	return 0;
}
