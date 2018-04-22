/*
 * test133.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//design a memory cache structure that has the following features
//(1) the cache has a fixed size of K
//(2) there are two operations set(key, value) and get(key), each of O(1) time complexity
//(3) if a set/get operation happens on a key, that key is the most recent accessed record
//(4) if the cache is full, remove the oldest record (the set/get operation happened in the oldest in history)
template<class T1, class T2>
class _CacheClass {
public:
	_CacheClass(int size);
	~_CacheClass() {
		//clean up
		for (_OpSeq *p = m_mostRecent, *q = m_mostRecent; p; p = q) {
			q = p->m_next;
			delete p;
		}
		m_curSize = 0;
	};
	void set(const T1& key, const T2& value) {
		//check if @key is already in the Cache
		auto it = m_data.find(key);
		if (it != m_data.end()) {
			//old record
			it->second.m_value = value;
			//update access time
			_OpSeq *p = it->second.m_node->m_prev, *q = it->second.m_node->m_next;
			if (p) {
				//move it to most recent
				it->second.m_node->m_prev = NULL;
				it->second.m_node->m_next = m_mostRecent;
				m_mostRecent->m_prev = it->second.m_node;
				m_mostRecent = it->second.m_node;
				p->m_next = q;
				if (q) {
					q->m_prev = p;
				} else {
					m_leastRecent = p;
				}
			}
		} else {
			//new record, check current cache size
			_OpSeq *q = new _OpSeq(key, NULL, m_mostRecent);
			if (m_curSize == m_size) {
				//cache is full, need to remove oldest record
				_OpSeq *oldest = m_leastRecent, *p = m_leastRecent->m_prev;
				auto it = m_data->find(oldest->m_key);
				m_data.erase(it);
				delete m_leastRecent;
				if (m_size == 1) {
					q->m_next = NULL;
					m_mostRecent = m_leastRecent = q;
				} else {
					p->m_next = NULL;
					m_leastRecent = p;
					m_mostRecent->m_prev = q;
					m_mostRecent = q;
				}
			} else {
				//add at the head
				m_mostRecent->m_prev = q;
				m_mostRecent = q;
				++m_curSize;
			}
			m_data.emplace(key, _CacheData(value, q));
		}
	};

	T2 get(const T1& key) const {
		auto it = m_data.find(key);
		if (it != m_data.end()) {
			//update access
			_OpSeq *cur = it->second.m_node;
			if (m_mostRecent != cur) {
				_OpSeq *p = cur->m_prev, *q = cur->m_next;
				p->m_next = q;
				if (q) {
					q->m_prev = p;
				} else {
					m_leastRecent = p;
				}
				cur->m_prev = NULL;
				cur->m_next = m_mostRecent;
				m_mostRecent->m_prev = cur;
				m_mostRecent = cur;
			}
			return it->second.m_value;
		} else {
			return T2();
		}
	};

private:
	struct _OpSeq {
	public:
		_OpSeq(const T1& key, _OpSeq *prev, _OpSeq *next) : m_key(key), m_prev(prev), m_next(next) {};
		T1 m_key;
		_OpSeq *m_prev;
		_OpSeq *m_next;
	};

	struct _CacheData {
	public:
		_CacheData(const T2& value, _OpSeq *node) : m_value(value), m_node(node) {};
		T2 m_value;
		_OpSeq *m_node;
	};
	unordered_map<T1, _CacheData> m_data;
	_OpSeq *m_mostRecent;
	_OpSeq *m_leastRecent;
	const unsigned int m_size; //cache size
	unsigned int m_curSize; //current number of records
};

template<class T1, class T2>
_CacheClass<T1, T2>::_CacheClass(int size) : m_mostRecent(NULL), m_leastRecent(NULL), m_size(size), m_curSize(0) {}

int main(int argc, char* argv[]) {
	return 0;
}




