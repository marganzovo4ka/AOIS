#pragma once
#include "CalculationMethod.h"

class TabularMethod : CalculationMethod {
private:
	vector<vector<bool>> table;

	string ConverseToNum() {
		string res;
		for (int i = 0; i < expression.length(); i++) {
			res += '(';
			while (expression[i] != ')') {
				if (expression[i] >= 'a' && expression[i] <= 'z')
					res += '1';
				else if (expression[i] == '-' || expression[i] == '!') {
					res += '0';
					i = i + 2;
					continue;
				}
				i++;
			}
			if (expression[i] == ')')
				res += ')';
		}
		return res;
	}

	void CreatTable() {
		string buf = ConverseToNum();
		vector<bool> column;
		for (int k = 0; k < CountÑonstituents(minimize); k++) {
			for (int j = 0; j < buf.size(); j++) {
				int i = k * (CountVars() + 2);
				bool flag = true;
				while (minimize[i] != ')') {
					if (minimize[i] != '(' && flag != false) {
						if (minimize[i] == 'x') {
							i++;
							j++;
							continue;
						}
						if (minimize[i] != buf[j])
							flag = false;
					}
					i++;
					j++;
				}
				if (flag)
					column.push_back(1);
				else
					column.push_back(0);
			}
			table.push_back(column);
			column.clear();
		}
	}


	void Minimize() {
		for (int i = 0; i < table.size(); i++) {
			bool flag = true;
			for (int j = 0; j < table[i].size(); j++) {
				if (table[i][j]) {
					flag = true;
					for (int k = 0; k < table.size(); k++) {
						if (k != i && table[k][j] == 1) {
							flag = false;
							break;
						}
					}
					if (flag)
						break;
					else
						continue;
				}
			}
			if (!flag)
				minimize.erase(i * (CountÑonstituents(minimize) + 2), CountVars() + 2);
		}
	}

public:
	TabularMethod(string expression) {
		for (char c : expression) if (c != ' ') this->expression += c;
		int i = 0;
		while (this->expression[i] != ')')
			i++;
		if (this->expression[i + 1] == '|')
			SDNF = 1;
		this-> minimize = ConverseToNum();
		PrintVars();
		this->minimize = Gluing(this->minimize);
			CreatTable();
		Minimize();
		ConverseToStr(minimize);
	}

	void ShowTable() {
		for (int i = 0; i < table.size(); i++) {
			for (int j : table[i]) {
				cout << j << ' ';
			}
			cout << endl;
		}
	}

	string GetMinimize() {
		return minimize;
	}
};