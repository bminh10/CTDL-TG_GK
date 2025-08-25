#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* left, * right;
	int height = 1;
};

struct LinkedList {
	Node* data;
	LinkedList* next;
};


struct QueueList {
	LinkedList* head, * tail;
};

void init(QueueList& q);
bool isEmpty(QueueList q);
LinkedList* createNode(Node* x);
void push(QueueList& q, Node* x);
void pop(QueueList& q);

