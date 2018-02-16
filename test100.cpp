/*
 * test100.cpp
 *
 *  Created on: Feb 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <vector>

using namespace std;

//given an integer array, only one integer appears odd times, all other integers appear even times. find that integer that appears odd times
int findInteger1(const vector<int> vec) {
	//using exclusive OR operation. All integers apprearing even numbers will turn to 0
	int ans = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		ans ^= vec[i];
	}
	return ans;
}

//given an integer array, only two integers (int1, int2) appear odd times, all other integers appear even times. find the integers that appear odd times
void findInteger2(const vector<int> vec, vector<int>& num) {
	//using exclusive OR operation.
	int ans = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		ans ^= vec[i];
	}
	//ans is int1 ^ int2
	//since int1 != int2, ans must not be 0. So at least one bit position of ans is 1 (which means on that position, int1 is 1 and int2 is 0 OR int1 is 0 and int2 is 1)
	//this way, we differenciate int1 and int2
	//for all integers in the array that there is 1 on that position, only one appears odd times, all the other appears even times. So exclusive OR all those integers to get the integer that appears once
	int pos = 0;
	while (!((ans >> pos) & 1)) {
		++pos;
	}
	num[0] = 0;
	for (size_t i = 0; i < vec.size(); ++i) {
		if ((vec[i] >> pos) & 1) {
			num[0] ^= vec[i];
		}
	}
	//num[0] is one integer that appears odd times
	num[1] = num[0] ^ ans;
	return;
}

class BaseKNum {
public:
	BaseKNum(int base) : m_base(base) {};
	BaseKNum(int base, int Num) : m_base(base) {
		m_baseKNum.clear();
		m_baseKNum.insert(m_baseKNum.begin(), 1, Num % m_base);
		Num = Num / m_base;
		while (Num) {
			m_baseKNum.insert(m_baseKNum.begin(), 1, Num % m_base);
			Num = Num / m_base;
		}
	};
	~BaseKNum() {};
	int getInt() const {
		int ans = 0;
		for (size_t i = 0; i < m_baseKNum.size(); ++i) {
			ans = ans * m_base + m_baseKNum[i];
		}
		return ans;
	};

	int getBase() const {
		return m_base;
	};

	int getDigitAtPos(int pos) const {
		if (pos < m_baseKNum.size()) {
			return m_baseKNum[m_baseKNum.size() - 1 - pos];
		} else {
			return 0;
		}
	};

	void setDigitAtPos(int pos, int digit) {
		if (pos < m_baseKNum.size()) {
			m_baseKNum[m_baseKNum.size() - 1 - pos] = digit;
		} else {
			while (pos >= m_baseKNum.size()) {
				m_baseKNum.insert(m_baseKNum.begin(), 1, 0);
			}
			m_baseKNum[0] = digit;
		}
	};

	//get most significant position
	int getMSP() const {
		return m_baseKNum.size();
	};

	BaseKNum& operator^ (const BaseKNum& other) {
		int pos = 0, digit1, digit2;
		if (other.getBase() != m_base) {
			//change to m_base
			int val = other.getInt();
			BaseKNum num1(m_base, val);
			int msp = max(getMSP(), num1.getMSP());
			while (pos <= msp) {
				digit1 = num1.getDigitAtPos(pos);
				digit2 = getDigitAtPos(pos);
				setDigitAtPos(pos, (digit1 + digit2) % m_base);
				++pos;
			}
		} else {
			int msp = max(getMSP(), other.getMSP());
			while (pos <= msp) {
				digit1 = other.getDigitAtPos(pos);
				digit2 = getDigitAtPos(pos);
				setDigitAtPos(pos, (digit1 + digit2) % m_base);
				++pos;
			}
		}
		return *this;
	};

private:
	vector<int> m_baseKNum;
	int m_base; //base

	BaseKNum();
};

//given an integer array and integer K > 1. one integer appears once, all the others appear exactly K times. Find the integer that appears once
int findInteger3(const vector<int> vec, int K) {
	//similar to base 2 exclusive OR, if a number appears multiple of K times, its base K representation will become 0 if apply base K exclusive OR operation
	BaseKNum ans(K);
	//cout << "ans: " << ans.getInt() << endl;
	for (size_t i = 0; i < vec.size(); ++i) {
		BaseKNum num1(K, vec[i]);
		//cout << "num1: " << num1.getInt() << endl;
		ans = ans ^ num1;
		//cout << "ans ^ num1: " << ans.getInt() << endl;
	}
	return ans.getInt();
}

int main(int argc, char* argv[]) {
	vector<int> vec({3, 0, 2, 3, 2, 3, 4, 4, 5, 4, 0, 2, 0}), num(2);
	//findInteger2(vec, num);
	//cout << "two numbers appearing odd times: " << num[0] << ", " << num[1] << endl;
	cout << "the number appearing once: " << findInteger3(vec, 3) << endl;

    return 0;
}




