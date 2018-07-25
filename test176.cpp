/*
 * test176.cpp
 *
 *  Created on: May 2, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

//The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
//Given an integer n, return all distinct solutions to the n-queens puzzle.
//Each solution contains a distinct board configuration of the n-queens' placement,
//where 'Q' and '.' both indicate a queen and an empty space respectively.

class Solution1 {
public:
    /*
     * @param n: The number of queens
     * @return: All distinct solutions
     */
    vector<vector<string>> solveNQueens(int n) {
        // write your code here
        if (n <= 0) {
            return {{}};
        }
        vector<vector<string>> ret;
        vector<string> res(n, string(n, '.'));
        vector<int> pos(n, 0); // position of each queen in its row
        int cur = 0; // @cur queen
        while (1) {
            if (pos[cur] == n) {
                //no choice for current queen, go back one more
                if (cur == 0) {
                    break;
                }
                pos[cur] = 0;
                --cur;
                res[cur].at(pos[cur]) = '.';
                ++pos[cur];
            } else {
                if (checkPosition(cur, pos)) {
                    //no conflict, go to next queen
                    res[cur].at(pos[cur]) = 'Q';
                    ++cur;
                    if (cur == n) {
                        //find a solution
                        ret.push_back(res);
                        --cur;
                        res[cur].at(pos[cur]) = '.';
                        ++pos[cur];
                    }
                } else {
                    ++pos[cur];
                }
            }
        }
        return ret;
    }
    private:
    bool checkPosition(int cur, const vector<int>& pos) {
        //check queens from 0 to cur, make sure it is OK
        //check column
        for (int i = 0; i < cur; ++i) {
            if (pos[i] == pos[cur]) {
                return false;
            }
        }
        //check diagonal
        for (int i = cur - 1, j = pos[cur] - 1; i >= 0 && j >= 0; --i, --j) {
            if (pos[i] == j) {
                return false;
            }
        }
        for (int i = cur - 1, j = pos[cur] + 1; i >= 0 && j < pos.size(); --i, ++j) {
            if (pos[i] == j) {
                return false;
            }
        }
        return true;
    }
};

//Follow up for N-Queens problem.
//Now, instead outputting board configurations, return the total number of distinct solutions.
class Solution {
public:
    /**
     * @param n: The number of queens.
     * @return: The total number of distinct solutions.
     */
    int totalNQueens(int n) {
        // write your code here
        if (n <= 0) {
            return 0;
        }
        vector<int> pos(n, 0); //position of each queen
        int cur = 0, ret = 0;
        while (1) {
            if (pos[cur] == n) {
                //back to cur-1
                if (cur == 0) {
                    break;
                }
                pos[cur] = 0;
                --cur;
                ++pos[cur];
            } else {
                if (checkPosition(cur, pos)) {
                    ++cur;
                    if (cur == n) {
                        //find a solution
                        ++ret;
                        --cur;
                        ++pos[cur];
                    }
                } else {
                    ++pos[cur];
                }
            }
        }
        return ret;
    }
    private:
    bool checkPosition(int cur, const vector<int>& pos) {
        for (int i = 0; i < cur; ++i) {
            if (pos[i] == pos[cur]) {
                return false;
            }
        }
        for (int i = cur - 1, j = pos[cur] - 1; i >= 0 && j >= 0; --i, --j) {
            if (pos[i] == j) {
                return false;
            }
        }
        for (int i = cur - 1, j = pos[cur] + 1; i >= 0 && j < pos.size(); --i, ++j) {
            if (pos[i] == j) {
                return false;
            }
        }
        return true;
    }

};
