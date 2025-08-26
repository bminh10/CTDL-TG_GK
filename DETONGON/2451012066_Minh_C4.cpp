#include "QueueList.h"
#include <cmath>
#include <stack>
#include <queue>
#include <fstream>
using namespace std;



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
	if (root == nullptr) {
		return 0;
	}
	return root->height;
}

void updateHeight(Node*& root) {
	if (root == nullptr) {
		return;
	}
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
}

int getBalance(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return getHeight(root->left) - getHeight(root->right);
}

void rightRotate(Node*& root) {
	Node* q = root->left;
	Node* r = q->right;

	root->left = r;
	q->right = root;

	updateHeight(root); 
	updateHeight(q);
	root =q;

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






void addNode(Node*& root, int x) {
	if (root == nullptr) {
		root = createNodeLa(x);
		return;
	}
	else if (x > root->info) {
		addNode(root->right, x);
	}
	else {
		addNode(root->left, x);
	}

	updateHeight(root);
	int balance = getBalance(root);

	if (balance > 1 && x < root->left->info) {
		rightRotate(root);
	}
	else if (balance > 1 && x > root->left->info) {
		leftRotate(root->left);
		rightRotate(root);
	}
	else if (balance < -1 && x > root->right-> info) {
		leftRotate(root);

	}
	else if (balance < -1 && x < root->right->info) {
		rightRotate(root->right);
		leftRotate(root);
	}


}

void addNodeNoRec(Node*& root, int x) {
	Node* tmp = root;
	Node* parent = nullptr;
	Node* p = createNodeLa(x);
	while (tmp != nullptr ) {
		parent = tmp;
		if (x > tmp->info) {
			tmp = tmp->right;
		}
		else if (x < tmp->info) {
			tmp = tmp->left;
		}
	}

	if (parent == nullptr) {
		root = p;
		return;
	}
	else {
		if (x > parent->info) {
			parent->right = p;
		}
		else {
			parent->left = p;
		}
	}

}

void delNodeNoRec(Node*& root, int x) {
	Node* tmp = root;
	Node* parent = nullptr;
	while (tmp != nullptr && tmp->info != x) {
		parent = tmp;
		if (x > tmp->info) {
			tmp = tmp->right;
		}
		else {
			tmp = tmp->left;
		}
	}

	if (tmp != nullptr) {
		if (tmp->left == nullptr || tmp->right == nullptr) {
			Node* lk = tmp;
			if (tmp->left == nullptr) {
				lk = tmp->right;
			}
			else {
				lk = tmp->left;
			}
			if (parent == nullptr) {
				root = lk;
				delete tmp;
				return;
			}
			else {
				if (x > parent->info) {
					parent->right = lk;
				}
				else {
					parent->left = lk;
				}
			}


		}
		else {
			Node* q = tmp->right;
			parent = nullptr;
			while (q->left != nullptr) {
				q = q->left;
			}
			tmp->info = q->info;
			Node* lkq = q;

			if (q->left == nullptr) {
				lkq = q->right;
			}
			else {
				lkq = q->left;
			}

			if (parent == nullptr) {
				tmp->right = lkq;
				delete q;
				return;
			}
			else {
				parent->left = lkq;
				delete q;
				return;
			}

		}

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
			tmp = tmp->left;
		}
		tmp = s.top();
		s.pop();
		tmp = tmp->right;
	}
	cout << endl;
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
	}


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
	else if (balance < -1 && getBalance(root->right) > 0) {
		rightRotate(root->right);
		leftRotate(root);
	}


}



void clearTree(Node*& root) {
	while (root != nullptr) {
		delNodeNoRec(root, root->info);
	}
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
	return q.rear - q.front == MAX-1;
}

Node* front(QueueTT q) {
	return q.a[q.front];
}
void push(QueueTT& q, Node* x) {
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

void pop(QueueTT& q) {
	if (isEmpty(q)) {
		return;
	}
	if (q.rear == q.front) {
		init(q);
		return;
	}
	q.front = q.front + 1;
}








void duyetRong(Node* root) {
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

void duyetRongCircle(Node* root) {
	Node* tmp = root;
	QueueVong q;
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

void duyetRongTT(Node* root) {
	Node* tmp = root;
	QueueTT q;
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


bool isPrime(int n) {
	if (n < 1) {
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
	if (isPrime(root->info)) {
		return (countPrime(root->left) + countPrime(root->right)) + 1;
	}
	return countPrime(root->left) + countPrime(root->right);
}

int countSL(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return 1 + (countSL(root->left) + countSL(root->right));
}


int sum(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return root->info + (sum(root->left) + sum(root->right));
}

float AVG(Node* root) {
	int tong = sum(root);
	int sl = countSL(root);
	return 1.0* ( tong /  sl ) ;
}

void addLast(List*& head, Node* x) {
	List* p = createNode(x);
	if (head == nullptr) {
		head = p;
		return;
	}
	List* q = head;
	while (q->next != nullptr) {
		q = q->next;
	}
	q->next = p;
}

void saveNodeLv(List*& head, Node* root) {
	if (root == nullptr) {
		return;
	}
	if (root->left != nullptr && root->right != nullptr) {
		addLast(head, root);
		saveNodeLv(head, root->left);
		saveNodeLv(head, root->right);
	}
	else {
		saveNodeLv(head, root->left);
		saveNodeLv(head, root->right);
	}
	
}

void init(List*& head) {
	head = nullptr;
}

void xuatNodeBac2(List* head) {
	ofstream fout;
	fout.open("NodeBac2.txt");
	if (fout.is_open()) {
		List* tmp = head;
		while (tmp != nullptr) {
			fout << tmp->info->info << " ";
			tmp = tmp->next;
		}
		cout << "Ghi data thanh cong \n";
		fout.close();
	}
}

void delFirst(List*& head) {
	if (head == nullptr) {
		return;
	}
	List* tmp = head;
	if (head->next == nullptr) {
		head = nullptr;
		delete tmp;
		return;
	}
	head = head->next;
	tmp->next = nullptr;
	delete tmp;

}

int findMax(Node* root) {
	/*if (root->left == nullptr && root->right == nullptr) {
		return root->info;
	}*/
	if (root->right == nullptr) {
		return root->info;
	}

	int max = root->info;
	/*if (root->left != nullptr) {
		int left = findMax(root->left);
		if (max < left) {
			max = left;
		}
	}*/
	if (root->right != nullptr) {
		int right = findMax(root->right);
		if (max < right) {
			max = right;
		}
	}
	return max;
}



int findMin(Node* root) {
	/*if (root->left == nullptr && root->right == nullptr) {
		return root->info;
	}

	int min = root->info;
	if (root->left != nullptr) {
		int left = findMin(root->left);
		if (min > left) {
			min = left;
		}
	}
	if (root->right != nullptr) {
		int right = findMin(root->right);
		if (min > right) {
			min = right;
		}
	}*/
	if (root->left == nullptr) {
		return root->info;
	}


	int min = root->info;
	if (root->left != nullptr) {
		int left = findMin(root->left);
		if (min > left) {
			min = left;
		}
	}


	return min;
}




Node* findParent(Node* root,int a ,int b) {
	if (root->info >= a && root->info <= b) {
		return root;
	}
	if (root->info > a && root->info > b) {
		return findParent(root->left, a, b);
	}
	else if(root->info < a && root->info < b) {
		return findParent(root->right, a, b);
	}
	
}


int calCanh(Node* parent, int val) {
	if (parent->info == val) {
		return 0;
	}
	if (val > parent->info) {
		return calCanh(parent->right, val)+1;
	}
	else {
		return calCanh(parent->left, val)+1;
	}
}

int aToB(Node* parent,int a , int b) {
	if (parent == nullptr) {
		return 0;
	}

	int d1 = calCanh(parent, a);
	int d2 = calCanh(parent, b);
	return d1 + d2;
}



int countIf(Node* root, int x) {
	if (root == nullptr) {
		return 0;
	}
	if (root->info >= x) {
		return (countIf(root->left, x) + countIf(root->right, x)) + 1;
	}
	return countIf(root->left, x) + countIf(root->right, x);
}

void xuatMucK(Node* root,int k,int muc = 0 ) {
	if (root == nullptr) {
		return;
	}
	if (muc == k) {
		cout << root->info << " ";
	}		
	xuatMucK(root->left, k,muc + 1);
	xuatMucK(root->right, k,muc+1);
}

int findDepth(Node* root, Node* tmp) {
	if (root->info == tmp->info) {
		return 0;
	}
	if (tmp->info > root->info) {
		return findDepth(root->right, tmp) + 1;
	}
	else {
		return findDepth(root->left, tmp) + 1;
	}

}

int tinhHeight(Node* root) {
	if (root == nullptr) {
		return -1;
	}
	return 1 + max(tinhHeight(root->left), tinhHeight(root->right));

}


void clearNode(List*& head) {

	while (head != nullptr) {
		delFirst(head);
	}
}


int main() {
	Node* root;;
	init(root);
	readFile(root);
	
	duyetRongTT(root);





	/*int res = countPrime(root);
	cout << "Cay co " << res << " snt ! \n";
	int soluong = countSL(root);
	cout << "Cay co " << soluong << " phan tu ! \n";
	float avg = AVG(root);
	cout << "Trung binh cong = " << avg << endl;
	cout << "Max = " << findMax(root) << endl;
	cout << "Min = " << findMin(root) << endl;

	xuatMucK(root, 2);
	cout << endl;*/

	/*int a, b;
	cout << "Nhap a: ";
	cin >> a;
	cout << "Nhap b: ";
	cin >> b;
	Node* parent = findParent(root, a, b);
	cout << "Cha chung cua a va b la: " << parent->info << endl;
	cout << "tu a toi b mat " << aToB(parent, a, b) << " canh  ! \n";*/

	/*int x;
	cout << "Nhap khoa x: ";
	cin >> x;
	cout << "Co " << countIf(root, x) << " gia tri lon hon hoac bang khoa x ! \n";*/

	List* head;
	init(head);
	saveNodeLv(head, root);
	xuatNodeBac2(head);
	

	//Node* p = createNodeLa(10);
	//int depth = findDepth(root, p);
	//cout << "Chieu sau tu goc toi node " << p->info << " la: " << depth << endl;
	//cout << "Chieu cao cua cay la: " << tinhHeight(root) << endl;

	clearNode(head);
	clearTree(root);
	if (root == nullptr && head==nullptr) {
		cout << "Giai phong thanh cong \n";
	}
	return 0;
}