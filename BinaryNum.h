#pragma once
#include "FixBinaryNum.h"
#include <cmath>
#include <iostream>
using namespace std;
class BinaryNum {
private:
	bool value[16];
	const int last_index = 15;

	void InverseCode() {
		if (this->value[0] == 1)
		{
			for (int i = 1; i < last_index + 1; i++) {
				if (this->value[i])
					value[i] = 0;
				else
					value[i] = 1;
			}
		}
	}	

	void Clear() {
		for (int i = 0; i < last_index + 1; i++) {
			this->value[i] = 0;
		}
	}

public:

	BinaryNum& operator++ () {
		for (int i = last_index; i > 0; i--) {
			if (this->value[i] == 1) {
				value[i] = 0;
				continue;
			}
			else {
				this->value[i] = 1;
				break;
			}
		}
		return *this;
	}

	BinaryNum(const BinaryNum& other) {
		for (int i = last_index; i >= 0; i--) {
			this->value[i] = other.value[i];
		}
	}

	BinaryNum()
	{
		for (int i = last_index; i >= 0; i--) {
			this->value[i] = 0;
		}
	}

	BinaryNum(int value) {
		if (value < 0) {
			this->value[0] = 1;
			value *= -1;
		}
		else
			this->value[0] = 0;
		for (int i = last_index; i >= 1; i--) {
			if (value / 2 != 0) {
				this->value[i] = value % 2;
				value /= 2;
			}
			else {
				this->value[i] = value;
				value = 0;
			}
		}
	}

	void PrintNum() const{
		for (int i = 0; i < last_index + 1; i++)
			cout << this->value[i];
		cout << ' ' << this->BinaryToInt() << endl;
	}

	
	BinaryNum SumInDirectCode(const BinaryNum& other) {
		int buf = 0;
		BinaryNum res;
		for (int i = last_index; i >= 0; i--) {
			buf += other.GetNum(i);
			buf += this->GetNum(i);
			if (buf % 2 == 0)
				res.SetNum(i, 0);
			else
				res.SetNum(i, 1);
			if (buf > 1)
				buf = 1;
			else
				buf = 0;
		}
		return res;
	}

	BinaryNum SumInInverseCode(const BinaryNum& other) {
		BinaryNum res, copy1(*this), copy2(other);
		int buf = 0;
		copy1.InverseCode();
		copy2.InverseCode();
		for (int i = last_index; i >= 0; i--) {
			buf += copy2.GetNum(i);
			buf += copy1.GetNum(i);
			if (buf % 2 == 0)
				res.SetNum(i, 0);
			else
				res.SetNum(i, 1);
			if (i == 0) {
				if (buf > 1) 
					++res;
			}
			else {
				if (buf > 1)
					buf = 1;
				else
					buf = 0;
			}
			if (res.value[0])
				res.InverseCode();
		}
		return res;		
	}

	int BinaryToInt() const{
		int res = 0;
		for (int i = last_index; i > 0; i--) {
			res += (this->GetNum(i) * pow(2, last_index - i));
		}
		if (this->value[0])
			res *= -1;
		return res;
	}

	BinaryNum SumInAdditionalCode(const BinaryNum& other) {
		BinaryNum res, copy1(*this), copy2(other);
		int buf = 0;
		if (copy1.value[0]) {
			copy1.InverseCode();
			++copy1;
		}
		if (copy2.value[0]) {
			copy2.InverseCode();
			++copy2;
		}
		for (int i = last_index; i >= 0; i--) {
			buf += copy2.GetNum(i);
			buf += copy1.GetNum(i);
			if (buf % 2 == 0)
				res.SetNum(i, 0);
			else
				res.SetNum(i, 1);
			if (buf > 1)
				buf = 1;
			else
				buf = 0;
			if (res.value[0]) {
				res.InverseCode();
				++res;
			}
		}
		return res;
	}

	BinaryNum Multiply(const BinaryNum& other) {
		BinaryNum res, multiplier(other), term;
		int buf = 0;
		if (multiplier.GetNum(0)) 
			buf++;
		if (this->GetNum(0))
			buf++;
		if (buf % 2 == 0) 
			res.SetNum(0, 0);
		else 
			res.SetNum(0, 1);
		buf = 0;
		for (int i = last_index; i > 0; i--)
		{
			if (!multiplier.value[i]) 
				buf++;
			else {
				for (int j = i; j > 0; j--)
					term.value[j] = this->value[j + buf];
				res = res.SumInDirectCode(term);
				term.Clear();
				buf++;
			}
		}
		return res;
	}

	BinaryNum& operator= (const BinaryNum& other) {
		for (int i = last_index; i >= 0; i--) {
			this->value[i] = other.value[i];
		}
		return *this;
	}

	bool operator>(const BinaryNum& other) const {
		if (this->BinaryToInt() > other.BinaryToInt())
			return true;
		else
			return false;
	}

	bool GetNum(int index) const {
		return this->value[index];
	}

	bool operator ==(const BinaryNum& other) {
		bool flag = true;
		for (int i = 0; i <= last_index; i++) {
			if (this->value[i] == other.GetNum(i))
				continue;
			else {
				flag = false;
				break;
			}
		}
		return flag;
	}

	BinaryNum Copy(int start_index, int end_index) const {
		BinaryNum res;
		for (int i = end_index; i >= start_index; i--) {
			res.value[res.len() - 1 - (end_index - i)] = this->value[i];
		}
		return res;
	}

	FixBinaryNum Divide (const BinaryNum &other) {
		FixBinaryNum res;
		BinaryNum dividend, copy(other);
		copy.value[0] = 1;
		int i = 1;
		dividend.Push_back(this->value[i]);
		while (other > dividend && i < 16) {
			dividend.Push_back(this->value[i]);
			i++;
		}
		if (i < 16) {
			res.Push_back(1);
			dividend = dividend.SumInAdditionalCode(copy);
			dividend.Push_back(this->value[i]);
		}
		else {
			for (int j = 10; j < 16; j++) {
				if (other > dividend) {
					res.SetNum(j, 0);
					dividend.Push_back(0);
				}
				else {
					res.SetNum(j, 1);
					dividend = dividend.SumInAdditionalCode(copy);
					dividend.Push_back(0);
				}
			}
			return res;
		}
		while (i < 16) {
			if (other > dividend) {
				res.Push_back(0);
				dividend.Push_back(this->value[i]);
				i++;
			}
			else {
				res.Push_back(1);
				dividend = dividend.SumInAdditionalCode(copy);
				dividend.Push_back(this->value[i]);
				i++;
			}
		}
		for (int j = 11; j < 16; j++) {
			if (other > dividend) {
				res.SetNum(j, 0);
				dividend.Push_back(0);
			}
			else {
				res.SetNum(j, 1);
				dividend = dividend.SumInAdditionalCode(copy);
				dividend.Push_back(0);
			}
		}
		return res;
	}

	int len() {
		return this->last_index + 1;
	}

	void Push_back(bool value) {
		for (int i = 2; i <= 15; i++) {
			this->value[i - 1] = this->value[i];
		}
		this->value[15] = value;
	}

	void SetNum(int index, bool value) {
		this->value[index] = value;
	}
};