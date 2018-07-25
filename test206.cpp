/*
 * test206.cpp
 *
 *  Created on: May 28, 2018
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
Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.
*/

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {

    }

    ~Trie() {
        for (auto it : m_head) {
            deleteNode(it.second);
        }
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        int len = word.length();
        char ch;
        if (len == 0) {
            return;
        } else {
            unordered_map<char, _Node*> *m = &m_head;
            int i;
            for (i = 0; i < len; ++i) {
                ch = word.at(i);
                unordered_map<char, _Node*>::iterator it = m->find(ch);
                if (it == m->end()) {
                    break;
                } else {
                    m = &(it->second->m_next);
                    if (i == len - 1) {
                        it->second->m_isWord = true;
                    }
                }
            }
            for (; i < len; ++i) {
                //insert characters into trie
                _Node *p = new _Node(word.at(i), (i == len - 1));
                m->emplace(word.at(i), p);
                m = &(p->m_next);
            }
        }
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        int len = word.length();
        if (len == 0) {
            return false;
        } else {
            unordered_map<char, _Node*> *m = &m_head;
            int i;
            for (i = 0; i < len; ++i) {
                unordered_map<char, _Node*>::iterator it = m->find(word.at(i));
                if (it == m->end()) {
                    return false;
                } else {
                    m = &(it->second->m_next);
                }
                if (i == len - 1) {
                    return it->second->m_isWord;
                }
            }
        }
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        int len = prefix.length();
        if (len == 0) {
            return false;
        } else {
            unordered_map<char, _Node*> *m = &m_head;
            int i;
            for (i = 0; i < len; ++i) {
                unordered_map<char, _Node*>::iterator it = m->find(prefix.at(i));
                if (it == m->end()) {
                    return false;
                } else {
                    m = &(it->second->m_next);
                }
            }
            return true;
        }
    }
    private:
    struct _Node{
        public:
        char m_val;
        bool m_isWord;
        unordered_map<char, _Node*> m_next;
        _Node(char val, bool isWord) : m_val(val), m_isWord(isWord) {};
    };
    unordered_map<char, _Node*> m_head;
    void deleteNode(_Node *n) {
        if (!n) {
            return;
        } else {
            for (auto it : n->m_next) {
                deleteNode(it.second);
            }
            delete n;
        }
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */
