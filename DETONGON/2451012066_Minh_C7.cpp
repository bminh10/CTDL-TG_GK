#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* next;
};


struct CircularLinkedList {
	Node* head, * tail;
};

void init(CircularLinkedList& l) {
	l.head = l.tail = nullptr;
}

Node* createNode(int x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	return p;
}

void addLast(CircularLinkedList& l, int x) {
	Node* p = createNode(x);
	
	if (l.head == nullptr) {
		l.head = l.tail = p;
		l.tail->next = l.head;
		return;
	}
	
	l.tail->next = p;
	l.tail = p;
	l.tail->next = l.head;


}

void createList(CircularLinkedList& l, int n) {
	for (int i = 1; i <= n; i++) {
		addLast(l, i);
	}
}


void delFirst(CircularLinkedList& l) {
	if (l.head == nullptr) {
		return;
	}
	Node* tmp = l.head;
	if (l.head == l.tail) {
		l.head = l.tail = nullptr;
		
		delete tmp;
		return;
	}
	l.head = l.head->next;
	l.tail->next = l.head;
	tmp->next = nullptr;
	delete tmp;

	


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


int countSL(CircularLinkedList l) {
	if (l.head == nullptr) {
		return 0;
	}
	int i = 0;
	Node* tmp = l.head;
	do
	{
		i++;
		tmp = tmp->next;
	} while (tmp!=l.head);
	return i;
}


void delPlayer(CircularLinkedList& l, Node*& tmp,bool &flag) {
	if (l.head == nullptr) {
		return;
	}

	Node* del = tmp;
	if (flag == true) {
		if (tmp == l.head) {
			if (l.head == l.tail) {
				l.head = l.tail = nullptr;
				tmp = nullptr;
				delete del;
				flag = false;
				return;
			}
			l.head = l.head->next;
			tmp = l.head;
			l.tail->next = l.head;
			del->next = nullptr;
			delete del;
			flag = false;
			return;
		}
		if (tmp == l.tail) {
			if (l.head == l.tail) {
				l.head = l.tail = nullptr;
				tmp = nullptr;
				delete del;
				flag = false;
				return;
			}
			tmp = tmp->next;
			Node* q = l.head;
			while (q->next != l.tail) {
				q = q->next;
			}
			l.tail = q;
			l.tail->next = l.head;

			del->next = nullptr;
			flag = false; 
			delete del;

			return;

		}
		tmp = tmp->next;
		Node* p = l.head;
		while (p->next != del) {
			p = p->next;
		}
		p->next = tmp;
		del->next = nullptr;
		delete del;
		flag = false;
		return;

	}
	else {
		Node* tmp2 = l.head;
		while (tmp2->next != del) {
			tmp2 = tmp2->next;
		}

		if (tmp == l.head) {
			if (l.head == l.tail) {
				l.head = l.tail = nullptr;
				tmp = nullptr;
				delete del;
				flag = true;
				return;
			}
			l.head = l.head->next;
			tmp = l.head;
			l.tail->next = l.head;
			del->next = nullptr;
			delete del;
			flag = true;
			return;
		}
		if (tmp == l.tail) {
			if (l.head == l.tail) {
				l.head = l.tail = nullptr;
				tmp = nullptr;
				delete del;
				flag = true;
				return;
			}
			tmp = tmp->next;
			Node* q = l.head;
			while (q->next != l.tail) {
				q = q->next;
			}
			l.tail = q;
			l.tail->next = l.head;

			del->next = nullptr;
			flag = true;
			delete del;

			return;

		}
		tmp = tmp->next;
		Node* p = l.head;
		while (p->next != del) {
			p = p->next;
		}
		p->next = tmp;
		del->next = nullptr;
		delete del;
		flag = true;
		return;
	}
	

}
void clearNode(CircularLinkedList& l) {
	if (l.head == nullptr) {
		return;
	}

	while (l.head != nullptr) {
		delFirst(l);
	}
}


CircularLinkedList cloneList(CircularLinkedList l) {
	Node* tmp = l.head;
	CircularLinkedList res;
	init(res);
	do {
		addLast(res, tmp->info);
		tmp = tmp->next;
	} while (tmp != l.head);
	return res;
}


void reverseList(CircularLinkedList& l) {
	Node* tmp = l.head;
	Node* pre = nullptr;
	Node* next = l.tail;
	do {
		pre = tmp;
		tmp = tmp->next;
		pre->next = next;
		next = pre;

	} while (tmp != l.head);
	l.head = pre;
	l.tail = tmp;
}


Node* findWin(CircularLinkedList l) {
	if (l.head == nullptr) {
		return nullptr;
	}
	int i = 1;
	
	Node* tmp = l.head;
	bool flag = true;
	
	while (countSL(l) > 1) {
		if (flag == true) {
			if (isPrime(i)) {
				delPlayer(l, tmp, flag);

			}
			else {
				tmp = tmp->next;
			}
		}
		else {
			Node* pre=l.head;
			while (pre->next != tmp) {
				pre = pre->next;
			}

			if (isPrime(i)) {
				delPlayer(l, tmp, flag);

			}
			else {
				tmp = pre;
			}
		}
		
		i++;
	}
	
	return tmp;
	
}

Node* findKWin(CircularLinkedList l,int k) {

	Node* start = l.head;
	
	do {
		Node* tmp = start;
		CircularLinkedList clone;
		init(clone);
		do
		{
			addLast(clone, tmp->info);
			tmp = tmp->next;
		} while (tmp != start);

		Node* winner = findWin(clone);
		if (winner->info == k) {
			return start;
		}

		
		start = start->next;
	} while (start != l.head);
	return NULL;
}


void selectionSort(CircularLinkedList& l) {
	Node* pos;
	Node* i = l.head;
	do {
		pos = i;
		Node* j = i->next;
		do
		{
			if (pos->info < j->info) {
				pos = j;
			}
			j = j->next;
		} while (j!=l.head);
		swap(i->info, pos->info);
		i = i->next;
	} while (i->next != l.head);
	
}


void interchangeSort(CircularLinkedList& l) {
	Node* i = l.head;
	do
	{
		Node* j = i->next;
		do
		{
			if (i->info < j->info) {
				swap(i->info, j->info);
			}
			j = j->next;
		} while (j!=l.head);
		i = i->next;
	} while (i->next!=l.head);
}

void bubbleSort(CircularLinkedList& l) {
	bool flag;
	Node* last = l.head;
	do
	{
		flag = false;
		Node* i = l.head;
		while (i->next != last) {
			if (i->info < i->next->info) {
				swap(i->info, i->next->info);
				flag = true;
			}
			i = i->next;
		}

		last = i;
	} while (flag==true);
}



void insOdered(CircularLinkedList& l,int x) {
	Node* p = createNode(x);
	if (l.head == nullptr) {
		l.head = l.tail = p;
		l.tail->next = l.head;
		return;
	}
	if (x > l.head->info) {
		p->next = l.head;
		l.head = p;
		l.tail->next = l.head;
		return;

	}
	Node* q = l.head;
	while (q->next != nullptr) {
		if (q->info > x && x > q->next->info) {
			p->next = q->next;
			q->next = p;
			return;
		}
		q = q->next;
	}
	q->next = p;


}


void insertionSort(CircularLinkedList& l) {
	CircularLinkedList clone;
	init(clone);
	Node* tmp = l.head;
	
	do
	{
		insOdered(clone, tmp->info);
		tmp = tmp->next;
	} while (tmp!=l.head);
	clearNode(l);
	l = clone;
}



void printList(CircularLinkedList l) {
	Node* tmp = l.head;
	do
	{
		cout << tmp->info << " ";
		tmp = tmp->next;
	} while (tmp!=l.head);
	cout << endl;
}




	
int main() {
	CircularLinkedList l;
	init(l);

	createList(l, 4);
	insertionSort(l);
	printList(l);
	
	



	clearNode(l);
	
	
	if (l.head == nullptr ) {
		cout << "Da giai phong \n";
	}
	return 0;
}