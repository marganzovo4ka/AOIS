#pragma once
#include "TruthTable.h"

using namespace std;

class CalculationMethod {
protected:
	string expression;
	bool SDNF = 0;	
	string minimize;
	string vars;

	void PrintVars() {
		int i = 0;
		while (expression[i] != ')') {
			if (expression[i] >= 'a' && expression[i] <= 'z')
				vars += expression[i];
			i++;
		}
	}


	void ConverseToNum() {
		string res;
		for (int i = 0; i < expression.length(); i++) {
			res += '(';
			while (expression[i] != ')') {
				if (expression[i] >= 'a' && expression[i] <= 'z')
					res += '1';
				else if (expression[i] == '!' || expression[i] == '-') {
					res += '0';
					i = i + 2;
					continue;
				}
				i++;
			}
			if (expression[i] == ')')
				res += ')';
		}
		this->minimize = res;
	}

	void ConverseToStr(string num_form) {
		string res;
		int j = 0;
		for (int i = 1; i < num_form.length(); i++) {
			res += '(';
			while (num_form[i] != ')') {
				
				if (num_form[i] == '0') {
					if (res[res.size() - 1] >= 'a' && res[res.size() - 1] <= 'z') 
						if (SDNF)
							res += '&';
						else
							res += '|';
					res += '!';
					res += vars[j];
				}
				else if (num_form[i] == '1') {
					if (res[res.size() - 1] >= 'a' && res[res.size() - 1] <= 'z') {
						if (SDNF)
							res += '&';
						else
							res += '|';
					}
					res += vars[j];
				}
				j++;
				i++;
			}
			if (num_form[i] == ')'){
				j = 0;
				i++;
				res += ')';
				if (i < num_form.length()) {
					if (SDNF)
						res += '|';
					else
						res += '&';
				}
			}
				
		}
		this->minimize = res;
	}

	int CountVars() {
		int i = 0;
		int count = 0;
		while (expression[i] != ')') {
			i++;
			if (expression[i] >= 'a' && expression[i] <= 'z')
				count++;
		}
		return count;
	}

	int CountÑonstituents(string expression) {
		int count = 0;
		for (int i = 0; i < expression.size(); i++) {
			if (expression[i] == '(')
				count++;
		}
		return count;
	}


	string DelÑonstituents(int index_l, int index_r) {
		string res = this->minimize;
		if (res.size()-1 != index_r) 
			res.erase(index_l, index_r - index_l + 2);
		else
			res.erase(index_l - 1, index_r - index_l + 2);
		return res;
	}

	string Gluing(string num_form) {
		string res;
		vector<vector<char>> table;
		string used_index;
		vector<char> column;
		for (int i = 0; i < num_form.size(); i++) {

			if (num_form[i] == ')') {
				bool flag = true;
				for (int j = 0; j < table.size(); j++) {
					if (column == table[j]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					table.push_back(column);
					column.clear();
				}
				else
					column.clear();

			}
			else if (num_form[i] != '(')
				column.push_back(num_form[i]);
		}
		int count_vars = 0;

		for (int i = 0; i < table.size() - 1; i++) {
			for (int j = i + 1; j < table.size(); j++) {
				int considences = 0;
				int count_x = 0;
				for (int k = 0; k < table[i].size(); k++) {
					if (table[i][k] == table[j][k] && table[i][k] != 'x')
						considences++;
					if (table[i][k] == 'x' && table[j][k] != 'x') {
						considences = 0;
						break;
					}
					if (table[i][k] == 'x')
						count_x++;
				}
				if (considences >= table[i].size() - 1 - count_x) {
					if (used_index.find(to_string(i)) == string::npos)
						used_index += to_string(i);
					if (used_index.find(to_string(j)) == string::npos)
						used_index += to_string(j);
					res += '(';
					for (int k = 0; k < table[i].size(); k++) {
						if (table[i][k] == table[j][k])
							res += table[j][k];
						else
							res += 'x';
					}
					res += ')';
				}
			}
		}
		for (int i = 0; i < table.size(); i++) {
			if (used_index.find(to_string(i)) == string::npos) {
				res += '(';
				for (int j = 0; j < table[i].size(); j++)
					res += table[i][j];
				res += ')';
			}
		}
		if (num_form == res)
			return res;
		else
			return Gluing(res);
	}

public:
	CalculationMethod(string expression) {
		for (char c : expression) if (c != ' ') this->expression += c;
		int i = 0;
		while (this->expression[i] != ')')
			i++;
		if (this->expression[i + 1] == '|')
			SDNF = 1;
		ConverseToNum();
		PrintVars();
		if (vars.size() == 1)
			minimize = expression;
		else {
			ConverseToStr(Gluing(this->minimize));
			TruthTable a(this->minimize);
			if (CountÑonstituents(this->minimize) != 1) {
				string to_check;
				int index_l, index_r;
				for (int j = 0; j < minimize.size(); j++) {
					if (minimize[j] == '(')
						index_l = j;
					if (minimize[j] == ')') {
						index_r = j;
						to_check = DelÑonstituents(index_l, index_r);
						TruthTable b(to_check);
						if (b.GetRes() == a.GetRes()) {
							minimize = to_check;
							j = index_l - 1;
						}
					}
				}
			}
		}
	}

	CalculationMethod() {

	}

	

	void Show() {
		cout << minimize << endl;
	}

	string GetMinimize() {
		return minimize;
	}
};