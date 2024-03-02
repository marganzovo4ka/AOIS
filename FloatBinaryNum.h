#pragma once
#include "BinaryNum.h"
class FloatBinaryNum {
private:
	bool value[32];
	const int last_index = 31;	

	void IncreseOneByIndex(int index) {
		for (int i = index; i > 0; i--) {
			if (this->value[i] == 1)
				this->value[i] = 0;
			else {
				this->value[i] = 1;
				break;
			}
		}
	}
	void Clear() {
		for (int i = 0; i < last_index + 1; i++)
			value[i] = 0;
	}

public:
	FloatBinaryNum(double value) {
		this->Clear();
		for (int i = 0; i < 127; i++) 
			this->IncreseOneByIndex(8);
		
		if (value < 0) {
			this->value[0] = 1;
			value *= -1;
		}
		else
			this->value[0] = 0;
		int whole_part = value;
		BinaryNum x(whole_part);
		double fraction = value - whole_part;
		int i = 1;
		while (x.GetNum(i) == 0) {
			i++;
		}
		i++;

		for (int j = 9; j < 32; j++) {
			if (i < x.len()) {
				this->value[j] = x.GetNum(i);
				i++;
				this->IncreseOneByIndex(8);
			}
			else {
				fraction *= 2;
				if (fraction >= 1) {
					this->value[j] = 1;
					fraction -= 1;
				}
				else 
					this->value[j] = 0;				
			}
		}
	}

	FloatBinaryNum() {
		this->Clear();
	}

	BinaryNum Copy(int start_index, int end_index) const{
		BinaryNum res;
		for (int i = end_index; i >= start_index; i--) {
			res.SetNum(res.len() - 1 - (end_index - i), this->value[i]);
		}
		return res;
	}

	void PrintNum() const {
		for (int i = 0; i < last_index + 1; i++)
			cout << this->value[i];
		cout << ' ' << this->BinaryToFloat() << endl;
	}

	FloatBinaryNum Sum(const FloatBinaryNum& other) {
		BinaryNum exp1, exp2;
		FloatBinaryNum res;
		exp1 = this->Copy(1, 8);
		exp2 = other.Copy(1, 8);
		int buf = 0;
		if (exp1 > exp2) {
			while (exp1 > exp2)
			{
				++exp2;
				buf++;
			}
			for (int i = 1; i <= 8; i++) {
				res.value[i] = this->value[i];
			}
			FloatBinaryNum bias(other);
			bias.Bias(buf);
			for (int i = last_index; i >= 9; i--) {
				buf += this->value[i];
				buf += bias.GetValue(i);
				if (buf % 2 == 1)
					res.value[i] = 1;
				else
					res.value[i] = 0;
				if (buf > 1)
					buf = 1;
				else
					buf = 0;
			}
			if (buf == 1)
				res.Bias(1);
		}
		else if(exp2 == exp1){
			for (int i = 1; i <= 8; i++) {
				res.value[i] = this->value[i];
			}
			res.IncreseOneByIndex(8);
			for (int i = last_index; i >= 10; i--) {
				buf += this->value[i-1];
				buf += other.GetValue(i-1);
				if (buf % 2 == 1)
					res.value[i] = 1;
				else
					res.value[i] = 0;
				if (buf > 1)
					buf = 1;
				else
					buf = 0;
			}
			if (buf == 1)
				res.Bias(1);
		}
		else {
			while (exp2 > exp1)
			{
				++exp1;
				buf++;
			}
			for (int i = 1; i <= 8; i++) {
				res.value[i] = other.value[i];
			}
			FloatBinaryNum bias(*this);
			bias.Bias(buf);
			for (int i = last_index; i >= 9; i--) {
				buf += bias.value[i];
				buf += other.GetValue(i);
				if (buf % 2 == 1)
					res.value[i] = 1;
				else
					res.value[i] = 0;
				if (buf > 1)
					buf = 1;
				else
					buf = 0;
			}
			if (buf == 1)
				res.Bias(1);
		}
		return res;
	}

	bool GetValue(int index) const{
		return this->value[index];
	}

	double BinaryToFloat() const{
		BinaryNum exp;
		exp = this->Copy(1, 8);
		double res = 0;
		res += 1;
		for (int i = 9; i < 32; i++) {
			res += (this->value[i] * pow(2, 8 - i));
		}
		res = res * pow(2, (exp.BinaryToInt() - 127));
		if (this->value[0])
			res *= -1;
		return res;
	}

	void Bias(int count) {
		if (count == 0)
			return;
		for (int i = last_index; i > 8+count; i--) 
			this->value[i] = this->value[i - count];
		this->value[count + 8] = 1;
		for (int i = count + 8 - 1; i > 8; i--)
			this->value[i] = 0;
	}

	FloatBinaryNum& operator= (const FloatBinaryNum& other) {
		for (int i = last_index; i >= 0; i--) {
			this->value[i] = other.value[i];
		}
		return *this;
	}
};