#include <iostream>


#define MAX 7
using namespace std;
struct Node {
	int info;
	Node* left;
	Node* right;
};

//queue luu 1 nut cua cay
struct Queue {
	Node* a[MAX];
	int front, rear;
};
//khoi tao rong
void init(Queue& pQ) {
	pQ.front = -1;
	pQ.rear = -1;
}

//kiem tra rong
bool isEmpty(Queue Q) {
	return Q.front == -1;
}
//kiem tra queue day
bool fullQueue(Queue Q) {
	return (Q.rear + 1) % MAX == Q.front;
}
//lay phan tu nut dau tien
Node* front(Queue Q) {
	return Q.a[Q.front];
}

//them queue (them cuoi)
void Push(Queue& pQ, Node* x) {
	if (fullQueue(pQ)) {
		cout << "Hang day \n";
		return;
	}
	if (isEmpty(pQ)) {
		pQ.front = 0;
	}
	pQ.rear = (pQ.rear + 1) % MAX;
	pQ.a[pQ.rear] = x;
}
//xoa dau queue
void pop(Queue& pQ) {
	if (isEmpty(pQ)) {
		cout << "Hang rong\n";
		return;
	}
	if (pQ.front == pQ.rear) {
		init(pQ);
	}
	else {
		pQ.front = (pQ.front + 1) % MAX;
	}
}
