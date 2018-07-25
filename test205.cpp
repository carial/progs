/*
 * test205.cpp
 *
 *  Created on: May 28, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input:
11110
11010
11000
00000

Output: 1
Example 2:

Input:
11000
11000
00100
00011

Output: 3
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        if (rows == 0) {
            return 0;
        }
        int columns = grid[0].size();
        if (columns == 0) {
            return 0;
        }
        unordered_set<int> visited;
        int i = 0, j = 0;
        stack<int> pos;
        int total = 0;
        while (i < rows) {
            if (grid[i][j] == '1' && visited.find(i * columns + j) == visited.end()) {
                //new position
                pos.push(i * columns + j);
                visited.insert(i * columns + j);
                ++total;
                while (!pos.empty()) {
                    int curPos = pos.top();
                    int k = curPos / columns, l = curPos % columns;
                    pos.pop();
                    //check neighbors
                    if (l > 0 && grid[k][l - 1] == '1' && visited.find(curPos - 1) == visited.end()) {
                        pos.push(curPos - 1);
                        visited.insert(curPos - 1);
                    }
                    if (l < columns - 1 && grid[k][l + 1] == '1' && visited.find(curPos + 1) == visited.end()) {
                        pos.push(curPos + 1);
                        visited.insert(curPos + 1);
                    }
                    if (k > 0 && grid[k - 1][l] == '1' && visited.find(curPos - columns) == visited.end()) {
                        pos.push(curPos - columns);
                        visited.insert(curPos - columns);
                    }
                    if (k < rows - 1 && grid[k + 1][l] == '1' && visited.find(curPos + columns) == visited.end()) {
                        pos.push(curPos + columns);
                        visited.insert(curPos + columns);
                    }
                }
            }
            ++j;
            if (j == columns) {
                j = 0;
                ++i;
            }
        }
        return total;
    }
};
