/*
 * test161.cpp
 *
 *  Created on: April 26, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//Implement a stack with min() function, which will return the smallest number in the stack.
//It should support push, pop and min operation all in O(1) cost.
//min operation will never be called if there is no number in the stack.

class MinStack {
public:
    MinStack() {
        // do intialization if necessary
    }

    /*
     * @param number: An integer
     * @return: nothing
     */
    void push(int number) {
        // write your code here
        if (value.empty()) {
            minValue.push(number);
        } else {
            int topValue = minValue.top();
            if (number < topValue) {
                minValue.push(number);
            } else {
                minValue.push(topValue);
            }
        }
        value.push(number);
    }

    /*
     * @return: An integer
     */
    int pop() {
        // write your code here
        if (value.empty()) {
            return INT32_MIN;
        }
        minValue.pop();
        int val = value.top();
        value.pop();
        return val;
    }

    /*
     * @return: An integer
     */
    int min() {
        // write your code here
        return minValue.top();
    }
    private:
    stack<int> value, minValue;
};
