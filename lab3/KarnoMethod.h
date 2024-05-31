#pragma once
#include "TruthTable.h"
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>


using namespace std;
class KarnoMethod {
private:
	string expression;
	string numeric_form;
	string minimizeDNF;
	string minimizeKNF;
	vector<vector<int>> table;
	string vars;
	string expressionSDNF;
	string expressionSKNF;	

	void ConverseToNum(string expression) {
		string res;
		int i = 0;
		while (expression[i] != ')') {
			if (expression[i] >= 'a' && expression[i] <= 'z')
				this->vars += expression[i];
			i++;
		}
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
		this->numeric_form = res;
	}

	string getVariable(char var, bool isNegative) {
		return isNegative ? "!" + string(1, var) : string(1, var);
	}

	string DelÑonstituents(int index_l, int index_r) {
		string res = this->minimizeDNF;
		if (res.size() - 1 != index_r)
			res.erase(index_l, index_r - index_l + 2);
		else
			res.erase(index_l - 1, index_r - index_l + 2);
		return res;
	}

	bool FindConstit(string to_find) {
		bool flag = false;
		for (int i = 1; i < numeric_form.size(); i++) {
			if (numeric_form[i - 1] == '(') {
				string for_comparison;
				while (numeric_form[i] != ')') {
					for_comparison += numeric_form[i];
					i++;
				}
				if (for_comparison == to_find)
					return true;
			}
		}
		return false;
	}

	void CreateTable() {
		vector<vector<int>> left_indexes = GenerateGrayCode(vars.size() / 2);
		vector<vector<int>> top_indexes = GenerateGrayCode(vars.size() - vars.size() / 2);
		for (int i = 0; i < left_indexes.size(); i++) {
			string buf;
			vector<int> res;
			for (int j = 0 ; j < left_indexes[i].size(); j++) {
				buf += to_string(left_indexes[i][j]);
			}
			for (int j = 0; j < top_indexes.size(); j++) {
				string to_find;
				to_find += buf;
				for (int k = 0; k < top_indexes[j].size(); k++) {
					to_find += to_string(top_indexes[j][k]);
				}
				if (FindConstit(to_find)) {
					res.push_back(1);
				}
				else
					res.push_back(0);
			}
			table.push_back(res);
		}
	}

	vector<vector<int>> GenerateGrayCode(int n) {
		int N = pow(2, n);
		vector<vector<int>> result(N, vector<int>(n));

		for (int i = 0; i < N; i++) {
			int num = i ^ (i >> 1);
			for (int j = n - 1; j >= 0; j--) {
				result[i][j] = (num & 1);
				num >>= 1;
			}
		}
		return result;
	}

	string CalculateDNF() {
		int rows = table.size();
		int cols = table[0].size();
		TabularMethod x(expressionSDNF);
		minimizeDNF = x.GetMinimize();
		vector<vector<bool>> visited(rows, vector<bool>(cols, false));
		set<string> terms;

		int numVars = 0;
		while ((1 << numVars) < max(rows, cols)) {
			numVars++;
		}

		for (int rowSize = rows; rowSize > 0; rowSize /= 2) {
			for (int colSize = cols; colSize > 0; colSize /= 2) {
				for (int i = 0; i < rows; i += rowSize) {
					for (int j = 0; j < cols; j += colSize) {
						if (!visited[i][j] && canBeGrouped(table, i, j, rowSize, colSize)) {
							string term;
							for (int k = 0; k < numVars; ++k) {
								if (rowSize == 1) {
									term += getVariable('A' + k, !(i & (1 << k))) + " ";
								}
								if (colSize == 1) {
									term += getVariable('A' + k + numVars, !(j & (1 << k))) + " ";
								}
							}
							terms.insert(term);
							for (int x = i; x < i + rowSize; ++x) {
								for (int y = j; y < j + colSize; ++y) {
									visited[x % rows][y % cols] = true;
								}
							}
						}
					}
				}
			}
		}
		return minimizeDNF;
	}

	bool canBeGrouped(const vector<vector<int>>& kmap, int row, int col, int rowSize, int colSize) {
		for (int i = 0; i < rowSize; ++i) {
			for (int j = 0; j < colSize; ++j) {
				if (!kmap[(row + i) % kmap.size()][(col + j) % kmap[0].size()]) {
					return false;
				}
			}
		}
		return true;
	}

	string CalculateKNF() {
		int rows = table.size();
		int cols = table[0].size();
		TabularMethod x(expressionSKNF);
		minimizeKNF = x.GetMinimize();
		vector<vector<bool>> visited(rows, vector<bool>(cols, false));
		set<string> terms;
		int numVars = 0;
		while ((1 << numVars) < max(rows, cols)) {
			numVars++;
		}
		for (int rowSize = rows; rowSize > 0; rowSize /= 2) {
			for (int colSize = cols; colSize > 0; colSize /= 2) {
				for (int i = 0; i < rows; i += rowSize) {
					for (int j = 0; j < cols; j += colSize) {
						if (!visited[i][j] && canBeGrouped(table, i, j, rowSize, colSize)) {
							string term;
							for (int k = 0; k < numVars; ++k) {
								if (rowSize == 1) {
									term += getVariable('A' + k, !(i & (1 << k))) + " ";
								}
								if (colSize == 1) {
									term += getVariable('A' + k + numVars, !(j & (1 << k))) + " ";
								}
							}
							terms.insert(term);
							for (int x = i; x < i + rowSize; ++x) {
								for (int y = j; y < j + colSize; ++y) {
									visited[x % rows][y % cols] = true;
								}
							}
						}
					}
				}
			}
		}

		return minimizeKNF;
	}

public:

	KarnoMethod(string expression) {
		this->expression = expression;
		TruthTable a(expression);
		expressionSDNF = a.SDNF();
		expressionSKNF = a.SKNF();
		ConverseToNum(expressionSDNF);
		CreateTable();
		ShowTable();
		this -> minimizeDNF = CalculateDNF();
		this->minimizeKNF = CalculateKNF();
	}

	void ShowTable() {
		for (int i = 0; i < table.size(); i++) {
			for (int j = 0; j < table[i].size(); j++) {
				cout << table[i][j] << ' ';
			}
			cout << endl;
		}
	}

	string GetMinimizeDNF() {
		return minimizeDNF;
	}

	string GetMinimizeKNF() {
		return minimizeKNF;
	}
};
