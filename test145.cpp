/*
 * test145.cpp
 *
 *  Created on: April 9, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//Design a data structure that can hold the continuously input numbers i_1, i_2,...i_N
//requirement:
//if there are N numbers, add next number takes O(logN) time complexity
//get the median takes O(1) time complexity
class _MedianHolder {
public:
	_MedianHolder() : m_head(NULL), m_lsize(0), m_rsize(0) {};
	~_MedianHolder() {
		deleteNodes(m_head);
		m_head = NULL;
		m_lsize = 0;
		m_rsize = 0;
	};
	void insertNumber(int value) {
		_Node *r = new _Node(value);
		if (!m_head) {
			//first number
			m_head = r;
			return;
		} else {
			//insert node to binary search tree
			_Node *p = m_head, *q = NULL;
			while (1) {
				if (r->m_value <= p->m_value) {
					//go to left tree
					if (p == m_head) {
						++m_lsize;
					}
					q = p->m_left;
					if (!q) {
						p->m_left = r;
						break;
					} else {
						p = q;
					}
				} else {
					//go to right tree
					if (p == m_head) {
						++m_rsize;
					}
					q = p->m_right;
					if (!q) {
						p->m_right = r;
						break;
					} else {
						p = q;
					}
				}
			}
			//check if we need to update median number
			if (m_lsize > m_rsize) {
				//move m_head to right tree
				p = m_head->m_left;
				q = m_head->m_right;
				if (!q) {
					//no node in right tree, switch left node and m_head
					p->m_right = m_head;
					m_head->m_left = NULL;
					m_head->m_right = NULL;
					m_head = p;
				} else {
					_Node *s = q;
					while (s) {
						if (s->m_left) {
							s = s->m_left;
						} else {
							s->m_left = m_head;
							m_head->m_left = NULL;
							m_head->m_right = NULL;
							break;
						}
					}
					_Node *t = NULL;
					s = p;
					while (s) {
						if (s->m_right) {
							t = s;
							s = s->m_right;
						} else {
							//s has no right child
							if (!s->m_left) {
								//s is leaf node, move s to root
								t->m_right = NULL;
								s->m_left = p;
								s->m_right = q;
							} else {
								//s has left child
								//move left child to s's parent
								if (!t) {
									//s is p, p will be m_head
									s->m_right = q;
								} else {
									t->m_right = s->m_left;
									s->m_left = p;
									s->m_right = q;
								}
							}
							m_head = s;
							break;
						}
					}
				}
				--m_lsize;
				++m_rsize;
			} else if (m_rsize > m_lsize + 1) {
				//move m_head to left tree
				++m_lsize;
				--m_rsize;
				p = m_head->m_left;
				q = m_head->m_right;
				_Node *s, *t;
				if (!p) {
					if (q->m_left) {
						//q->m_left is the new median
						s = m_head;
						s->m_right = NULL;
						m_head = q->m_left;
						q->m_left = NULL;
						m_head->m_right = q;
						m_head->m_left = s;
					} else {
						//q is the new median
						m_head->m_right = NULL;
						q->m_left = m_head;
						m_head = q;
					}
				} else {
					//move m_head to left, to the rightmost of left
					s = p;
					while (s) {
						if (s->m_right) {
							s = s->m_right;
						} else {
							s->m_right = m_head;
							m_head->m_left = NULL;
							m_head->m_right = NULL;
							break;
						}
					}
					//find the median number, should be the left of the right tree
					s = q, t = NULL;
					while (s) {
						if (s->m_left) {
							t = s;
							s = s->m_left;
						} else {
							//s is the next median number
							if (s == q) {
								q->m_left = p;
								m_head = q;
							} else {
								if (!s->m_right) {
									//s is leaf node
									t->m_left = NULL;
									s->m_left = p;
									s->m_right = q;
									m_head = s;
								} else {
									//s's right child should be t's left child
									t->m_left = s->m_right;
									s->m_left = p;
									s->m_right = q;
									m_head = s;
								}
							}
							break;
						}
					}
				}
			}
		}
	}

	int getMedian(void) {
		if (!m_head) {
			cout << "!!!No node!!!" << endl;
			return INT32_MIN;
		} else {
			return m_head->m_value;
		}
	}

private:
	struct _Node {
	public:
		int m_value;
		_Node *m_left, *m_right;
		_Node(int value) : m_value(value), m_left(NULL), m_right(NULL) {};
		~_Node() {};
	};
	_Node *m_head;
	int m_lsize, m_rsize; //left/right tree size
	void deleteNodes(_Node *head) {
		if (!head) {
			return;
		}
		deleteNodes(head->m_left);
		deleteNodes(head->m_right);
		delete head;
		return;
	}
};

//an example
int main(int argc, char* argv[]) {
	_MedianHolder mh;
	vector<int> arr({6, 1, 3, 0, 9, 8, 7, 2, 10, -1});
	cout << "median number:" << endl;
	for (int i = 0; i < arr.size(); ++i) {
		mh.insertNumber(arr[i]);
		cout << mh.getMedian() << ", ";
	}
	cout << endl;
	return 0;
}




