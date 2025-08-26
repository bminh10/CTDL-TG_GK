#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct SinhVien {
	string hoten;
	long long mssv;
	string lop;
	float dtb;
};


void nhap1SV(SinhVien& sv) {
	cout << "===============\n";
	cout << "Nhap ho ten: ";
	getline(cin, sv.hoten);
	cout << "Nhap mssv";
	cin >> sv.mssv;
	cin.ignore();
	cout << "Nhap lop: ";
	getline(cin, sv.lop);
	cout << "Nhap dtb: ";
	cin >> sv.dtb;
	cout << "===============\n";
}

void xuat1SV(SinhVien sv) {
	cout << "===============\n";
	cout << " ho ten: " << sv.hoten << endl;
	
	cout << " mssv: " << sv.mssv << endl;
	cout << " lop: " << sv.lop << endl;
	cout << " dtb: " << sv.dtb << endl;
	cout << "===============\n";
}


struct Node {
	SinhVien info;
	Node* next, * prev;
};

struct DoublyLinkedList {
	Node* head, * tail;
};

Node* createNode(SinhVien x) {
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	p->prev = nullptr;
	return p;
}

void addLast(DoublyLinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	if (l.head == nullptr) {
		l.head = l.tail = p;
		return;
	}
	l.tail->next = p;
	p->prev = l.tail;
	l.tail = p;

}

void readFile(DoublyLinkedList& l) {
	ifstream fin;
	fin.open("SinhVien.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			SinhVien x;
			fin >> x.mssv;
			fin.ignore();
			getline(fin, x.hoten, '#');
			getline(fin, x.lop, '#');
			fin >> x.dtb;
			addLast(l, x);
		}

		fin.close();
	}
}

void delFirst(DoublyLinkedList& l) {
	if (l.head == nullptr) {
		return;
	}
	Node* tmp = l.head;	
	if (l.head == l.tail) {
		l.head = l.tail = nullptr;
		delete tmp;
		return;
	}

	l.head = tmp->next;
	l.head->prev = nullptr;
	tmp->next = nullptr;
	delete tmp;


}


void xuatDS(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		xuat1SV(tmp->info);
		tmp = tmp->next;
	}
	cout << endl;
}

void xuatHoten(SinhVien sv) {
	cout << "========HOTEN======\n";
	cout << "Ho ten: " << sv.hoten << endl;
	cout << "===================\n";
}
void xuatMSSV(SinhVien sv) {
	cout << "========MSSV======\n";
	cout << "MSSV: " << sv.mssv << endl;
	cout << "===================\n";
}
void xuatLop(SinhVien sv) {
	cout << "========LOP======\n";
	cout << "LOP: " << sv.lop << endl;
	cout << "===================\n";
}
void xuatDTB(SinhVien sv) {
	cout << "========DTB======\n";
	cout << "DTB: " << sv.dtb << endl;
	cout << "===================\n";
}

void xuatRutGon(DoublyLinkedList l) {
	int c=-1;
	string yeucau;
	
	do
	{
		cout << "Ban muon xuat DS theo (mssv,hoten,lop,dtb): ";
		cin >> yeucau;
		if (yeucau == "mssv") {
			Node* tmp = l.head;
			while (tmp != nullptr) {
				xuatMSSV(tmp->info);
				tmp = tmp->next;
			}
			cout << endl;
		}
		else if (yeucau == "hoten") {
			Node* tmp = l.head;
			while (tmp != nullptr) {
				xuatHoten(tmp->info);
				tmp = tmp->next;
			}
			cout << endl;
		}
		else if (yeucau == "lop") {
			Node* tmp = l.head;
			while (tmp != nullptr) {
				xuatLop(tmp->info);
				tmp = tmp->next;
			}
			cout << endl;
		}
		else if(yeucau=="dtb"){
			Node* tmp = l.head;
			while (tmp != nullptr) {
				xuatDTB(tmp->info);
				tmp = tmp->next;
			}
			cout << endl;
		}
		cout << "Tiep tuc(bam 1)/ Ket thuc(bam 0) : ";
		cin >> c;
	} while (c!=0);
}

Node* search(DoublyLinkedList l, string name, string lop) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		if (tmp->info.hoten.compare(name) == 0 && tmp->info.lop.compare(lop) == 0) {
			return tmp;
		}
		tmp = tmp->next;
	}
	return tmp;
}


void delNode(DoublyLinkedList& l, Node*& tmp) {
	if (l.head == nullptr) {
		return;
	}
	Node* toDel = tmp;
	if (tmp == l.head) {
		if (l.head == l.tail) {
			l.head = l.tail = nullptr;
			tmp = nullptr;
			delete toDel;
			return;
		}
		l.head = tmp->next;
		tmp = l.head;
		tmp->prev = nullptr;
		toDel->next = nullptr;
		delete toDel;
		return;
	}
	if (tmp == l.tail) {
		if (l.tail == l.head) {
			l.head = l.tail = nullptr;
			tmp = nullptr;
			delete toDel;
			return;
		}
		l.tail = tmp->prev;
		tmp = tmp->next;
		l.tail->next = nullptr;
		toDel->prev = nullptr;
		delete toDel;
		return;
	}

	Node* toDelPre = toDel->prev;
	Node* toDelNext = toDel->next;

	tmp = tmp->next;
	toDelPre->next = toDel->next;
	toDelNext->prev = toDel->prev;
	toDel->next = nullptr;
	toDel->prev = nullptr;
	delete toDel;
	return;
}

void delClass(DoublyLinkedList& l, string lop) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		if (tmp->info.lop.compare(lop) == 0) {
			delNode(l, tmp);
		}
		else {
			tmp = tmp->next;
		}
	}
}



int compareDTB(SinhVien a, SinhVien b) {
	return a.dtb - b.dtb > 0 ? 1 : (a.dtb - b.dtb < 0 ? -1 : 0);
}

void bubbleSort(DoublyLinkedList& l) {
	for (Node* i = l.head; i->next != nullptr; i = i->next) {
		for (Node* j = l.tail; j != i; j = j->prev) {
			if (compareDTB(i->info, j->info) < 0) {
				swap(i->info, j->info);
			}
		}
	}
}

void insOdered(DoublyLinkedList& l,SinhVien x) {
	Node* p = createNode(x);
	if (l.head == nullptr) {
		l.head = p;
		return;
	}
	if (x.dtb > l.head->info.dtb) {
		p->next = l.head;
		l.head->prev = p;
		l.head = p;
		return;
	}
	Node* q = l.head;
	while (q != l.tail) {
		if (q->info.dtb > x.dtb && q->next->info.dtb < x.dtb) {
			p->next = q->next;
			q->next->prev = p;
			q->next = p;
			p->prev = q;
			return;
		}
		q = q->next;
	}
	q->next = p;
	p->prev = q;
}

void xemLinhHoat(DoublyLinkedList l) {
	if (l.head == nullptr) {
		return;
	}

	int c = 1;
	Node* tmp = l.head;
	do
	{
		switch (c)
		{
		case 1: {
			cout << "Thong tin sinh vien hien tai dau tien trong ds \n";
			xuat1SV(tmp->info);

			break;
		}
		case 2: {
			tmp = tmp->next;
			if (tmp == nullptr) {
				cout << "Vuot ngoai pham vi ds ! \n";
				return;
			}
			cout << "Sinh vien tiep theo \n";
			xuat1SV(tmp->info);
			break;
		}
		case 3: {
			tmp = tmp->prev;
			if (tmp == nullptr) {
				cout << "Vuot ngoai pham vi ds ! \n";
				return;
			}
			cout << "Sinh vien truoc do \n";
			xuat1SV(tmp->info);

			break;
		}
		
		default:
			cout << "Khong co chuc nang ban vua nhap ! \n";
			break;
		}
		cout << "Coi sv hien tai(bam 1)/ coi sv tiep theo(bam 2) / coi sv truoc do(bam 3)/ ket thuc (bam 0): ";
		cin >> c;
		if (c == 0) {
			cout << "ket thuc chuong trinh \n";
			return;
		}
	} while (c!=0);
	
}

void init(DoublyLinkedList& l) {
	l.head = l.tail = nullptr;
}

void clearNode(DoublyLinkedList& l) {
	while (l.head != nullptr) {
		delFirst(l);
	}
}

int main() {
	DoublyLinkedList l;
	init(l);
	readFile(l);
	bubbleSort(l);
	xuatDS(l);

	xemLinhHoat(l);
	/*xuatRutGon(l);
	cin.ignore();
	string name;
	string lop;
	cout << "Nhap ten sinh vien can tim: ";
	getline(cin, name);
	cout << "Nhap ten lop sinh vien can tim: ";
	cin >> lop;
	
	Node* res = search(l, name, lop);
	if (res != nullptr) {
		cout << "Sinh vien ton tai trong ds ! \n";
		xuat1SV(res->info);
	}
	else {
		cout << "Sinh vien khong ton tai \n";
	}*/

	/*string delLop;
	cout << "Nhap lop can xoa: ";
	cin >> delLop;
	delClass(l, delLop);
	cout << "=============KQ SAU KHI XOA==========\n";
	xuatDS(l);*/
	SinhVien sv;
	cout << "Nhap sinh vien can them: \n" ;
	nhap1SV(sv);
	insOdered(l, sv);
	cout << "===============KQ SAU KHI THEM==============\n" << endl;
	
	xuatDS(l);
	return 0;
}