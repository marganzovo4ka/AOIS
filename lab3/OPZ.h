#pragma once
#include<iostream>
#include <stack>
using namespace std;

class OPZ {
private:
	string opz_form;

	int Prior(char a) {
		switch (a) {
		case '!': return 5;
		case '&': return 4;
		case '|': return 3;
		case '-':  return 2;
		case '~':  return 1;
		}
		return 0;
	}

	bool IsSign(char value) {
		if (value == '!' || value == '|' || value == '&' || value == '-' || value == '~')
			return true;
		return false;
	}

public:

	OPZ(string input) {
		stack<char> stack;
		for (int i = 0; i < input.length(); i++) {
			if (input[i] >= 'a' && input[i] <= 'z') {
				opz_form += input[i];
			}
			if (input[i] == '(') {
				stack.push(input[i]);
			}
			if (input[i] == ')') {
				while (stack.top() != '(' && !stack.empty()) {
					char buf = stack.top();
					if (buf == '-')
						opz_form += "->";
					else
						opz_form += buf;
					stack.pop();
				}
				stack.pop();
			}
			if (IsSign(input[i])) {
				while (!stack.empty() && Prior(stack.top()) >= Prior(input[i])) {
					char buf = stack.top();
					if (buf == '-')
						opz_form += "->";
					else
						opz_form += buf;
					stack.pop();
				}
				stack.push(input[i]);
			}
		}
		while (!stack.empty()) {
			char buf = stack.top();
			if (buf == '-')
				opz_form += "->";
			else
				opz_form += buf;
			stack.pop();
		}
	}

	string GetOPZ() {
		return opz_form;
	}
};