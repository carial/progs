/*
 * test200.cpp
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
The API: int read4(char *buf) reads 4 characters at a time from a file.

The return value is the actual number of characters read. For example, it returns 3 if there is only 3 characters left in the file.

By using the read4 API, implement the function int read(char *buf, int n) that reads n characters from the file.

Note:
The read function may be called multiple times.

Example 1:

Given buf = "abc"
read("abc", 1) // returns "a"
read("abc", 2); // returns "bc"
read("abc", 1); // returns ""
Example 2:

Given buf = "abc"
read("abc", 4) // returns "abc"
read("abc", 1); // returns ""
*/

// Forward declaration of the read4 API.
int read4(char *buf);

class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Maximum number of characters to read
     * @return    The number of characters read
     */
    int read(char *buf, int n) {
        auto it1 = m_bufToNodeptr.find(buf);
        Node *p;
        if (it1 != m_bufToNodeptr.end()) {
            p = it1->second;
        } else {
            //new buffer
            p = new Node();
            m_bufToNodeptr.emplace(buf, p);
        }
        int nRead = 0;
        while (1) {
            while (p->m_pos < p->m_size && nRead < n) {
                buf[nRead] = p->m_cache[p->m_pos];
                ++p->m_pos;
                ++nRead;
            }
            if (nRead < n) {
                p->m_size = read4(p->m_cache);
                if (p->m_size == 0) {
                    //no more to read
                    break;
                } else {
                    p->m_pos = 0;
                }
            } else {
                break;
            }
        }
        return nRead;
    }
    ~Solution() {
        for (auto i : m_bufToNodeptr) {
            delete i.second;
        }
    }

    private:
    struct Node {
        public:
        Node() : m_pos(0), m_size(0) {};
        int m_pos, m_size;
        char m_cache[4];
    };
    unordered_map<char*, Node*> m_bufToNodeptr;
};
