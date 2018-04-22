/*
 * test144.cpp
 *
 *  Created on: April 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

//Design a heap structure that do not need to re-allocate memory if the allocated memory is not enough
//use tree-like structure
class _Heap {
public:
	_Heap(bool isSmallHeap) : m_head(NULL), m_up(m_head), m_size(0), m_isSmallHeap(isSmallHeap) {};
	~_Heap() {
		deleteNode(m_head);
		m_head = NULL;
		m_up = m_head;
		m_size = 0;
		m_isSmallHeap = true;
	}
	int getHead() {
		if (m_head) {
			return m_head->m_value;
		} else {
			cout << endl << "!!!Head node is NULL!!!" << endl;
			return INT32_MIN;
		}
	}
	int getSize() {
		return m_size;
	}
	void add(int value) {
		if (!m_head) {
			//allocate a new node
			m_head = new _Node(NULL, value);
			m_head->m_next = m_head;
			m_head->m_prev = m_head;
			++m_size;
			m_up = m_head;
		} else {
			_Node *node = new _Node(m_up, value);
			++m_size;
			//add node to the heap
			if (!m_up->m_left) {
				//m_up must be the first node in its level
				m_up->m_left = node;
				node->m_next = node; //node is the first node in its level
				node->m_prev = node;
			} else if (!m_up->m_right) {
				m_up->m_right = node;
				node->m_next = m_up->m_left->m_next;
				node->m_next->m_prev = node;
				m_up->m_left->m_next = node;
				node->m_prev = m_up->m_left;
				//do not update m_up yet
			} else {
				//neither m_left/m_right is NULL
				_Node *node1 = m_up->m_next;
				if (node1->m_left) {
					//all nodes at this level has children, go to the next level
					m_up = node1->m_left;
					node->m_up = m_up;
					m_up->m_left = node;
					node->m_next = node;
					node->m_prev = node;
				} else {
					node->m_up = node1;
					node1->m_left = node;
					node->m_next = m_up->m_right->m_next;
					node->m_next->m_prev = node;
					m_up->m_right->m_next = node;
					node->m_prev = m_up->m_right;
					m_up = node1;
				}
			}
			//adjust node
			if (m_isSmallHeap) {
				//head is the smallest number
				_Node *node1 = node->m_up;
				while (node1 && node->m_value < node1->m_value) {
					//exchange node and node1
					exchangeNodes(node, node1);
					node1 = node->m_up;
				}
				if (!node1) {
					m_head = node;
				}
			} else {
				//head is the biggest number
				_Node *node1 = node->m_up;
				while (node1 && node->m_value > node1->m_value) {
					//exchange node and node1
					exchangeNodes(node, node1);
					node1 = node->m_up;
				}
				if (!node1) {
					m_head = node;
				}
			}
		}
	}

	void popHead(void) {
		if (m_size == 1) {
			//only head node
			deleteNode(m_head);
			m_head = NULL;
			m_up = NULL;
			m_size = 0;
		} else if (m_size > 1) {
			//copy the last node to m_head
			_Node *last;
			if (m_up->m_right) {
				last = m_up->m_right;
				m_up->m_right = NULL;
			} else {
				last = m_up->m_left;
				m_up->m_left = NULL;
				//update m_up
				if (m_up == m_head) {
					//no need to update m_up
				} else {
					_Node *next_up = m_up->m_prev;
					if (!next_up->m_right) {
						//current m_up is the first node in its level
						//set to the last node in upper level
						next_up = next_up->m_up->m_prev;
					}
					m_up = next_up;
				}
			}
			m_head->m_value = last->m_value;
			//delete last node
			//check if last node is the first node in its level
			if (last->m_next != last) {
				last->m_prev->m_next = last->m_next;
				last->m_next->m_prev = last->m_prev;
			}
			delete last;
			--m_size;
			//move m_head down to the next level
			_Node *current = m_head, *next_l = m_head->m_left, *next_r = m_head->m_right;
			while (next_l || next_r) {
				_Node *change = findChangeNode(current, next_l, next_r);
				if (change == current) {
					break;
				}
				//switch node change and current
				exchangeNode2(current, change);
				next_l = current->m_left;
				next_r = current->m_right;
			}
		}
	}

private:
	_Heap();
	struct _Node{
	public:
		_Node *m_left, *m_right, *m_up, *m_next, *m_prev;
		int m_value;
		_Node() : m_left(NULL), m_right(NULL), m_up(NULL), m_next(NULL), m_prev(NULL), m_value(0) {}
		_Node(_Node* up, int value) : m_left(NULL), m_right(NULL), m_up(up), m_next(NULL), m_prev(NULL), m_value(value) {}
	};

	_Node *m_head, *m_up;
	int m_size;
	bool m_isSmallHeap;

	void deleteNode(_Node *node) {
		if (node) {
			deleteNode(node->m_left);
			deleteNode(node->m_right);
			delete node;
		}
	}
	void exchangeNodes(_Node *node, _Node *node1) {
		_Node *node2 = node1->m_up;
		if (node2) {
			if (node2->m_left == node1) {
				node2->m_left = node;
			} else {
				node2->m_right = node;
			}
			_Node *prev = node1->m_prev, *next = node1->m_next;
			if (node->m_next == node) {
				//single node in this level
				node1->m_next = node1;
				node1->m_prev = node1;
			} else {
				node1->m_next = node->m_next;
				node1->m_prev = node->m_prev;
				node1->m_next->m_prev = node1;
				node1->m_prev->m_next = node1;
			}
			node->m_next = next;
			node->m_prev = prev;
			next->m_prev = node;
			prev->m_next = node;
		} else {
			//node1 is head node
			if (node->m_next != node) {
				_Node *prev = node->m_prev, *next = node->m_next;
				node1->m_prev = prev;
				node1->m_next = next;
				prev->m_next = node1;
				next->m_prev = node1;
				node->m_prev = node;
				node->m_next = node;
			}
		}
		node->m_up = node2;
		node1->m_up = node;
		if (node1->m_left == node) {
			_Node *right = node1->m_right;
			node1->m_left = node->m_left;
			node1->m_right = node->m_right;
			node->m_left = node1;
			node->m_right = right;
		} else {
			_Node *left = node1->m_left;
			node1->m_left = node->m_left;
			node1->m_right = node->m_right;
			node->m_left = left;
			node->m_right = node1;

		}
		if (node1->m_left) {
			node1->m_left->m_up = node1;
		}
		if (node1->m_right) {
			node1->m_right->m_up = node1;
		}
		if (node->m_left) {
			node->m_left->m_up = node;
		}
		if (node->m_right) {
			node->m_right->m_up = node;
		}
		if (m_up) {
			if (m_up == node1) {
				m_up = node;
			} else if (m_up == node) {
				m_up = node1;
			}
		}
	}

	_Node* findChangeNode(_Node *current, _Node *next_l, _Node *next_r) {
		_Node *change = current;
		if (m_isSmallHeap) {
			if (next_r && change->m_value > next_r->m_value) {
				change = next_r;
			}
			if (next_l && change->m_value > next_l->m_value) {
				change = next_l;
			}
		} else {
			if (next_r && change->m_value < next_r->m_value) {
				change = next_r;
			}
			if (next_l && change->m_value < next_l->m_value) {
				change = next_l;
			}
		}
		return change;
	}

	void exchangeNode2(_Node *current, _Node *change) {
		//exchange current with change, change is its left or right child
		if (m_head == current) {
			m_head = change;
		}
		_Node *c_up = current->m_up, *c_prev = current->m_prev, *c_next = current->m_next, *c_left = current->m_left, *c_right = current->m_right;
		_Node *c_up2 = change->m_up, *c_prev2 = change->m_prev, *c_next2 = change->m_next, *c_left2 = change->m_left, *c_right2 = change->m_right;
		change->m_up = c_up;
		current->m_up = change;
		if (c_next != current) {
			change->m_next = c_next;
			change->m_prev = c_prev;
			c_next->m_prev = change;
			c_prev->m_next = change;
		} else {
			change->m_next = change;
			change->m_prev = change;
		}
		if (c_next2 != change) {
			current->m_next = c_next2;
			current->m_prev = c_prev2;
			c_next2->m_prev = current;
			c_prev2->m_next = current;
		} else {
			current->m_next = current;
			current->m_prev = current;
		}
		if (c_up) {
			if (c_up->m_left == current) {
				c_up->m_left = change;
			} else {
				c_up->m_right = change;
			}
		}
		current->m_left = c_left2;
		current->m_right = c_right2;
		if (c_left2) {
			c_left2->m_up = current;
		}
		if (c_right2) {
			c_right2->m_up = current;
		}
		if (change == c_left) {
			//left child
			change->m_left = current;
			change->m_right = c_right;
		} else {
			//right child
			change->m_left = c_left;
			change->m_right = current;
		}
		if (m_up == current) {
			m_up = change;
		} else if (m_up == change) {
			m_up = current;
		}
		return;
	}
};

int main(int argc, char* argv[]) {
	return 0;
}




