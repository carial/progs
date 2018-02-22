/*
 * test112.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//small sum of an array:
//for example: arr=[1 3 5 2 4 6], the sum of all elements on the left and smaller than arr[i] is [0 1 4 1 6 15], so the small sum is 27
//given an array, find the small sum of the array
struct _Node {
public:
	_Node(int val) : m_left(NULL), m_right(NULL), m_smallTotal(0), m_val(val) {}
	_Node *m_left;
	_Node *m_right;
	int m_smallTotal;
	int m_val;
};

_Node* insertNode(_Node *root, _Node *node) {
	if (!node) {
		return root;
	}
	if (!root) {
		return node;
	} else {
		if (root->m_val <= node->m_val) {
			root->m_right = insertNode(root->m_right, node);
		} else {
			//@node is smaller than root, update @m_smallTotal
			root->m_smallTotal += node->m_val;
			root->m_left = insertNode(root->m_left, node);
		}
	}
	return root;
}

int findSmallTotal(_Node *root, int val) {
	int total = 0;
	if (root) {
		if (root->m_val <= val) {
			//all root's left branch are smaller than val
			total += root->m_smallTotal;
			if (root->m_val < val) {
				total += root->m_val;
			}
			total += findSmallTotal(root->m_right, val);
		} else {
			//search along root's left branch
			total += findSmallTotal(root->m_left, val);
		}
	}
	return total;
}

void deleteNode(_Node *root) {
	if (!root) {
		return;
	}
	deleteNode(root->m_left);
	deleteNode(root->m_right);
	delete root;
}

int smallSum(const vector<int>& arr) {
	int smallSum = 0;
	_Node *root = NULL;
	for (int i = 0; i < arr.size(); ++i) {
		smallSum += findSmallTotal(root, arr[i]);
		//insert to binary search tree
		_Node *node = new _Node(arr[i]);
		root = insertNode(root, node);
	}
	deleteNode(root);
	return smallSum;
}

int main(int argc, char* argv[]) {
	cout << "small sum of array " << smallSum({1, 3, 5, 2, 4, 6}) << endl;
}




