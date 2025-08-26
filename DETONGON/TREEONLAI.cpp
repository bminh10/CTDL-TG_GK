#include <iostream>
#include <stack>
#include <fstream>
#include <queue>
using namespace std;


struct Node {
	int info;
	Node* left, * right;
};
void init(Node*& root) {
	root = nullptr;
}


Node* createNodeLa(int x) {
	Node* p = new Node();
	p->info = x;
	p->left = nullptr;
	p->right = nullptr;
	return p;
}

void addNode(Node*& root,int x) {
	if (root == nullptr) {
		root = createNodeLa(x);
		return;
	}
	if (x > root->info) {
		addNode(root->right, x);
	}
	else {
		addNode(root->left, x);
	}

}

void readFile(Node*& root) {
	ifstream fin;
	fin.open("BST.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
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
		delNode(root->left,x);
	}
	else {
		Node* tmp = root;
		if (root->left == nullptr) {
			root = root->right;
		}
		else if (root->right == nullptr) {
			root = root->left;
		}
		else {
			tmp = tmp->right;
			while (tmp->left != nullptr) {
				tmp = tmp->left;
			}
			root->info = tmp->info;
			delNode(root->right, tmp->info);
		}
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
	cout << endl;
}
void stackNLR(Node* root) {
	Node* tmp = root;
	stack<Node*>s;
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



struct List {
	Node* info;
	List* next;
};


struct QueueList {
	List* head, * tail;
};

void init(QueueList& q) {
	q.head = q.tail = nullptr;
}

List* createNode(Node* x) {
	List* p = new List();
	p->info = x;
	p->next = nullptr;
	return p;

}

bool isEmpty(QueueList q) {
	return q.head == nullptr;
}

Node* front(QueueList q) {
	return q.head->info;
}

void enQueue(QueueList& q, Node* x) {
	List* p = createNode(x);
	if (isEmpty(q)) {
		q.head = q.tail=  p;
		return;
	}
	q.tail->next = p;
	q.tail = p;

}

void deQueue(QueueList& q) {
	if (isEmpty(q)) {
		return;
	}
	List* tmp = q.head;
	if (q.head == q.tail) {
		init(q);
		delete tmp;
		return;
	}
	q.head = q.head->next;
	tmp->next = nullptr;
	delete tmp;
}

#define MAX 7
struct QueueCircle {
	Node* a[MAX];
	int front;
	int rear;
};

void init(QueueCircle& q) {
	q.front = q.rear = -1;
}

bool isEmpty(QueueCircle q) {
	return q.front == -1;
}

bool isFull(QueueCircle q) {
	return (q.rear + 1) % MAX == q.front;
}

Node* front(QueueCircle q) {
	return q.a[q.front];
}

void enQueue(QueueCircle& q, Node* x) {
	if (isFull(q)) {
		return;
	}
	if (isEmpty(q)) {
		q.front = 0;
	}
	q.rear = (q.rear + 1) % MAX;
	q.a[q.rear] = x;
}

void deQueue(QueueCircle& q) {
	if (isEmpty(q)) {
		return;
	}
	if (q.front == q.rear) {
		init(q);
		return;
	}
	q.front = (q.front + 1) % MAX;
}


struct QueueTT {
	Node* a[MAX];
	int front;
	int rear;
};

void init(QueueTT& q) {
	q.front = q.rear = -1;
}

bool isEmpty(QueueTT q) {
	return q.front == -1;
}

bool isFull(QueueTT q) {
	return q.rear - q.front == MAX - 1;
}

Node* front(QueueTT q) {
	return q.a[q.front];
}

void enQueue(QueueTT& q, Node* x) {
	if (isFull(q)) {
		return;
	}
	if (isEmpty(q)) {
		q.front = 0;
	}
	if (q.rear + 1 == MAX) {
		for (int i = 0; i <= q.rear - q.front; i++) {
			q.a[i] = q.a[q.front + i];
		}
		q.rear = q.rear - q.front;
		q.front = 0;

	}
	q.rear = q.rear + 1;
	q.a[q.rear] = x;
}

void deQueue(QueueTT& q) {
	if (isEmpty(q)) {
		return;
	}
	if (q.front == q.rear) {
		init(q);
		return;
	}
	q.front = q.front + 1;
}








void duyetRong(Node* root) {
	Node* tmp = root;
	queue<Node*>q;
	q.push(root);
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

void duyetRongList(Node* root) {
	Node* tmp = root;
	QueueList q;
	init(q);
	enQueue(q, tmp);
	while (!isEmpty(q)) {
		tmp = front(q);
		deQueue(q);
		cout << tmp->info << " ";
		if (tmp->left != nullptr) {
			enQueue(q,tmp->left);
		}
		if (tmp->right != nullptr) {
			enQueue(q, tmp->right);
		}
	}
	cout << endl;
}

void duyetRongCircle(Node* root) {
	Node* tmp = root;
	QueueCircle q;
	init(q);
	enQueue(q, tmp);
	while (!isEmpty(q)) {
		tmp = front(q);
		deQueue(q);
		cout << tmp->info << " ";
		if (tmp->left != nullptr) {
			enQueue(q, tmp->left);
		}
		if (tmp->right != nullptr) {
			enQueue(q, tmp->right);
		}
	}
	cout << endl;
}

void duyetRongTT(Node* root) {
	Node* tmp = root;
	QueueTT q;
	init(q);
	enQueue(q, tmp);
	while (!isEmpty(q)) {
		tmp = front(q);
		deQueue(q);
		cout << tmp->info << " ";
		if (tmp->left != nullptr) {
			enQueue(q, tmp->left);
		}
		if (tmp->right != nullptr) {
			enQueue(q, tmp->right);
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
	duyetRongTT(root);


	clearTree(root);
	if (root == nullptr) {
		cout << "Da giai phong \n";
	}

	return 0;
}