#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* left, * right;
	int height;
};

struct List {
	Node* info;
	List* next;
};


List* createNode(Node* x) {
	List* q = new List();
	q->info = x;
	q->next = nullptr;
	
	return q;
}

struct QueueList {
	List* head, * tail;
};

void init(QueueList& q) {
	q.head = q.tail = nullptr;
}

bool isEmpty(QueueList q) {
	return q.head == nullptr;
}



Node* front(QueueList q) {
	return q.head->info;
}


void push(QueueList& q, Node* x) {
	List* p = createNode(x);
	if (isEmpty(q)) {
		q.head = q.tail = p;
		return;
	}
	q.tail->next = p;
	q.tail = p;
}

void pop(QueueList& q) {
	if (isEmpty(q)) {
		cout << "Rong\n";
		return;
	}
	List* tmp = q.head;
	if (q.head == q.tail) {
		q.head = q.tail = nullptr;
		delete tmp;
		return;
	}
	q.head = q.head->next;
	tmp->next = nullptr;
	delete tmp;
	return;
}


#define MAX 7



struct QueueVong {
	Node* a[MAX];
	int front;
	int rear;
};

void init(QueueVong& q) {
	q.front = q.rear = -1;
}

bool isEmpty(QueueVong q) {
	return q.front == -1;
}

bool isFull(QueueVong q) {
	return (q.rear + 1) % MAX == q.front;
}

Node* front(QueueVong q) {
	return q.a[q.front];
}

void push(QueueVong& q, Node* x) {
	if (isFull(q)) {
		return;
	}
	if (isEmpty(q)) {
		q.front = 0;
	}
	q.rear = (q.rear + 1) % MAX;
	q.a[q.rear] = x;

}

void pop(QueueVong& q) {
	if (isEmpty(q)) {
		return;
	}
	if (q.rear == q.front) {
		init(q);
		return;
	}
	q.front = (q.front + 1) % MAX;

}