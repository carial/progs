/*
 * test111.cpp
 *
 *  Created on: Feb 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

//given an unsorted integer array and an integer K, the items in array can be positive, negative, or zero. find the maximum length of the subarray that total equals or less than K
//time complexity O(N^2), space complexity O(1)
int maxLengthArrayAddToK(const vector<int>& arr, int K) {
	if (arr.size() == 0) {
		return -1;
	}
	//@dir 0: from left to right, 1: from right to left
	int maxLength = 0, sum = 0, dir;
	for (int i = 0; i < arr.size(); ++i) {
		sum += arr[i];
	}
	if (sum <= K) {
		return arr.size();
	}
	dir = 1; //from right to left
	int i;
	for (int length = arr.size() - 1; length > 0; --length) {
		if (dir == 1) {
			sum -= arr[length];
		} else {
			sum -= arr[arr.size() - 1 - length];
		}
		dir = 1 - dir;
		if (dir) {
			i = arr.size() - 1;
		} else {
			i = 0;
		}
		while(1) {
			if (sum <= K) {
				return length;
			}
			if (dir) {
				--i;
				if ( i - length + 1 >= 0) {
					sum -= arr[i + 1];
					sum += arr[i - length + 1];
				} else {
					break;
				}
			} else {
				++i;
				if (i + length <= arr.size()) {
					sum += arr[i + length - 1];
					sum -= arr[i - 1];
				} else {
					break;
				}
			}
		}
	}
	return maxLength;
}

//method2: time complexity O(NlogN), space complexity O(N)
//@_Node is a binary search tree, left branch contains nodes smaller than parent, right branch contains nodes larger than parent
struct _Node {
public:
	_Node(_Node* left, _Node* right, int idx, int val) :
		m_left(left), m_right(right), m_idx(idx), m_val(val) {}
	_Node *m_left;
	_Node *m_right;
	int m_idx;
	int m_val;
};

_Node* insertNode(_Node *root, _Node *node) {
	if (!node) {
		return root;
	}
	if (!root) {
		return node;
	} else {
		if (root->m_val < node->m_val) {
			//node should be on root's right branch
			root->m_right = insertNode(root->m_right, node);
		} else {
			root->m_left = insertNode(root->m_left, node);
		}
	}
	return root;
}

void deleteTree(_Node *root) {
	if (!root) {
		return;
	}
	deleteTree(root->m_left);
	deleteTree(root->m_right);
	delete root;
}

int findIndex(_Node *root, int sum) {
	if (!root) {
		return -2;
	} else if (root->m_val >= sum) {
		return root->m_idx;
	} else {
		//@root->m_val < sum
		return findIndex(root->m_right, sum);
	}
}

int maxLengthArrayAddToK2(const vector<int>& arr, int K) {
	//@sum is the total from 0 to i
	int maxLength = 0, sum = 0;
	//@pos is the leftmost position that [0...i] total is sum
	unordered_set<int> totals;
	//to handle single item value equals to K, 0 always appears and in pos -1
	totals.emplace(0);
	_Node *root = new _Node(NULL, NULL, -1, 0);
	for (int i = 0; i < arr.size(); ++i) {
		sum += arr[i];
		//find minimum index that the node value is greater than sum - K
		int idx = findIndex(root, sum - K);
		if (idx != -2 && i - idx > maxLength) {
			maxLength = i - idx;
		}
		//check if sum - K has appeared before
		//add @sum to @totals and binary tree
		auto it = totals.find(sum);
		if (it == totals.end()) {
			totals.emplace(sum);
			_Node *node = new _Node(NULL, NULL, i, sum);
			insertNode(root, node);
		}
	}
	deleteTree(root);
	return maxLength;
}

int main(int argc, char* argv[]) {
	int K = 3;
	cout << "maximum length of array add to equal or less than " << K << " :" << maxLengthArrayAddToK2({1, -1, -2, 6, 3, 1, 1}, 8) << endl;
}




