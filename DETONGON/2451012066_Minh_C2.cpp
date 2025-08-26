#include <iostream>
#include <fstream>
using namespace std;


struct Node {
	int info;
	Node* next;
};

void init(Node*& head) {
	head = nullptr;
}

Node* createNode(int x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	return p;
}

void addLast(Node*& head, int x) {
	Node* p = createNode(x);
	if (head == nullptr) {
		head = p;
		return;
	}
	Node* q = head;
	while (q->next != nullptr) {
		q = q->next;
	}
	q->next = p;
}

void readFile(Node*& head) {
	ifstream fin;
	fin.open("number.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			int x;
			fin >> x;
			fin.ignore();
			addLast(head, x);
		}
		fin.close();
	}
}

void delFirst(Node*& head) {
	if (head == nullptr) {
		return;
	}
	Node* tmp = head;
	if (head->next == nullptr) {
		head = nullptr;
		delete tmp;
		return;
	}
	head = head->next;
	tmp->next = nullptr;
	delete tmp;
	return;
}
void printList(Node* head) {
	Node* tmp = head;
	while (tmp != nullptr) {
		cout << tmp->info << " ";
		tmp = tmp->next;
	}

	cout << endl;
}

bool ASC(int a, int b) {
	return a > b;
}
bool DESC(int a, int b) {
	return a < b;
}

void selectionSort(Node*& head,bool func(int,int)) {
	Node* pos;
	for (Node* i = head; i->next != nullptr; i = i->next) {
		pos = i;
		for (Node* j = i->next; j != nullptr; j = j->next) {
			if ( func(pos->info , j->info)) {
				pos = j;
			}
		}
		swap(i->info, pos->info);
	}
}

void clearNode(Node*& head) {
	while (head != nullptr) {
		delFirst(head);
	}
}

void insOdered(Node*& head,int x, bool func(int, int)) {
	Node* p = createNode(x);
	if (head == nullptr) {
		head = p;
		return;
	}
	if (func(head->info , x) ) {
		p->next = head;
		head = p;
		return;
	}
	Node* q = head;
	while (q->next != nullptr) {
		if ( func(x , q->info) && func(q->next->info , x) ) {
			p->next = q->next;
			q->next = p;
			return;
		}
		q = q->next;
	}

	q->next = p;
}


void insertionSort(Node*& head, bool func(int, int)) {
	Node* tmp;
	init(tmp);
	for (Node* i = head; i != nullptr;i=i->next) {
		insOdered(tmp, i->info,func);
	}
	clearNode(head);
	head = tmp;
}

//void bubbleSort(Node*& head,bool func(int,int)) {
//	//tao flag kiem tra neu co su hoan vi thi tiep tuc lap de kiem tra lai tu dau
//	if (head == nullptr) {
//		return;
//	}
//	bool flag;
//	//last la phan tu cuoi cung de giam pham vi duyet
//	Node* last;
//	init(last);
//	do {
//		flag = false;
//		Node* i = head;
//		while ( i->next != last) {
//			if (func(i->info, i->next->info)) {
//				swap(i->info, i->next->info);
//				flag = true;
//			}
//			i = i->next;
//		}
//
//		//gan last cho Node doi cho cuoi cung de giam pham vi lap 
//		last = i;
//	} while (flag == true); //tiep tuc neu co su thay doi
//	
//}

void bubbleSort(Node*& head, bool func(int, int)) {
	if (head == nullptr) {
		return;
	}
	bool flag;
	Node* last = nullptr;
	do {
		flag = false;
		Node* i = head;
		while (i->next != last) {
			if (i->info < i->next->info) {
				swap(i->info, i->next->info);
				flag = true;
			}
			
			i = i->next;
		}
		last = i;

	} while (flag == true);
}

Node* search(Node* head, int x) {
	Node* tmp = head;
	while (tmp != nullptr && tmp->info != x) {
		tmp = tmp->next;
	}
	return tmp;
}

bool isDesc(Node* head) {
	for (Node* i = head; i->next != nullptr; i = i->next) {
		Node* j = i->next;
		if (i->info < j->info) {
			return false;
		}
	}
	return true;
}

bool isEven(int n) {
	return n % 2 == 0;
}

Node* evenList(Node* head) {
	Node* tmp = head;
	Node* newList;
	init(newList);
	while (tmp != nullptr) {
		if (isEven(tmp->info)) {
			addLast(newList, tmp->info);
		}
		tmp = tmp->next;
	}
	return newList;
}

void reverseList(Node*& head) {
	Node* tmp = head;
	Node* pre = nullptr;
	Node* next = nullptr;
	while (tmp != nullptr) {
		pre = tmp;
		tmp = tmp->next;
		pre->next = next;
		next = pre;
	}
	head = pre;
}


int main() {
	Node* head;
	init(head);
	readFile(head);
	/*selectionSort(head,ASC);*/

	/*insertionSort(head,ASC);*/
	bubbleSort(head, ASC);
	
	printList(head);

	/*Node* res = evenList(head);
	if (res != nullptr) {
		cout << "DS PHAN TU CHAN : \n";
		printList(res);
	}
	else {
		cout << "DS KHONG CO SO CHANG\n";
	}*/

	clearNode(head);
	if (head == nullptr) {
		cout << "Giai phong thanh cong\n";
	}

	return 0;
}