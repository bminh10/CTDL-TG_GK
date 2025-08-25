#include "QueueList.h"
#include <fstream>
#include <stack>
#include <queue>




//nếu ko để các hàm của queue list ra ngoài thì sẽ bị báo lỗi
void init(QueueList& q) {
	q.head = q.tail = nullptr;
}

bool isEmpty(QueueList q) {
	return q.head == nullptr;
}


Node* front(QueueList q) {
	return q.head->data;
}

LinkedList* createNode(Node* x) {
	LinkedList* p = new LinkedList();
	p->data = x;
	p->next = nullptr;
	return p;
}



void push(QueueList& q, Node* x) {
	LinkedList* p = createNode(x);
	if (isEmpty(q)) {
		q.head = q.tail = p;
		return;
	}
	q.tail->next = p;
	q.tail = p;
}

void pop(QueueList& q) {
	if (isEmpty(q)) {
		return;
	}
	LinkedList* tmp = q.head;
	if (q.head == q.tail) {
		q.head = q.tail = nullptr;
		delete tmp;
		return;
	}
	q.head = tmp->next;
	tmp->next = nullptr;
	delete tmp;
	return;


}


void init(Node*& root) {
	root = nullptr;
}

Node* createNodeLa(int x) {
	Node* p = new Node();
	p->info = x;
	p->left = nullptr;
	p->right = nullptr;
	p->height = 1;
	return p;
}


int getHeight(Node* root) {
	return root == NULL ? 0 : root->height;
}

void updateHeight(Node*& root) {
	if (root == nullptr)return;
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalance(Node* root) {
	return getHeight(root->left) - getHeight(root->right);
}



void rightRotate(Node*& root) {
	
	Node* q = root->left;
	Node* r = q->right;

	root->left = r;
	q->right = root;

	updateHeight(root);
	updateHeight(q);

	root = q;
}

void leftRotate(Node*& root) {
	
	Node* q = root->right;
	Node* r = q->left;

	root->right = r;
	q->left = root;

	updateHeight(root);
	updateHeight(q);

	root = q;

}




void addNode(Node*& root , int x) {
	if (root == nullptr) {
		root = createNodeLa(x);
		return;
		
	}
	else if (x > root->info) {
		addNode(root->right,x);
	}
	else if( x< root->info) {
		addNode(root->left,x);
	}
	


	updateHeight(root);
	int balance = getBalance(root);
	if (balance > 1 && x < root->info) {
		rightRotate(root);
	}
	else if (balance > 1 && x > root->left->info) {
		leftRotate(root->left);
		rightRotate(root);
	}
	else if (balance < -1 && x >root->info) {
		leftRotate(root);
	}
	else if (balance < -1 && x < root->right->info) {
		rightRotate(root->right);
		leftRotate(root);
	}



}



void readFile(Node*& root) {
	ifstream fin;
	fin.open("BST.txt");
	if (fin.is_open()) {
		int n;
		fin >> n;
		for (int i = 0; i < n; i++) {
			int x;
			fin >> x;
			fin.ignore();
			addNode(root, x);
		}
		
		fin.close();
	}
}


void delNode(Node*& root, int x) {
	if (root == nullptr) {
		return;
	}
	if (x > root->info) {
		delNode(root->right, x);
	}
	else if (x < root->info) {
		delNode(root->left, x);
	}
	else {
		Node* tmp = root;
		if (root->left == nullptr) {
			root = root->right;
			delete tmp;
		}
		else if (root->right == nullptr) {
			root = root->left;
			delete tmp;
		}
		else {
			tmp = tmp->right;
			while (tmp->left != nullptr) {
				tmp = tmp->left;
			}
			root->info = tmp->info;
			delNode(root->right, tmp->info);
		}
		if (root == nullptr) {
			return;
		}
		
	}
	//khi xoa thi phai cap nhat lai chieu cao va can bang lai ( neu mat can bang ) 
	updateHeight(root);
	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0) {
		rightRotate(root);
	}
	else if (balance > 1 && getBalance(root->left) < 0) {
		leftRotate(root->left);
		rightRotate(root);
	}
	else if (balance < -1 && getBalance(root->right) <= 0) {
		leftRotate(root);
	}
	else if (balance < -1 && getBalance(root->right)>0) {
		rightRotate(root->right);
		leftRotate(root);
	}

	////cap nhat chieu cao
	//updateHeight(root);
	////lay he so can bang
	//int val = getBalance(root);

	//if (val < -1 && getBalance(root->right) <= 0) {
	//	//mat can bang phai phai
	//	leftRotate(root);

	//}
	//else if (val < -1 && getBalance(root->right)>0) {
	//	//mat can bang phai trai
	//	rightRotate(root->right);
	//	leftRotate(root);
	//}
	//else if (val > 1 && getBalance(root->left) >= 0) {
	//	//mat can bang trai trai
	//	rightRotate(root);

	//}
	//else if (val > 1 && getBalance(root->left) < 0) {
	//	//mat can bang trai phai
	//	leftRotate(root->left);
	//	rightRotate(root);
	//}

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
	cout << endl;
}

void stackLRN(Node* root) {
	Node* tmp = root;
	stack<Node*>s1;
	stack<Node*>s2;
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
	cout << endl;

}
void stackNLR(Node* root) {
	Node* tmp = root;
	stack<Node*>s;
	while (tmp != nullptr || !empty(s)) {
		while (tmp != nullptr) {
			cout << tmp->info << " ";
			s.push(tmp);
			tmp = tmp -> left;
		}
		tmp = s.top();
		s.pop();
		tmp = tmp->right;
	}
	cout << endl;
}

void duyetRong(Node* root) {
	Node* tmp = root;
	queue<Node*> q;
	q.push(tmp);
	while (!empty(q)) {
		tmp = q.front();
		q.pop();
		cout << tmp->info << " ";
		if (tmp->left != nullptr) {
			q.push(tmp->left);
		}
		if (tmp->right != nullptr) {
			q.push(tmp->right);
		}
	}
	cout << endl;
}

void clearQueue(QueueList& q) {
	while (q.head != nullptr) {
		pop(q);
	}
}

void duyetRongLinkedList(Node* root) {
	Node* tmp = root;
	QueueList q;
	init(q);
	push(q, tmp);
	while (!isEmpty(q)) {
		tmp = front(q);
		pop(q);
		cout << tmp->info << " ";
		if (tmp->left != nullptr) {
			push(q, tmp->left);
		}
		if (tmp->right != nullptr) {
			push(q, tmp->right);
		}
	}
	
	
	cout << endl;
}



void clearTree(Node*& root) {
	while (root != nullptr) {
		delNode(root, root->info);
	}
}


int main() {
	Node* root;
	init(root);
	readFile(root);
	delNode(root, 20);
	duyetRongLinkedList(root);



	clearTree(root);
	if (root == nullptr) {
		cout << "Giai phong thanh cong !\n";
	}
	else {
		cout << "That bai ! \n";
	}
	return 0;
}