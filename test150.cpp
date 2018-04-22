/*
 * test150.cpp
 *
 *  Created on: April 12, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
using namespace std;

//Design a function to find the size of longest palindrome in a string
//requirement:
//the time complexity is O(N), N is the size of the string
//for example: str = "123", the siz of longest palindrome is 1
//str = "abc1234321ab", the size of longest palindrome is 7
int longestPalindrome(const string& str) {
	int len = str.size();
	if (len == 0 || len == 1) {
		return len;
	}
	int maxLen = 1;
	struct _Node {
	public:
		char m_val;
		vector<int> m_pos;
		int m_next;
		_Node(char val, int pos) : m_val(val), m_next(1) {
			m_pos.push_back(pos);
		}
		~_Node() {};
		void addPos(int pos) {
			m_pos.push_back(pos);
		}
	};
	unordered_map<char, _Node*> charToNodeMap;
	//collect statistics
	for (int i = 0; i < len; ++i) {
		char ch = str.at(i);
		auto it = charToNodeMap.find(ch);
		if (it == charToNodeMap.end()) {
			_Node *p = new _Node(ch, i);
			charToNodeMap.emplace(ch, p);
		} else {
			it->second->addPos(i);
		}
	}
	for (int i = 0; i < len; ++i) {
		//scan whole string
		char ch = str.at(i);
		auto it = charToNodeMap.find(ch);
		_Node *p = it->second;
		for (int j = p->m_next; j < p->m_pos.size(); ++j) {
			int start = i + 1, end = p->m_pos[j] - 1;
			for (; start <= end; ++start, --end) {
				if (str.at(start) != str.at(end)) {
					break;
				}
			}
			if (start > end && maxLen < p->m_pos[j] - i + 1) {
				maxLen = p->m_pos[j] - i + 1;
			}
		}
		++p->m_next;
	}
	//clean up
	for (auto item : charToNodeMap) {
		delete item.second;
	}
	return maxLen;
}

//an example
int main(int argc, char* argv[]) {
	cout << "size of longest palindrome: " << longestPalindrome("abc1234321ab") << endl;
	return 0;
}




