/*
 * test199.cpp
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
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache( 2 );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

class LRUCache {
public:
    LRUCache(int capacity) : m_capacity(capacity), m_head(nullptr), m_tail(nullptr) {

    }

    ~LRUCache() {
        Node *p = m_head, *q;
        while (p) {
            q = p->m_next;
            delete p;
            p = q;
        }
    }

    int get(int key) {
        auto it1 = m_keyToNodeptr.find(key);
        if (it1 != m_keyToNodeptr.end()) {
            Node *p = it1->second;
            int val = p->m_val;
            //put p to the end of linked list
            Node *q = p->m_prev, *r = p->m_next;
            if (q && r) {
                //remove p
                q->m_next = r;
                r->m_prev = q;
                m_tail->m_next = p;
                p->m_prev = m_tail;
                p->m_next = nullptr;
                m_tail = p;
            } else if (!q && r) {
                //p is m_head;
                r->m_prev = nullptr;
                m_head = r;
                m_tail->m_next = p;
                p->m_prev = m_tail;
                p->m_next = nullptr;
                m_tail = p;
            } else if (q && !r) {
                //p is m_tail, no need to update
            } else {
                //p is only node, no need to update
            }
            return val;
        } else {
            return -1;
        }
    }

    void put(int key, int value) {
        auto it1 = m_keyToNodeptr.find(key);
        if (it1 != m_keyToNodeptr.end()) {
            //set val
            Node *p = it1->second;
            p->m_val = value;
            //update access time
            get(key);
        } else {
            //check if need to add (key, value) to the cache
            if (m_capacity > 0 || m_head) {
                Node *p = new Node(key, value);
                if (m_capacity > 0) {
                    //add to end of list
                    if (m_tail) {
                        m_tail->m_next = p;
                        p->m_prev = m_tail;
                        m_tail = p;
                    } else {
                        //list is empty
                        m_head = m_tail = p;
                    }
                    --m_capacity;
                } else {
                    //reach capacity, remove m_head
                    Node *q = m_head;
                    if (q->m_next) {
                        m_head = q->m_next;
                        m_head->m_prev = nullptr;
                        m_tail->m_next = p;
                        p->m_prev = m_tail;
                        m_tail = p;
                    } else {
                        m_head = m_tail = p;
                    }
                    //remove from map
                    m_keyToNodeptr.erase(m_keyToNodeptr.find(q->m_key));
                    delete q;
                }
                //add p to map
                m_keyToNodeptr.emplace(key, p);
            }
            //the capacity of cache is 0 or less than 0
            //cannot add key
        }
    }
    private:
    int m_capacity;
    struct Node {
        public:
        Node(int key, int val) : m_key(key), m_val(val), m_prev(nullptr), m_next(nullptr) {};
        int m_key;
        int m_val;
        Node *m_prev, *m_next;
    };
    unordered_map<int, Node*> m_keyToNodeptr;
    Node *m_head, *m_tail;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
