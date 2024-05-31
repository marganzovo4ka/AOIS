#pragma once
#include<vector>
#include <string>
#include "OPZ.h"
#include "TabularMethod.h"

class TruthTable {
private:
	vector<vector<bool>> table;
	string expression;
	string vars;

	int CountVars() {
		for (int i = 0; i < expression.length(); i++)
			if (expression[i] >= 'a' && expression[i] <= 'z') {
				if (vars.find(expression[i]) != std::string::npos)
					continue;
				vars += expression[i];
			}
		return vars.size();
	}

	void CreatTable() {
		int count_start_columns = CountVars();
		for (int i = 1; i <= count_start_columns; i++) {
			int j = 0;
			vector<bool> vec;
			while (j != pow(2, count_start_columns)) {
				for (int k = 0; k < pow(2, count_start_columns - i); k++) {
					vec.push_back(0);
					j++;
				}
				for (int k = 0; k < pow(2, count_start_columns - i); k++) {
					vec.push_back(1);
					j++;
				}
			}
			table.insert(table.begin() + (i - 1), vec);
		}
	}

	bool IsSign(char value) {
		if (value == '!' || value == '|' || value == '&' || value == '-' || value == '~')
			return true;
		return false;
	}

	int FindIndex(char var) {
		for (int i = 0; i < vars.size(); i++)
			if (var = vars[i])
				return i;
	}

	void Inverse(vector<bool>& column) {
		for (int i = 0; i < column.size(); i++) {
			column[i] = !column[i];
		}
	}

	void Implication(vector<bool>& column1, vector<bool>& column2) {
		for (int i = 0; i < column1.size(); i++) {
			if (column1[i] && !column2[i])
				column1[i] = 0;
			else
				column1[i] = 1;
		}
	}

	void Equivalence(vector<bool>& column1, vector<bool>& column2) {
		for (int i = 0; i < column1.size(); i++) {
			if (column1[i] == column2[i])
				column1[i] = 1;
			else
				column1[i] = 0;
		}
	}

	void Conjunction(vector<bool>& column1, vector<bool>& column2) {
		for (int i = 0; i < column1.size(); i++) {
			if (column1[i] && column2[i])
				column1[i] = 1;
			else
				column1[i] = 0;
		}
	}

	void Disjunction(vector<bool>& column1, vector<bool>& column2) {
		for (int i = 0; i < column1.size(); i++) {
			if (column1[i] || column2[i])
				column1[i] = 1;
			else
				column1[i] = 0;
		}
	}

	void Calculate() {
		stack<vector<bool>> stack;
		for (int i = 0; i <= expression.size(); i++)
		{
			vector<bool> first_el, second_el;
			if (expression[i] >= 'a' && expression[i] <= 'z') {
				for (int j = 0; j < vars.size(); j++)
					if (expression[i] == vars[j])
						stack.push(table[j]);
			}
			if (IsSign(expression[i]))
			{
				if (expression[i] == '!') {
					first_el = stack.top();
					stack.pop();
					Inverse(first_el);
					stack.push(first_el);
					continue;
				}
				first_el = stack.top();
				stack.pop();
				second_el = stack.top();
				stack.pop();
				switch (expression[i])
				{
				case '-':
					Implication(first_el, second_el);
					stack.push(first_el);
					break;
				case '&':
					Conjunction(first_el, second_el);
					stack.push(first_el);
					break;
				case '|':
					Disjunction(first_el, second_el);
					stack.push(first_el);
					break;
				case '~':
					Equivalence(first_el, second_el);
					stack.push(first_el);
					break;
				}
			}
		}
		table.push_back(stack.top());

	}

public:

	TruthTable(string expression) {
		OPZ a(expression);
		this->expression = a.GetOPZ();
		CreatTable();
		Calculate();
	}

	void Print() {
		for (int i = 0; i < table.size() - 1; i++) {
			cout << vars[i] << '\t';
			for (int j : table[i]) {
				cout << j << ' ';
			}
			cout << endl;
		}
		cout << ' ' << '\t';
		for (int j : table[table.size() - 1]) {
			cout << j << ' ';
		}
	}

	string GerExpression() {
		return this->expression;
	}



	string SKNF() {
		string res;
		for (int i = 0; i < table[table.size() - 1].size(); i++) {
			if (table[table.size() - 1][i])
				continue;
			res += '(';
			for (int j = 0; j < table.size() - 1; j++) {
				if (table[j][i])
					res += '-';
				res += vars[j];
				if (j != table.size() - 2)
					res += '|';
			}
			res += ")&";
		}
		res.erase(res.size() - 1, 1);
		return res;
	}

	string SDNF() {
		string res;
		for (int i = 0; i < table[table.size() - 1].size(); i++) {
			if (!table[table.size() - 1][i])
				continue;
			res += '(';
			for (int j = 0; j < table.size() - 1; j++) {
				if (!table[j][i])
					res += '-';
				res += vars[j];
				if (j != table.size() - 2)
					res += '&';
			}
			res += ")|";
		}
		if (!res.empty())
			res.erase(res.size() - 1, 1);
		return res;
	}

	string NumericForm() {
		string res;
		res += '(';
		for (int i = 0; i < table[table.size() - 1].size(); i++) {
			if (table[table.size() - 1][i])
				continue;
			res += to_string(i);
			res += ',';
		}
		res.erase(res.size() - 1, 1);
		res += ")&\n";
		res += '(';
		for (int i = 0; i < table[table.size() - 1].size(); i++) {
			if (!table[table.size() - 1][i])
				continue;
			res += to_string(i);
			res += ',';
		}
		if (!res.empty() && res[res.size() - 1] != '(')
			res.erase(res.size() - 1, 1);
		res += ")|";
		return res;
	}


	int IndexForm() {
		int res = 0;
		for (int i = 0; i < table[table.size() - 1].size(); i++) {
			if (table[table.size() - 1][i])
		res += pow(2, (table[table.size() - 1].size() - i - 1));
		}
		return res;
	}

	vector<bool> GetRes() {
		return table[table.size() - 1];
	}
};