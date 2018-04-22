/*
 * test131.cpp
 *
 *  Created on: Feb 27, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <tuple>
#include <functional>

using namespace std;
//design a hash table that has "setAll" function that can set the values of all keys to the same
//requires O(1) time complexity
template<class T1, class T2>
class _HashTable {
public:
	_HashTable();
	void put(const T1& key, const T2& val);
	const T2 get(const T1& key) const;
	bool containsKey(const T1& key) const;
	void setAll(const T2& val);
	~_HashTable() {};
private:
	const unsigned int m_size;
	unsigned int m_seq; //add sequence id
	vector<vector<tuple<T1, T2, unsigned int>>> m_hTable;
	pair<T2, unsigned int> m_gVal;
};

template<class T1, class T2>
_HashTable<T1, T2>::_HashTable() : m_size(1024), m_seq(0), m_hTable(m_size, {}), m_gVal(T2(), m_seq++) {};

template<class T1, class T2>
void _HashTable<T1, T2>::put(const T1& key, const T2& val) {
	//calculate a hash number
	unsigned int idx = std::hash<T1>{}(key) % m_size;
	if (m_hTable[idx].empty()) {
		m_hTable[idx].emplace_back(key, val, m_seq++);
	} else {
		int i;
		for (i = 0; i < m_hTable[idx].size(); ++i) {
			if (std::get<1>(m_hTable[idx][i]) == key) {
				break;
			}
		}
		if (i == m_hTable[idx].size()) {
			//not found
			m_hTable[idx].emplace_back(key, val, m_seq++);
		} else {
			m_hTable[idx][i] = make_tuple(key, val, m_seq++);
		}
	}
}

template<class T1, class T2>
const T2 _HashTable<T1, T2>::get(const T1& key) const {
	unsigned int idx = std::hash<T1>{}(key) % m_size;
	if (m_hTable[idx].empty()) {
		return T2();
	} else {
		int i;
		for (i = 0; i < m_hTable[idx].size(); ++i) {
			if (std::get<1>(m_hTable[idx][i]) == key) {
				break;
			}
		}
		if (i == m_hTable[idx].size()) {
			return T2();
		} else {
			unsigned int seq = std::get<3>(m_hTable[idx][i]);
			if (seq > m_gVal.second) {
				return std::get<2>(m_hTable[idx][i]);
			} else {
				return m_gVal.first;
			}
		}
	}
}

template<class T1, class T2>
void _HashTable<T1, T2>::setAll(const T2& val) {
	m_gVal.first = m_seq++;
	m_gVal.second = val;
	return;
}

template<class T1, class T2>
bool _HashTable<T1, T2>::containsKey(const T1& key) const {
	unsigned int idx = std::hash<T1>{}(key) % m_size;
	int i;
	for (i = 0; i < m_hTable[idx].size(); ++i) {
		if (std::get<1>(m_hTable[idx][i]) == key) {
			break;
		}
	}
	if (i == m_hTable[idx].size()) {
		return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	return 0;
}




