/*
 * test207.cpp
 *
 *  Created on: May 29, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
using namespace std;

/*
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell,
where "adjacent" cells are those horizontally or vertically neighboring.
The same letter cell may not be used more than once in a word.

Example:

Input:
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

Output: ["eat","oath"]
Note:
You may assume that all inputs are consist of lowercase letters a-z.
*/

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        int rows = board.size();
        if (rows == 0) {
            return {};
        }
        int columns = board[0].size();
        if (columns == 0) {
            return {};
        }
        int len = words.size();
        if (len == 0) {
            return {};
        }

        //build dictionary tree for words
        _Node *head = new _Node(0, false);
        int i;
        for (i = 0; i < len; ++i) {
            insertToDictionary(head, words[i]);
        }
        vector<string> ret;
        string res;
        unordered_set<int> visitedPos;
        stack<int> nextPos;
        stack<_Node*> nextNode;
        unordered_set<string> foundString;
        //search @board for words
        int j, pos;
        _Node *cur, *next;
        for (i = 0; i < rows; ++i) {
            for (j = 0; j < columns; ++j) {
                cur = head;
                pos = i * columns + j;
                next = isPrefix(cur, board[i][j]);
                if (next != nullptr) {
                    nextPos.push(pos);
                    nextNode.push(next);
                    while (!nextPos.empty()) {
                        pos = nextPos.top();
                        nextPos.pop();
                        if (pos == -1) {
                            //deliminater. all its children has been explored
                            pos = nextPos.top();
                            nextPos.pop();
                            res.erase(res.length() - 1, 1);
                            visitedPos.erase(pos);
                            continue;
                        }
                        int k = pos / columns, l = pos % columns;
                        cur = nextNode.top();
                        nextNode.pop();
                        res.append(1, board[k][l]);
                        visitedPos.insert(pos);
                        //check if it is a word
                        if (cur->m_isWord) {
                            foundString.insert(res);
                        }
                        nextPos.push(pos);
                        nextPos.push(-1);
                        //continue to search its neighbors
                        if (k > 0 && visitedPos.find(pos - columns) == visitedPos.end()) {
                            next = isPrefix(cur, board[k - 1][l]);
                            if (next != nullptr) {
                                nextPos.push(pos - columns);
                                nextNode.push(next);
                            }
                        }
                        if (k < rows - 1 && visitedPos.find(pos + columns) == visitedPos.end()) {
                            next = isPrefix(cur, board[k + 1][l]);
                            if (next != nullptr) {
                                nextPos.push(pos + columns);
                                nextNode.push(next);
                            }
                        }
                        if (l > 0 && visitedPos.find(pos - 1) == visitedPos.end()) {
                            next = isPrefix(cur, board[k][l - 1]);
                            if (next != nullptr) {
                                nextPos.push(pos - 1);
                                nextNode.push(next);
                            }
                        }
                        if (l < columns - 1 && visitedPos.find(pos + 1) == visitedPos.end()) {
                            next = isPrefix(cur, board[k][l + 1]);
                            if (next != nullptr) {
                                nextPos.push(pos + 1);
                                nextNode.push(next);
                            }
                        }
                    }
                }
            }
        }
        for (auto i : foundString) {
            ret.push_back(i);
        }
        deleteNode(head);
        return ret;
    }

    private:
    struct _Node{
        public:
        char m_ch;
        bool m_isWord;
        unordered_map<char, _Node*> m_next;
        _Node(char ch, bool isWord) : m_ch(ch), m_isWord(isWord) {}
    };
    void insertToDictionary(_Node* head, const string& w) {
        int len = w.length();
        if (len == 0) {
            return;
        }
        _Node *h = head;
        int i;
        for (i = 0; i < len; ++i) {
            char ch = w.at(i);
            auto it = h->m_next.find(ch);
            if (it == h->m_next.end()) {
                h->m_next.emplace(ch, new _Node(ch, i == (len - 1)));
            } else if (i == len - 1) {
                it->second->m_isWord = true;
            }
            h = h->m_next[ch];
        }
    }
    _Node* isPrefix(_Node* h, char ch) {
        //check if @ch is a prefix
        auto it = h->m_next.find(ch);
        if (it == h->m_next.end()) {
            return nullptr;
        } else {
            return it->second;
        }
    }
    void deleteNode(_Node* p) {
        if (!p) {
            return;
        }
        for (auto i : p->m_next) {
            deleteNode(i.second);
        }
        delete p;
    }
};

int main(int argc, char *argv[]) {
	vector<vector<char>> b({{'b','a','a','b','a','b'},
		{'a','b','a','a','a','a'},
		{'a','b','a','a','a','b'},
		{'a','b','a','b','b','a'},
		{'a','a','b','b','a','b'},
		{'a','a','b','b','b','a'},
		{'a','a','b','a','a','b'}});
	vector<string> w({"bbaabaabaaaaabaababaaaaababb",
		"aabbaaabaaabaabaaaaaabbaaaba",
		"babaababbbbbbbaabaababaabaaa",
		"bbbaaabaabbaaababababbbbbaaa",
		"babbabbbbaabbabaaaaaabbbaaab",
		"bbbababbbbbbbababbabbbbbabaa",
		"babababbababaabbbbabbbbabbba",
		"abbbbbbaabaaabaaababaabbabba",
		"aabaabababbbbbbababbbababbaa",
		"aabbbbabbaababaaaabababbaaba",
		"ababaababaaabbabbaabbaabbaba",
		"abaabbbaaaaababbbaaaaabbbaab",
		"aabbabaabaabbabababaaabbbaab",
		"baaabaaaabbabaaabaabababaaaa",
		"aaabbabaaaababbabbaabbaabbaa",
		"aaabaaaaabaabbabaabbbbaabaaa",
		"abbaabbaaaabbaababababbaabbb",
		"baabaababbbbaaaabaaabbababbb",
		"aabaababbaababbaaabaabababab",
		"abbaaabbaabaabaabbbbaabbbbbb",
		"aaababaabbaaabbbaaabbabbabab",
		"bbababbbabbbbabbbbabbbbbabaa",
		"abbbaabbbaaababbbababbababba",
		"bbbbbbbabbbababbabaabababaab",
		"aaaababaabbbbabaaaaabaaaaabb",
		"bbaaabbbbabbaaabbaabbabbaaba",
		"aabaabbbbaabaabbabaabababaaa",
		"abbababbbaababaabbababababbb",
		"aabbbabbaaaababbbbabbababbbb",
		"babbbaabababbbbbbbbbaabbabaa"});
	/*
	vector<string> w({"aabbbbabbaababaaaabababbaaba", "abaabbbaaaaababbbaaaaabbbaab", "ababaababaaabbabbaabbaabbaba"});
	*/
	vector<string> r;
	Solution s;
	r = s.findWords(b, w);
	for (auto i : r) {
		cout << i << endl;
	}
	return 0;
}
