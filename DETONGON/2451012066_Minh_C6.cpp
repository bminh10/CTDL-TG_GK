#include <iostream>
#include <stack>
using namespace std;


struct Node {
	char info;
	Node* left, * right;
};

void init(Node*& root) {
	root = nullptr;
}

Node* createNodeLa(char op) {
	Node* p = new Node();
	p->info = op;
	p->left = nullptr;
	p->right = nullptr;
	return p;
}



void createTree(char op, stack<Node*>& NS) {
	Node* p = new Node();
	p->info = op;

	Node* NStop = NS.top();
	NS.pop();
	Node* NSbot = NS.top();
	NS.pop();

	p->right = NStop;
	p->left = NSbot;

	NS.push(p);

}

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

Node* createRoot(char* str) {
	int len = strlen(str);
	stack<char>CS;
	stack<Node*>NS;
	for (int i = 0; i < len; i++) { 
		if (isdigit(str[i])) {
			Node* tmp = createNodeLa(str[i]);
			NS.push(tmp);
		}
		else if (str[i] == '(') {
			CS.push(str[i]);
		}
		else if (str[i] == ')') {
			char op = CS.top();
			CS.pop();
			while (op != '(') {
				createTree(op, NS);
				op = CS.top();
				CS.pop();
			}
		}
		else {
			if (str[i] != ' ') {
				if (!empty(CS) && getPriority(str[i]) <= getPriority(CS.top())) {
					createTree(CS.top(), NS);
					CS.pop();
				}
				CS.push(str[i]);
			}
		}


	}

	while (!empty(CS)) {
		createTree(CS.top(), NS);
		CS.pop();
	}

	Node* res = NS.top();
	return res;
	
}



void duyetHauTo(Node* root) {
	if (root != nullptr) {
		duyetHauTo(root->left);
		duyetHauTo(root->right);
		cout << root->info << " ";
	}
}



int main() {

	char str[] = "5 * (6+2)";
	Node* root;
	init(root);
	root = createRoot(str);
	duyetHauTo(root);

	cout << endl;

	return 0;
}