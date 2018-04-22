/*
 * test134.cpp
 *
 *  Created on: Feb 28, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//design a data pool structure that has the following features
//(1) it has 3 operations: insertKey, deleteKey, getRandomKey, each is in time complexity O(1)
//(2) the data in the pool is not duplicate
//(3) getRandomKey will return a key with equal probability
//place holder, make compiler happy
int getRandom(int N) {
	return 0;
}

template<class T>
class _DataPoolClass {
public:
	_DataPoolClass();
	~_DataPoolClass() {};
	void insertKey(const T& key);
	void deleteKey(const T& key);
	T getRandomKey() const;
private:
	unsigned int m_size;
	unordered_set<T> m_keys;
	vector<T> m_data;
	unordered_map<T, unsigned int> keyToIdx;
};

template<class T>
_DataPoolClass<T>::_DataPoolClass() : m_size(0) {}

template<class T>
void _DataPoolClass<T>::insertKey(const T& key) {
	auto it = m_keys.find(key);
	if (it == m_keys.end()) {
		m_keys.insert(key);
		++m_size;
		if (m_size > m_data.size()) {
			m_data.push_back(key);
		} else {
			m_data[m_size - 1] = key;
		}
		keyToIdx.emplace(key, m_size - 1);
	}
}

template<class T>
void _DataPoolClass<T>::deleteKey(const T& key) {
	auto it = m_keys.find(key);
	if (it != m_keys.end()) {
		m_keys.erase(key);
		auto it1 = keyToIdx.find(key);
		if (it1->second != m_size - 1) {
			m_data[it1->second] = m_data[m_size - 1];
			auto it2 = keyToIdx.find(m_data[it1->second]);
			it2->second = it1->second;
		}
		--m_size;
		keyToIdx.erase(it1);
	}
}

template<class T>
T _DataPoolClass<T>::getRandomKey() const {
	//generate a random number between 1...m_size with equal probability
	int i = getRandom(m_size);
	return m_data[i - 1];
}

int main(int argc, char* argv[]) {
	return 0;
}




