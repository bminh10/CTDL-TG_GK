#include <iostream>

#include <stack>
#include <queue>
using namespace std;



int getPriority(char op) {
	if (op == '^') {
		return 3;
	}
	if (op == '*' || op == '/') {
		return 2;
	}
	if (op == '+' || op == '-') {
		return 1;
	}
	return 0;
}


string infixToPostfix(char* str) {
	int len = strlen(str);
	stack<char> s;
	queue<char> q;

	for (int i = 0; i < len; i++) {
		if (isdigit(str[i])) {
			q.push(str[i]);
		}
		else if (str[i] == '(') {
			s.push(str[i]);
		}
		else if (str[i] == ')') {
			char op = s.top();
			s.pop();
			
			while (op != '(') {
				
				q.push(op);
				op = s.top();
				s.pop();
			}
		}
		else {
			if (str[i] != ' ') {
				if (!empty(s) && getPriority(str[i]) <= getPriority(s.top())) {
					
					q.push(s.top());
					s.pop();
				}
				s.push(str[i]);
			}
			
		}
	}

	while (!empty(s)) {
		q.push(s.top());
		s.pop();
	}



	string postfix = "";
	while (!empty(q)) {
		postfix += q.front();
		q.pop();
		if (!empty(q)) {
			postfix += " ";
		}
	}

	return postfix;
}



string infixToPrefix(char* str) {
	stack<char>s;
	int len = strlen(str);
	string prefix = "";
	for (int i = len - 1; i >= 0; i--) {
		if (isdigit(str[i])) {
			prefix += str[i];
			prefix += " ";
		}
		else if (str[i] == ')') {
			s.push(str[i]);
		}
		else if (str[i] == '(') {
			char op = s.top();
			s.pop();
			while (op != ')') {
				prefix += op;
				op = s.top();
				s.pop();
				
			}
		}
		else {
			if (str[i] != ' ') {
				if (!empty(s) && getPriority(str[i]) <= getPriority(s.top())) {
					prefix += s.top();
					
						prefix += " ";
					
					
					s.pop();
				}
				s.push(str[i]);
			}
		}
	}
	
	while (!empty(s)) {
		prefix += s.top();
		s.pop();
		
			prefix += " ";
		
		
	}
	



	int newLen = prefix.length();
	for (int i = 0; i < newLen/2; i++) {
		swap(prefix[i], prefix[newLen-1-i]);
	}

	return prefix;

}


int main() {

	char str[] = "(3+5)*(2-4)+(7/2)";
	string res = infixToPostfix(str);
	cout << res << endl;

	string res2 = infixToPrefix(str);
	cout << res2 << endl;
	return 0;
}