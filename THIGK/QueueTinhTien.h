#include <iostream>
#define MAX 5
using namespace std;
struct Node {
	int info;
	Node* left;
	Node* right;
	int height;
};
//khai bao queue chua Nut cua cay
struct Queue {
	Node* a[MAX];
	int front, rear;
};

//khoi tao rong queue
void init(Queue& q) {
	q.front = -1;
	q.rear = -1;
}
//kiem tra rong
bool isEmpty(Queue q) {
	return q.front == -1;
}
//kiem tra day
bool isFull(Queue q) {
	return q.rear-q.front+1 == MAX;
}

//lay nut dau tien trong queue
Node* front(Queue q) {
	if (!isEmpty(q)) {
		return q.a[q.front];
	}
	return NULL;
}
//xoa phan tu dau
void pop(Queue& q) {
	if (isEmpty(q)) {
		cout << "Hang rong\n";
		return;
	}
	if (q.front == q.rear) {
		init(q);
	}
	else {
		q.front = q.front + 1;
	}

}
//them vao cuoi queue
void push(Queue& q, Node* x) {
	if (isFull(q)) {
		cout << "Hang day \n";
		return;
	}
	if (isEmpty(q)) {
		q.front = 0;
	}


	/*else if (q.rear == MAX - 1) {

		for (int i = q.front; i <= q.rear; i++) {

			q.a[i - q.front] = q.a[i];
		}

		q.rear = q.rear - q.front;

		q.front = 0;

	}*/
	else if (q.rear == MAX - 1) {
		//tịnh tiến từ 0 tới q.rear-q.front
		for (int i = 0; i <= q.rear-q.front; i++) {

			q.a[i] = q.a[q.front+i];
		}

		q.rear = q.rear - q.front;

		q.front = 0;

	}
	q.rear = q.rear + 1;
	q.a[q.rear] = x;

}

