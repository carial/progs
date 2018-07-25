/*
 * test170.cpp
 *
 *  Created on: May 1, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

//LFU (Least Frequently Used) is a famous cache eviction algorithm.
//For a cache with capacity k, if the cache is full and need to evict a key in it,
//the key with the lease frequently used will be kicked out.
//Implement set and get method for LFU cache.
//Example
//Given capacity=3
//set(2,2)
//set(1,1)
//get(2)
//>> 2
//get(1)
//>> 1
//get(2)
//>> 2
//set(3,3)
//set(4,4)
//get(3)
//>> -1
//get(2)
//>> 2
//get(1)
//>> 1
//get(4)
//>> 4

class LFUCache {
public:
    /*
    * @param capacity: An integer
    */LFUCache(int capacity) : m_freqArr(capacity), m_capacity(capacity), m_size(0), m_tick(0) {
        // do intialization if necessary
    }

    /*
     * @param key: An integer
     * @param value: An integer
     * @return: nothing
     */
    void set(int key, int value) {
        // write your code here
        //put <key,value> into map
        auto it = m_keyToContent.find(key);
        if (it == m_keyToContent.end()) {
            if (m_capacity > 0) {
                //add <key, value> to heap
                if (m_size < m_capacity) {
                    _Content *p = new _Content(value, m_size, m_tick);
                    //add to heap
                    m_freqArr[m_size] = key;
                    m_keyToContent.emplace(key, p);
                    ++m_size;
                    ++m_tick;
                    //adjust heap
                    adjustHeap1();
                } else {
                    int key1 = m_freqArr[0];
                    //remove key1
                    m_freqArr[0] = key;
                    _Content *p = new _Content(value, 0, m_tick);
                    ++m_tick;
                    m_keyToContent.emplace(key, p);
                    auto it1 = m_keyToContent.find(key1);
                    delete it1->second;
                    m_keyToContent.erase(it1);
                    adjustHeap2(key);
                }
            }
        } else {
            it->second->m_value = value;
            //it->second->m_timeStamp = m_tick;
            //++m_tick;
        }
        return;
    }

    /*
     * @param key: An integer
     * @return: An integer
     */
    int get(int key) {
        // write your code here
        auto it1 = m_keyToContent.find(key);
        if (it1 == m_keyToContent.end()) {
            return -1;
        }
        int ret = it1->second->m_value;
        ++it1->second->m_freq;
        it1->second->m_timeStamp = m_tick;
        ++m_tick;
        adjustHeap2(key);
        return ret;
    }
    ~LFUCache() {
        for (auto it = m_keyToContent.begin(); it != m_keyToContent.end(); ++it) {
            delete it->second;
        }
    }
    private:
    void adjustHeap1() {
        //move last element up
        int cur = m_size - 1, up, freq1, freq2, pos1;
        auto it1 = m_keyToContent.find(m_freqArr[cur]);
        freq1 = it1->second->m_freq;
        while (cur > 0) {
            up = (cur - 1) / 2;
            auto it2 = m_keyToContent.find(m_freqArr[up]);
            freq2 = it2->second->m_freq;
            if (freq1 < freq2) {
                //move up
                int temp = m_freqArr[cur];
                m_freqArr[cur] = m_freqArr[up];
                m_freqArr[up] = temp;
                //update position
                it2->second->m_idx = cur;
                cur = up;
                it1->second->m_idx = cur;
            } else {
                break;
            }
        }
    }
    void adjustHeap2(int key) {
        //find index corresponding to key
        auto it1 = m_keyToContent.find(key);
        vector<int>::size_type cur = it1->second->m_idx, down1, down2, downPos;
        unsigned int curFreq = it1->second->m_freq, freq1, freq2, minFreq;
        unsigned int curTick = it1->second->m_timeStamp;
        //update
        while (cur < m_size) {
            down2 = (cur + 1) * 2;
            down1 = (cur + 1) * 2 - 1;
            minFreq = curFreq;
            int minTick = curTick;
            downPos = cur;
            unordered_map<int, _Content*>::iterator it2, it3;
            if (down1 < m_size) {
                it2 = m_keyToContent.find(m_freqArr[down1]);
                freq1 = it2->second->m_freq;
                unsigned int tick1 = it2->second->m_timeStamp;
                if (freq1 < minFreq || (freq1 == minFreq && minTick > tick1)) {
                    minFreq = freq1;
                    downPos = down1;
                    minTick = tick1;
                }
            }
            if (down2 < m_size) {
                it3 = m_keyToContent.find(m_freqArr[down2]);
                freq2 = it3->second->m_freq;
                unsigned int tick2 = it3->second->m_timeStamp;
                if (freq2 < minFreq || (freq2 == minFreq && minTick > tick2)) {
                    minFreq = freq2;
                    downPos = down2;
                    minTick = tick2;
                }
            }
            if (downPos == cur) {
                break;
            } else if (downPos == down1) {
                it2->second->m_idx = cur;
                it1->second->m_idx = down1;
                m_freqArr[cur] = m_freqArr[down1];
                m_freqArr[down1] = key;
                cur = down1;
            } else {
                it3->second->m_idx = cur;
                it1->second->m_idx = down2;
                m_freqArr[cur] = m_freqArr[down2];
                m_freqArr[down2] = key;
                cur = down2;
            }
        }
        return;
    }
    vector<int> m_freqArr;
    struct _Content {
        public:
        int m_value;
        unsigned int m_freq;
        vector<int>::size_type m_idx;
        unsigned int m_timeStamp;
        _Content(int value, vector<int>::size_type idx, unsigned int timeStamp) :
            m_value(value), m_freq(0), m_idx(idx), m_timeStamp(timeStamp) {}
    };
    unordered_map<int, _Content*> m_keyToContent;
    int m_capacity, m_size, m_tick; //@m_tick: time stamp
};
