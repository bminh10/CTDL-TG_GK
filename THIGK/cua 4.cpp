#include <iostream>
#include <stack>
using namespace std;

struct Node {
	int info;
	Node* left;
	Node* right;
};

void init(Node*& root) {
	root = nullptr;
}

Node* createNode(int x) {
	Node* p = new Node();
	p->info = x;
	p->left = nullptr;
	p->right = nullptr;
	return p;
}

//c1
void addNode(Node*& root,int x) {
	if (root == nullptr) {
		root = createNode(x);
		return;
	}
	else if (x > root->info) {
		addNode(root->right, x);
	}
	else {
		addNode(root->left, x);
	}

}

void delNode(Node*& root, int x) {
	if (root != nullptr) {
		if (x > root->info) {
			delNode(root->right, x);
		}
		else if (x < root->info) {
			delNode(root->left, x);
		}
		else {
			if (root->left == nullptr && root->right == nullptr) {
				Node* p = root;
				root = nullptr;
				delete p;
				return;
			}
			else if (root->left != nullptr && root->right != nullptr) {
				Node* tmp = root->right;
				while (tmp->left != nullptr) {
					tmp = tmp->left;
				}
				root->info = tmp->info;
				delNode(root->right, tmp->info);
			}
			else {
				Node* p = root;
				if (root->left == nullptr) {
					root = root->right;
				}
				else {
					root = root->left;
				}
				delete p;
				return;
			}

		}
	}
}

void clearNode(Node*& root) {
	while (root != nullptr) {
		delNode(root, root->info);
	}
}
bool isPrime(int n) {
	if (n < 2) {
		return false;
	}
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int countPrime(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	if (isPrime(root->info) == true) {
		return (countPrime(root->left) + countPrime(root->right))+1;
	}
	return countPrime(root->left) + countPrime(root->right);

}


void LNR(Node* root) {
	if (root != nullptr) {
		LNR(root->left);
		cout << root->info << " ";
		LNR(root->right);
	}
}
//void stackLNR(Node* root) {
//	Node* tmp = root;
//	stack<Node*> s;
//	while (tmp != nullptr || !empty(s)) {
//		while (tmp != nullptr) {
//			s.push(tmp);
//			tmp = tmp->left;
//		}
//		tmp = s.top();
//		s.pop();
//		cout << tmp->info << " ";
//		tmp = tmp->right;
//	}
//
//}
//void stackNLR(Node* root) {
//	Node* tmp = root;
//	stack<Node*>s;
//	
//	while (tmp != nullptr || !empty(s)) {
//		while (tmp != nullptr) {
//			s.push(tmp);
//
//			cout << tmp->info << " ";
//
//			tmp = tmp->left;
//		}
//		tmp = s.top();
//		s.pop();
//		tmp = tmp->right;
//	}
//}
//void stackLRN(Node* root) {
//	if (root == nullptr) {
//		return;
//	}
//	stack<Node*> s1, s2;
//	s1.push(root);
//
//	while (!s1.empty()) {
//		Node* tmp = s1.top(); s1.pop();
//		s2.push(tmp);
//
//		if (tmp->left != nullptr)
//			s1.push(tmp->left);
//		if (tmp->right != nullptr)
//			s1.push(tmp->right);
//	}
//
//	// s2 chứa theo thứ tự Node, Right, Left → đảo lại sẽ là LRN
//	while (!s2.empty()) {
//		cout << s2.top()->info << " ";
//		s2.pop();
//	}
//	
//
//}


//void stackLRN(Node* root) {
//	stack <Node*>s1, s2;
//	Node* tmp = root;
//	s1.push(tmp);
//	while (!empty(s1)) {
//		tmp = s1.top();
//		s1.pop();
//		s2.push(tmp);
//		if (tmp->left != nullptr) {
//			s1.push(tmp->left);
//		}
//		if (tmp->right != nullptr) {
//			s1.push(tmp->right);
//		}
//	}
//
//	while (!empty(s2)) {
//		cout << s2.top()->info << " ";
//		s2.pop();
//	}
//
//}
//
//void stackLNR(Node* root) {
//	stack<Node*>s;
//	Node* tmp = root;
//	while (!empty(s) || tmp != nullptr) {
//		while (tmp != nullptr) {
//			s.push(tmp);
//			tmp = tmp->left;
//		}
//		tmp = s.top();
//		s.pop();
//		cout << tmp->info << " ";
//		tmp = tmp->right;
//
//
//	}
//}
//void stackNLR(Node* root) {
//	stack <Node*>s;
//	Node* tmp = root;
//	while (!empty(s) || tmp != nullptr) {
//		while (tmp != nullptr) {
//			cout << tmp->info << " ";
//			s.push(tmp);
//			tmp = tmp->left;
//		}
//
//		tmp = s.top();
//		s.pop();
//		tmp = tmp->right;
//
//	}
//
//
//}



void stackLRN(Node* root) {
	Node* tmp = root;
	stack<Node*>s1, s2;
	s1.push(tmp);
	while (!empty(s1)) {
		tmp = s1.top();
		s1.pop();
		s2.push(tmp);
		if (tmp->left != nullptr) {
			s1.push(tmp->left);
		}
		if (tmp->right != nullptr) {
			s1.push(tmp->right);
		}
	}

	while (!empty(s2)) {
		cout << s2.top()->info << " ";
		s2.pop();
	}


}

void stackNLR(Node* root) {
	stack<Node*>s;
	Node* tmp = root;
	while (tmp != nullptr || !empty(s)) {
		while (tmp != nullptr) {
			cout << tmp->info << " ";
			s.push(tmp);
			tmp = tmp->left;
		}

		tmp = s.top();
		s.pop();
		tmp = tmp->right;

	}
}

void stackLNR(Node* root) {
	Node* tmp = root;
	stack<Node*>s;
	while (tmp != nullptr || !empty(s)) {
		while (tmp != nullptr) {
			s.push(tmp);
			tmp = tmp->left;
		}
		tmp = s.top();
		s.pop();
		cout << tmp->info << " ";
		tmp = tmp->right;

	}

}




int main() {
	Node* root;
	init(root);
	addNode(root,40);
	addNode(root,50);
	addNode(root,30);
	addNode(root,20);
	addNode(root,10);

	
	stackLNR(root);
	cout << endl;
	/*cout << endl;
	cout << countPrime(root) << endl;*/
	clearNode(root);
	if (root == nullptr) {
		cout << "Rong \n";
	}

	return 0;
}