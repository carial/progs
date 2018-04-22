/*
 * test149.cpp
 *
 *  Created on: April 11, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <stack>
using namespace std;

//Design a function to find the top K strings that appear the most
//input: string array and a number K
//requirement:
//the time complexity is O(NlogK), N is string array size
//for example: arr=["1", "2", "1", "3"], K = 2
//output: No 1: 1, times: 2
//        No 2: 2, times: 1
struct _Node {
public:
	string m_value;
	int m_num;
	_Node(const string& value) : m_value(value), m_num(1) {};
	~_Node() {};
};

void addToHeap(vector<_Node*>& smallHeap, _Node *node, int pos) {
	smallHeap[pos] = node;
	//bottom-up update
	int up;
	do {
		up = (pos - 1) / 2;
		if (smallHeap[up]->m_num > smallHeap[pos]->m_num) {
			//switch up and pos
			_Node *p = smallHeap[up];
			smallHeap[up] = smallHeap[pos];
			smallHeap[pos] = p;
		} else {
			break;
		}
		pos = up;
	} while (up);
}

void updateHeap(vector<_Node*>& smallHeap, int len) {
	//move smallHeap[0] down if necessary
	_Node *p = smallHeap[0], *q, *r;
	int pos = 0;
	while (1) {
		if ((pos + 1) * 2 - 1 < len) {
			q = smallHeap[(pos + 1) * 2 - 1];
		} else {
			q = NULL;
		}
		if ((pos + 1) * 2 < len) {
			r = smallHeap[(pos + 1) * 2];
		} else {
			r = NULL;
		}
		_Node *change = p;
		if (q && change->m_num > q->m_num) {
			change = q;
		}
		if (r && change->m_num > r->m_num) {
			change = r;
		}
		if (change == p) {
			break;
		} else if (change == q) {
			smallHeap[(pos + 1) * 2 - 1] = p;
			smallHeap[pos] = q;
			pos = (pos + 1) * 2 - 1;
		} else {
			smallHeap[(pos + 1) * 2] = p;
			smallHeap[pos] = r;
			pos = (pos + 1) * 2;
		}
	}
	return;
}

void printTopKStrings(const vector<string>arr, int K) {
	int len = arr.size();
	if (len == 0 || K <= 0) {
		return;
	}
	unordered_map<string, int> strToPosMap;
	vector<_Node*> strSet(len);
	int size = 0;
	//count different strings
	for (int i = 0; i < len; ++i) {
		auto it = strToPosMap.find(arr[i]);
		if (it == strToPosMap.end()) {
			//new str
			_Node *p = new _Node(arr[i]);
			strSet[size] = p;
			strToPosMap.emplace(arr[i], size);
			++size;
		} else {
			++strSet[it->second]->m_num;
		}
	}
	//build K small heap from @strSet
	int heapSize = size <= K ? size : K;
	vector<_Node*> strSmallHeap(heapSize);
	for (int i = 0; i < size; ++i) {
		_Node *p = strSet[i];
		if (i == 0) {
			//add to heap
			strSmallHeap[0] = p;
		} else if (i < K){
			//add to heap, maintain small heap
			addToHeap(strSmallHeap, p, i);
		} else if (p->m_num > strSmallHeap[0]->m_num) {
			//add to small heap and update
			strSmallHeap[0] = p;
			updateHeap(strSmallHeap, heapSize);
		}
	}

	//print out the heap
	vector<_Node*> strSet2(heapSize);
	for (int i = heapSize; i > 0; --i) {
		strSet2[i - 1] = strSmallHeap[0];
		//move last element to strSmallHeap head
		strSmallHeap[0] = strSmallHeap[i - 1];
		updateHeap(strSmallHeap, i - 1);
	}
	for (int i = 0; i < heapSize; ++i) {
		cout << "No " << i << ": " << strSet2[i]->m_value << ", times: " << strSet2[i]->m_num << endl;
	}
	for (int i = 0; i < size; ++i) {
		delete strSet[i];
	}
	return;
}

//implement topKRecord class with the following functions:
//(1) add(const string& str): add a string to the class (the string may exist, in this case update its appearance)
//(2) printTopK(): print the top K appearance strings
//requirement:
//add method time complexity O(logK), printTopK() method time complexity O(K)
//K is the predefined number in constructor
class _topKRecord {
public:
	_topKRecord(int K) : m_K(K), m_size(0), m_topK(K) {};
	~_topKRecord() {
		for (auto it = m_strToNodeMap.begin(); it != m_strToNodeMap.end(); ++it) {
			delete it->second;
		}
	}
	void add(const string& str);
	void printTopK(void);
private:
	struct _Node {
	public:
		string m_value;
		int m_num;
		bool m_isTopK;
		int m_pos; //position in @m_topK
		_Node(const string& value) : m_value(value), m_num(1), m_isTopK(false), m_pos(-1) {};
	};
	int m_K;
	int m_size;
	vector<_Node*> m_topK;
	unordered_map<string, _Node*> m_strToNodeMap;
	void updateTopK(_Node *);
};

void _topKRecord::add(const string& str) {
	//check if the string is existing
	auto it = m_strToNodeMap.find(str);
	if (it == m_strToNodeMap.end()) {
		//new string
		_Node *p = new _Node(str);
		m_strToNodeMap.emplace(str, p);
		updateTopK(p);
	} else {
		++it->second->m_num;
		updateTopK(it->second);
	}
}

void _topKRecord::printTopK() {
	for (int i = 0; i < m_size; ++i) {
		cout << "string: \"" << m_topK[i]->m_value << "\", times: " << m_topK[i]->m_num << endl;
	}
	cout << endl;
}

void _topKRecord::updateTopK(_Node *p) {
	if (p->m_isTopK) {
		//string is already in the heap, update its position
		int pos = p->m_pos;
		_Node *q, *r, *change;
		while (1) {
			if ((pos + 1) * 2 - 1 < m_size) {
				q = m_topK[(pos + 1) * 2 - 1];
			} else {
				q = nullptr;
			}
			if ((pos + 1) * 2 < m_size) {
				r = m_topK[(pos + 1) * 2];
			} else {
				r = nullptr;
			}
			change = p;
			if (q && q->m_num < change->m_num) {
				change = q;
			}
			if (r && r->m_num < change->m_num) {
				change = r;
			}
			if (change == p) {
				break;
			} else if (change == q) {
				//switch p and q
				m_topK[(pos + 1) * 2 - 1] = p;
				m_topK[pos] = q;
				p->m_pos = (pos + 1) * 2 - 1;
				q->m_pos = pos;
				pos = (pos + 1) * 2 - 1;
			} else {
				//switch p and r
				m_topK[(pos + 1) * 2] = p;
				m_topK[pos] = r;
				p->m_pos = (pos + 1) * 2;
				r->m_pos = pos;
				pos = (pos + 1) * 2;
			}
		}
	} else {
		//string not in heap
		if (m_size < m_K) {
			//add to heap
			m_topK[m_size] = p;
			p->m_isTopK = true;
			p->m_pos = m_size;
			++m_size;
			//bottom up update
			while (1) {
				if (p->m_pos == 0) {
					break;
				}
				_Node *q = m_topK[(p->m_pos - 1) / 2];
				if (q->m_num > p->m_num) {
					//switch p and q
					m_topK[(p->m_pos - 1) / 2] = p;
					m_topK[p->m_pos] = q;
					int j = p->m_pos;
					p->m_pos = q->m_pos;
					q->m_pos = j;
				} else {
					break;
				}
			}
		} else {
			//update heap
			if (p->m_num > m_topK[0]->m_num) {
				//replace m_topK[0] with p
				m_topK[0]->m_isTopK = false;
				m_topK[0]->m_pos = -1;
				p->m_pos = 0;
				p->m_isTopK = true;
				m_topK[0] = p;
				_Node *q, *r, *change;
				while (1) {
					if ((p->m_pos + 1) * 2 - 1 < m_K) {
						q = m_topK[(p->m_pos + 1) * 2 - 1];
					} else {
						q = nullptr;
					}
					if ((p->m_pos + 1) * 2 < m_K) {
						r = m_topK[(p->m_pos + 1) * 2];
					} else {
						r = nullptr;
					}
					change = p;
					if (q && q->m_num < change->m_num) {
						change = q;
					}
					if (r && r->m_num < change->m_num) {
						change = r;
					}
					if (change == p) {
						break;
					} else if (change == q) {
						//switch with q
						m_topK[q->m_pos] = p;
						m_topK[p->m_pos] = q;
						int j = p->m_pos;
						p->m_pos = q->m_pos;
						q->m_pos = j;
					} else {
						//switch with r
						m_topK[r->m_pos] = p;
						m_topK[p->m_pos] = r;
						int j = p->m_pos;
						p->m_pos = r->m_pos;
						r->m_pos = j;
					}
				}
			}
		}
	}
}

//an example
int main(int argc, char* argv[]) {
#if 0
	vector<string> arr({"1", "3", "2", "1"});
	printTopKStrings(arr, 2);
#endif
	_topKRecord record(2);
	record.add("A");
	record.printTopK();
	record.add("B");
	record.add("B");
	record.printTopK();
	record.add("C");
	record.add("C");
	record.printTopK();
	return 0;
}




