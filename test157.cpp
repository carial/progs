/*
 * test157.cpp
 *
 *  Created on: April 25, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <queue>
#include <cstdint>
#include <unordered_map>
#include <vector>
using namespace std;

//Design an algorithm and write code to serialize and deserialize a binary tree.
//Writing the tree to a file is called 'serialization' and reading back from the
//file to reconstruct the exact same binary tree is 'deserialization'.
// Definition of TreeNode:
class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
};

class Solution {
public:
    /**
     * This method will be invoked first, you should design your own algorithm
     * to serialize a binary tree which denote by a root node to a string which
     * can be easily deserialized by your own "deserialize" method later.
     */
    string serialize(TreeNode * root) {
        // write your code here
        vector<TreeNode*> treeArr;
        string ret;
        if (!root) {
            //empty tree
            return ret;
        }
        treeArr.push_back(root);
        int i = 0;
        while (i < treeArr.size()) {
            TreeNode *p = treeArr[i];
            ++i;
            if (p) {
                treeArr.push_back(p->left);
                treeArr.push_back(p->right);
            }
        }
        //output to string
        ret += std::to_string(treeArr[0]->val);
        for (i = 1; i < treeArr.size(); ++i) {
            ret += " ";
            if (treeArr[i]) {
                ret += std::to_string(treeArr[i]->val);
            } else {
                ret += "#";
            }
        }
        return ret;
    }

    /**
     * This method will be invoked second, the argument data is what exactly
     * you serialized at method "serialize", that means the data is not given by
     * system, it's given by your own serialize method. So the format of data is
     * designed by yourself, and deserialize it here as you serialize it in
     * "serialize" method.
     */
    TreeNode * deserialize(string &data) {
        // write your code here
        if (data.empty()) {
            return nullptr;
        }
        TreeNode *root, *p;
        queue<TreeNode *> treeQueue;
        unsigned int pos1 = 0, pos2;
        pos2 = data.find(' ', pos1);
        int value = std::stoi(data.substr(pos1, pos2 - pos1));
        root = new TreeNode(value);
        treeQueue.push(root);
        while (!treeQueue.empty()) {
            p = treeQueue.front();
            treeQueue.pop();
                //read next 2 values from string @data
                pos1 = pos2 + 1;
                pos2 = data.find(' ', pos1);
                //[pos1...(pos2 - 1)] is the data
                if (data.at(pos1) == '#') {
                    //it is an empty node
                    p->left = nullptr;
                } else {
                    value = std::stoi(data.substr(pos1, pos2 - pos1));
                    TreeNode *q = new TreeNode(value);
                    p->left = q;
                    treeQueue.push(q);
                }
                pos1 = pos2 + 1;
                pos2 = data.find(' ', pos1);
                if (data.at(pos1) == '#') {
                    //it is an empty node, push it in queue
                    p->right = nullptr;
                } else {
                    value = std::stoi(data.substr(pos1, pos2 - pos1));
                    TreeNode *q = new TreeNode(value);
                    p->right = q;
                    treeQueue.push(q);
                }
        }
        return root;
    }
};
