/*
 * test209.cpp
 *
 *  Created on: June 8, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

/*
 * A city's skyline is the outer contour of the silhouette formed by all the buildings in that city
 * when viewed from a distance. Now suppose you are given the locations and height of all the buildings
 * as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings
 * collectively (Figure B).
 *
 * The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi],
 * where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively, and Hi
 * is its height. It is guaranteed that 0 ≤ Li, Ri ≤ INT_MAX, 0 < Hi ≤ INT_MAX, and Ri - Li > 0. You may
 * assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
 * For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12],
 * [15 20 10], [19 24 8] ] .
 * The output is a list of "key points" (red dots in Figure B) in the format of
 * [ [x1,y1], [x2, y2], [x3, y3], ... ] that uniquely defines a skyline. A key point is the left endpoint of
 * a horizontal line segment. Note that the last key point, where the rightmost building ends, is merely
 * used to mark the termination of the skyline, and always has zero height. Also, the ground in between any
 * two adjacent buildings should be considered part of the skyline contour.
 * For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0],
 * [15 10], [20 8], [24, 0] ].

 * Notes:
 * The number of buildings in any input list is guaranteed to be in the range [0, 10000].
 * The input list is already sorted in ascending order by the left x position Li.
 * The output list must be sorted by the x position.
 * There must be no consecutive horizontal lines of equal height in the output skyline.
 * For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable; the three
 * lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
 */

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        int len1 = buildings.size();
        if (len1 == 0) {
            return {};
        }
        vector<pair<int, int>> ret;
        //maintain a max heap structure to get the skyline at certain pos
        //if a building end pos passed, that building's height is changed to 0
        //at each change point, if max value of heap has changed, output <pos, max>
        //maintain two index: nextL, nextR pointing to next Li and Ri segment
        //initially nextLIndex=0, nextRIndex=0.
        //max heap @maxBuilding store all building index
        vector<int> maxBuilding(len1, 0);
        vector<int> buildingIndexToMaxBuildingIndex(len1);
        vector<int> maxBuildingIndexToBuildingIndex(len1);
        vector<int> endLine(len1);
        for (int i = 0; i < len1; ++i) {
            buildingIndexToMaxBuildingIndex[i] = i;
            maxBuildingIndexToBuildingIndex[i] = i;
            endLine[i] = i;
        }
        int prevMax = 0;
        int i, j;
        //sort end building line in increasing order
        std::sort(endLine.begin(), endLine.end(), [buildings] (int i, int j) -> bool {
            return buildings[i][1] < buildings[j][1];
        });

#if 0
        for (auto i : buildingIndexToMaxBuildingIndex) {
        		cout << i << ", ";
        }
        cout << endl;
        for (auto i : maxBuildingIndexToBuildingIndex) {
        		cout << i << ", ";
        }
        cout << endl;
        for (auto i : endLine) {
        		cout << i << ", ";
        }
        cout << endl;
#endif

        for (i = 0, j = 0; i < len1 || j < len1; ) {
            if (j == len1 || (i < len1 && buildings[i][0] < buildings[endLine[j]][1])) {
                //left line of @i
                int val = buildings[i][0];
                while (i < len1 && buildings[i][0] == val) {
                    //new leftline
                    maxBuilding[buildingIndexToMaxBuildingIndex[i]] = buildings[i][2];
                    //update maxBuilding
                    updateMaxBuilding1(maxBuilding, buildingIndexToMaxBuildingIndex, maxBuildingIndexToBuildingIndex, i);
                    ++i;
                }
                //cout << maxBuilding[0] << ", " << val << endl;

                if (prevMax != maxBuilding[0]) {
                    prevMax = maxBuilding[0];
                    ret.push_back(std::make_pair(val, prevMax));
                }
            } else if (i == len1 || (j < len1 && buildings[i][0] > buildings[endLine[j]][1])) {
                //right line of @endLine[j]
                int val = buildings[endLine[j]][1];
                while (j < len1 && buildings[endLine[j]][1] == val) {
                    maxBuilding[buildingIndexToMaxBuildingIndex[endLine[j]]] = 0;
                    //upate maxBuilding
                    updateMaxBuilding2(maxBuilding, buildingIndexToMaxBuildingIndex, maxBuildingIndexToBuildingIndex, endLine[j]);
                    ++j;
                }
                //cout << maxBuilding[0] << ", " << val << endl;

                if (prevMax != maxBuilding[0]) {
                    prevMax = maxBuilding[0];
                    ret.push_back(std::make_pair(val, prevMax));
                }
            } else if (buildings[i][0] == buildings[endLine[j]][1]) {
                int val = buildings[i][0];
                while (i < len1 && buildings[i][0] == val) {
                    maxBuilding[buildingIndexToMaxBuildingIndex[i]] = buildings[i][2];
                    updateMaxBuilding1(maxBuilding, buildingIndexToMaxBuildingIndex, maxBuildingIndexToBuildingIndex, i);
                    ++i;
                }
                while (j < len1 && buildings[endLine[j]][1] == val) {
                    maxBuilding[buildingIndexToMaxBuildingIndex[endLine[j]]] = 0;
                    updateMaxBuilding2(maxBuilding, buildingIndexToMaxBuildingIndex, maxBuildingIndexToBuildingIndex, endLine[j]);
                    ++j;
                }
                //cout << maxBuilding[0] << ", " << val << endl;

                if (prevMax != maxBuilding[0]) {
                    prevMax = maxBuilding[0];
                    ret.push_back(std::make_pair(val, prevMax));
                }
            }
        }
        return ret;
    }

    private:
    void updateMaxBuilding1(vector<int>& maxBuilding, vector<int>& buildingIndexToMaxBuildingIndex, vector<int>& maxBuildingIndexToBuildingIndex, int buildingIndex) {
        int cur = buildingIndexToMaxBuildingIndex[buildingIndex];
        int up = (cur - 1) / 2;
        while (up >= 0) {
            if (maxBuilding[cur] > maxBuilding[up]) {
                //swap
                int temp = maxBuilding[cur];
                maxBuilding[cur] = maxBuilding[up];
                maxBuilding[up] = temp;
                int upIndex = maxBuildingIndexToBuildingIndex[up];
                buildingIndexToMaxBuildingIndex[buildingIndex] = up;
                buildingIndexToMaxBuildingIndex[upIndex] = cur;
                maxBuildingIndexToBuildingIndex[cur] = upIndex;
                maxBuildingIndexToBuildingIndex[up] = buildingIndex;
                cur = up;
                up = (cur - 1) / 2;
            } else {
                break;
            }
        }
    }

    void updateMaxBuilding2(vector<int>& maxBuilding, vector<int>& buildingIndexToMaxBuildingIndex, vector<int>& maxBuildingIndexToBuildingIndex, int buildingIndex) {
        int cur = buildingIndexToMaxBuildingIndex[buildingIndex];
        int down1 = cur * 2 + 1, down2 = cur * 2 + 2, len1 = maxBuilding.size();
        while (down2 < len1 || down1 < len1) {
            int down = cur;
            if (down1 < len1 && maxBuilding[down] < maxBuilding[down1]) {
                down = down1;
            }
            if (down2 < len1 && maxBuilding[down] < maxBuilding[down2]) {
                down = down2;
            }
            if (down == cur) {
                break;
            }
            //swap cur and down
            int temp = maxBuilding[cur];
            maxBuilding[cur] = maxBuilding[down];
            maxBuilding[down] = temp;
            int downIndex = maxBuildingIndexToBuildingIndex[down];
            buildingIndexToMaxBuildingIndex[buildingIndex] = down;
            buildingIndexToMaxBuildingIndex[downIndex] = cur;
            maxBuildingIndexToBuildingIndex[cur] = downIndex;
            maxBuildingIndexToBuildingIndex[down] = buildingIndex;
            cur = down;
            down1 = cur * 2 + 1;
            down2 = cur * 2 + 2;
        }
    }

};

class Solution2 {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        int len = buildings.size();
        if (len == 0) {
            return {};
        }
        //sort end time
        vector<int> endTime(len);
        for (int i = 0; i < len; ++i) {
            endTime[i] = i;
        }

        sort(endTime.begin(), endTime.end(), [buildings] (int i, int j) -> bool {
           return buildings[i][1] < buildings[j][1];
        });

        _Node *head = nullptr, *end = nullptr;
        unordered_map<int, _Node*> indexToNodePtr;
        int prevH = 0;
        vector<pair<int, int>> ret;

        for (int i = 0, j = 0; i < len || j < len; ) {
            int currentTime;
            bool needFindMax = false;
            if (i < len && j < len) {
                if (buildings[i][0] <= buildings[endTime[j]][1]) {
                    currentTime = buildings[i][0];
                } else {
                    currentTime = buildings[endTime[j]][1];
                }
            } else {
                currentTime = buildings[endTime[j]][1];
            }
            //check all time equal to endTime
            while (i < len && buildings[i][0] == currentTime) {
                //add buildings[i] to linked list
                _Node *p = new _Node(i);
                if (!head) {
                    //just add buildings[i]
                    head = end = p;
                } else {
                    if (buildings[i][2] <= buildings[head->m_index][2]) {
                        //add at the end
                        end->m_next = p;
                        p->m_prev = end;
                        end = p;
                    } else {
                        //add at the head
                        head->m_prev = p;
                        p->m_next = head;
                        head = p;
                    }
                }
                indexToNodePtr.emplace(i, p);
                ++i;
            }
            while (j < len && buildings[endTime[j]][1] == currentTime) {
                //remove buildings[j] from linked list
                int index = endTime[j];
                _Node *p = indexToNodePtr[index];
                if (p == head) {
                    needFindMax = true;
                    head = head->m_next;
                    if (!head) {
                        end = head;
                    } else {
                        head->m_prev = nullptr;
                    }
                } else {
                    p->m_prev->m_next = p->m_next;
                    if (p != end) {
                        p->m_next->m_prev = p->m_prev;
                    } else {
                    		end = p->m_prev;
                    }
                }
                delete p;
                ++j;
            }
            if (needFindMax) {
                int maxH = 0;
                _Node *maxNode = nullptr;
                for (_Node *p = head; p; p = p->m_next) {
                    if (buildings[p->m_index][2] > maxH) {
                        maxH = buildings[p->m_index][2];
                        maxNode = p;
                    }
                }
                if (maxNode && maxNode != head) {
                    //move maxNode to head
                    int index = head->m_index;
                    head->m_index = maxNode->m_index;
                    maxNode->m_index = index;
                    indexToNodePtr[head->m_index] = head;
                    indexToNodePtr[maxNode->m_index] = maxNode;
                }
            }
            int curH = head ? buildings[head->m_index][2] : 0;
            if (prevH != curH) {
                //output
                ret.push_back(make_pair(currentTime, curH));
                prevH = curH;
            }
        }
        return ret;
    }
    private:
    struct _Node{
    public:
        int m_index;
        _Node *m_prev, *m_next;
        _Node(int index) : m_index(index), m_prev(nullptr), m_next(nullptr) {}
    };
};

int main(int argc, char *argv[]) {
	Solution2 sol;

	vector<pair<int, int>> ret;
	int j = 10000;
	vector<vector<int>> buildings(j, vector<int>(3));

	for (int i = 0; i < j; ++i) {
		buildings[i][0] = i + 1;
		buildings[i][1] = 10001;
		buildings[i][2] = 10000 - i;
	}

	ret = sol.getSkyline(buildings);

	for (auto i : ret) {
		cout << i.first << ":" << i.second << endl;
	}
	return 0;
}
