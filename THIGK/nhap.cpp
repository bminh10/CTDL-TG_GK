#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

//output * + 3 4 - 5 / 6 2

int getPriority(char op) {
	if (op=='^') {
		return 3;
	}
	if (op=='*' || op == '/') {
		return 2;
	}
	if (op=='+'|| op=='-') {
		return 1;
	}
	return 0;
}


string infixToPrefix(char* str) {
	string prefix = "";
	stack<char> a;
	int len = strlen(str);
	for (int i = len - 1; i >= 0; i--) {
		if (isdigit(str[i])) {
			prefix += str[i];
			prefix += ' ';
		}
		else if (str[i] == ')') {
			a.push(str[i]);
		}
		else if (str[i] == '(') {
			char op = a.top();
			a.pop();
			while (op != ')') {
				prefix += op;
				prefix += ' ';
				op = a.top();
				a.pop();
			}
		}
		else {
			if (str[i] != ' ') {
				if (!empty(a) && getPriority(str[i]) <= getPriority(a.top())) {
					prefix += a.top();
					prefix += ' '; //! khong duoc viet la prefix += a.top() + ' '; vi do la cong ma ascii cua khoang trang vo
					a.pop();
				}

				a.push(str[i]);
			}
		
		}

	}

	while (!empty(a)) {
		prefix += a.top();
		if (!empty(a)) {
			prefix += ' ';
		}
		a.pop();
	}
	int newLen = prefix.length();

	for (int i = 0; i < newLen / 2; i++) {
		swap(prefix[i], prefix[newLen - 1 - i]);
	}

	return prefix;


}

//infix -> postfix
//8 2 + 3 1 - * 2 /
//cach 1: strtok
int getPriority(char *op) {
	if (*op == '^') {
		return 3;
	}
	if (*op == '/' || *op == '*') {
		return 2;
	}
	if (*op == '+' || *op == '-') {
		return 1;
	}
	return 0;
}
char* infixToPostfix(char* s) {
	stack<char*> a;
	queue<char*> q;

	int len = strlen(s);
	
	char* p = strtok(s," ");
	while (p != nullptr) {
		if (isdigit(*p)) {
			q.push(p);
		}
		else if (*p == '(') {
			a.push(p);
		}
		else if (*p == ')') {
			char* op = a.top();
			a.pop();
			while (*op != '(') {
				q.push(op);
				op = a.top();
				a.pop();
			}
		}
		else {
			if (!empty(a) && getPriority(p) <= getPriority(a.top())) {
				q.push(a.top());
				a.pop();
			}
			a.push(p);
		}

		p = strtok(NULL, " ");
	}

	while (!empty(a)) {
		q.push(a.top());
		a.pop();
	}

	char* temp = new char[len + 1];
	temp[0] = '\0';

	while(!empty(q)){
		strcat(temp, q.front());
		q.pop();
		if (!empty(q)) {
			strcat(temp, " ");

		}
	}
	return temp;
}
//cach 2 duyet tuan tu
int slen(char* s) {
	int len = 0;
	while (s[len] != '\0') {
		len++;
	}
	return len;
}


string infixToPostfix2(char* s) {

	int len = strlen(s);

	string postfix = "";
	stack<char>a;
	queue<char>b;

	for (int i = 0; i < len; i++) {
		if (isdigit(s[i])) {
			b.push(s[i]);
		}
		else if (s[i] == '(') {
			a.push(s[i]);
		}
		else if (s[i] == ')') {
			char op = a.top();
			a.pop();
			while (op != '(') {
				b.push(op);
				op = a.top();
				a.pop();
			}
		}
		else {
			if (s[i] != ' ') {
				if (!empty(a) && getPriority(s[i]) <= getPriority(a.top())) {
					b.push(a.top());
					a.pop();
				}

				a.push(s[i]);
			}
			
		}

	}

	while (!empty(a)) {
		b.push(a.top());
		a.pop();
	}


	while (!empty(b)) {
		postfix += b.front();
		b.pop();
		if (!empty(b)) {
			postfix += " ";
		}
	}

	return postfix;
}




int main() {
	char str[] = "(3 + 4) * (5 - (6 / 2))";
	char str2[] = "( 8 + 2 ) * ( 3 - 1 ) / 2";
	
	/*string res = infixToPrefix(str);
	cout << res << endl;

	char* res2 = infixToPostfix(str2);
	cout << res2 << endl;*/

	string res3 = infixToPostfix2(str2);
	cout << res3 << endl;
	/*delete[] res2;*/
	return 0;
}