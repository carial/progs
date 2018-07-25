/*
 * test196.cpp
 *
 *  Created on: May 15, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

/*
Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.
*/

/**
 * Definition for undirected graph.
 */
 	struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

 	class Solution {
 	public:
 	    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
 	        if (!node) {
 	            return nullptr;
 	        }
 	        std::queue<UndirectedGraphNode*> nodeQueue;
 	        std::unordered_map<int, UndirectedGraphNode*> labelToNodeptr;
 	        UndirectedGraphNode *ret = nullptr;
 	        nodeQueue.push(node);
 	        while (!nodeQueue.empty()) {
 	            UndirectedGraphNode *orig = nodeQueue.front();
 	            nodeQueue.pop();
 	            //check if this node has been visited
 	            if (labelToNodeptr.find(orig->label) == labelToNodeptr.end()) {
 	                //copy this node
 	                UndirectedGraphNode *copy = new UndirectedGraphNode(orig->label);
 	                if (ret == nullptr) {
 	                    ret = copy;
 	                }
 	                //add @copy to lableToNodeptr map
 	                labelToNodeptr.emplace(copy->label, copy);
 	                //handle neighbor
 	                for (int i = 0; i < orig->neighbors.size(); ++i) {
 	                    //check if neighbor is visited
 	                    auto it = labelToNodeptr.find(orig->neighbors[i]->label);
 	                    if (it == labelToNodeptr.end()) {
 	                        //not visited yet
 	                        //add to queue
 	                        nodeQueue.push(orig->neighbors[i]);
 	                    } else {
 	                        //visited, connect two nodes
 	                        //check if copy and it->second is the same node
 	                        copy->neighbors.push_back(it->second);
 	                        if (copy != it->second) {
 	                            it->second->neighbors.push_back(copy);
 	                        }
 	                    }
 	                }
 	            }
 	        }
 	        return ret;
 	    }
 	};

int main (int argc, char *argv[]) {
	UndirectedGraphNode *n1 = new UndirectedGraphNode(0), *n2 = new UndirectedGraphNode(1);
	n1->neighbors.push_back(n1);
	n2->neighbors.push_back(n1);
	Solution sol;
	UndirectedGraphNode *n3 = sol.cloneGraph(n1);

	delete n1;
	delete n2;

}
