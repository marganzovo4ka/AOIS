#pragma once
#include "BinaryNum.h"
#include <iostream>
using namespace std;

class FixBinaryNum{
private:

	bool value[16];
	int fix_point = 5;
	const int last_index = 15;

	void Clear() {
		for (int i = 0; i < len(); i++)
			this->SetNum(i, 0);
	}

public:
	FixBinaryNum() {
		Clear();
	}

	void PrintNum() {
		for (int i = 0; i < len(); i++) {
			cout << this->GetNum(i);
		}
		cout << ' ' << FixBinaryToFloat() << endl;
	}
	double FixBinaryToFloat() {
		double res = 0;
		for (int i = 1; i < this->len(); i++) {
			res += this->GetNum(i) * pow(2, len() - i - 1 - fix_point);
		}
		if (this->GetNum(0))
			res *= -1;
		return res;
	}

	void Push_back(bool value) {
		for (int i = 2; i <= 10; i++) {
			this->SetNum(i - 1, this->GetNum(i));
		}
		this->SetNum(10, value);
	}

	int len() {
		return this->last_index + 1;
	}


	void SetNum(int index, bool value) {
		this->value[index] = value;
	}

	bool GetNum(int index) const {
		return this->value[index];
	}
	
	FixBinaryNum& operator= (const FixBinaryNum& other) {
		for (int i = last_index; i >= 0; i--) {
			this->value[i] = other.GetNum(i);
		}
		return *this;
	}
};