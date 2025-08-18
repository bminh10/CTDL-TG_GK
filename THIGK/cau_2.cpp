#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct SinhVien {
	long long mssv;
	string hoten;
	string lop;
	long sdt;
	float dtb;
};


struct Node {
	SinhVien info;
	Node* next;
	Node* prev;
};
struct DoublyLinkedList {
	Node* head;
	Node* tail;
};


void init(DoublyLinkedList& l) {
	l.head = l.tail = nullptr;
}

void nhap1SV(SinhVien& sv) {
	cout << "Nhap mssv: ";
	cin >> sv.mssv;
	cout << "Nhap ho ten: ";
	cin >> sv.hoten;
	cout << "Nhap lop: ";
	cin >> sv.lop;
	cout << "Nhap sdt: ";
	cin >> sv.sdt;
	cout << "Nhap dtb: ";
	cin >> sv.dtb;
}
Node* createNode(SinhVien x){
	Node* p = new Node();
	p->info = x;
	p->next = nullptr;
	p->prev = nullptr;
	return p;
}

//them 1 node o cuoi
void addLast(DoublyLinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	//khi ds rong
	if (l.head == nullptr) {
		l.head = l.tail = p;
		return;
	}
	l.tail->next = p;
	p->prev = l.tail;
	l.tail = p;


}
void delLast(DoublyLinkedList& l) {
	if (l.head != nullptr) {
		//ds chi con 1 phan tu
		Node* tmp = l.tail;
		if (l.head == l.tail) {
			l.head = l.tail = nullptr;
			delete tmp;
			return;
		}
		l.tail = tmp->prev;
		l.tail->next = nullptr;
		tmp->prev = nullptr;
		delete tmp;

	}
}


void readFile(DoublyLinkedList& l) {
	ifstream fin;
	fin.open("SinhVien.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			SinhVien sv;
			fin >> sv.mssv;
			fin.ignore();
			getline(fin, sv.hoten, '#');
			getline(fin, sv.lop, '#');
			fin >> sv.sdt;
			fin.ignore();
			fin >> sv.dtb;

			addLast(l, sv);
		}



		fin.close();
	}

}


void xuat1SV(SinhVien sv) {
	cout << "=====================================\n";
	cout << "mssv: " << sv.mssv <<  endl;
	
	cout << "ho ten: " << sv.hoten << endl;
	
	cout << "lop: " << sv.lop << endl;
	
	cout << "sdt: " << sv.sdt << endl;
	
	cout << "dtb: " << sv.dtb << endl;
	cout << "=====================================\n";
}
void nhapDS(DoublyLinkedList& l) {
	int c;
	do {
		cout << "Nhap 1 sv: " << endl;
		SinhVien sv;
		nhap1SV(sv);
		addLast(l, sv);
		cout << "Tiep tuc (1)/ Ket thuc (0):  ";
		cin >> c;
	} while (c != 0);
}

void xuatDS(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		xuat1SV(tmp->info);
		tmp = tmp->next;
	}
	cout << endl;
}
void xuatMSSV(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		cout << "===================\n";
		cout << tmp->info.mssv << " ";
		cout << "===================\n";
		tmp = tmp->next;
	}
}
void xuathoTen(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		cout << "===================\n";
		cout << tmp->info.hoten << " ";
		cout << "===================\n";
		tmp = tmp->next;
	}
}
void xuatSdt(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		cout << "===================\n";
		cout << tmp->info.sdt << " ";
		cout << "===================\n";
		tmp = tmp->next;
	}
}void xuatDtb(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		cout << "===================\n";
		cout << tmp->info.dtb << " ";
		cout << "===================\n";
		tmp = tmp->next;
	}
}void xuatLop(DoublyLinkedList l) {
	Node* tmp = l.head;
	while (tmp != nullptr) {
		cout << "===================\n";
		cout << tmp->info.lop << " ";
		cout << "===================\n";
		tmp = tmp->next;
	}
}

string toLower(string str) {
	string tmp = "";
	int len = str.length();
	for (int i = 0; i < len; i++) {
		tmp += tolower(str[i]);
	}
	return tmp;
}


//xuat rut gon
void xuatRutGon(DoublyLinkedList l,string dieukien ) {
	if (dieukien == "mssv") {
		xuatMSSV(l);
		return;
	}
	if (dieukien == "hoten") {
		xuathoTen(l);
		return;
	}
	if (dieukien == "lop") {
		xuatLop(l);
		return;
	}
	if (dieukien == "sdt") {
		xuatSdt(l);
		return;
	}
	if (dieukien == "dtb") {
		xuatDtb(l);
		return;
	}

}
//kiem tra sinh vien co ton tai hay chua
Node* search(DoublyLinkedList l, string lop) {
	for (Node* i = l.head; i != nullptr; i = i->next) {
		if (lop == i->info.lop) {
			return i;
		}
	}
	return NULL;
}
//xoa sv thuoc lop do
//xoa node bat ki NHƯNG CHƯA CHỈNH TMP
void delNode(DoublyLinkedList& l, SinhVien x) {
	if (l.head != nullptr) {
		Node* tmp = l.head;
		while (tmp != nullptr && tmp->info.lop != x.lop) {
			tmp = tmp->next;
		}
		//khi tim thay sv can xoa
		if (tmp != nullptr) {
			//sv can xoa o dau 
			if (tmp == l.head) {
				if (l.head == l.tail) {
					l.head = l.tail = nullptr;
					delete tmp;
					return;
				}
				l.head = l.head->next;
				tmp->next = nullptr;
				l.head->prev = nullptr;
				delete tmp;
				return;
			}
			if (tmp == l.tail) {
				l.tail = tmp->prev;
				l.tail->next = nullptr;
				tmp->prev = nullptr;
				delete tmp;
				return;
			}
			Node* tmpNext = tmp->next;
			Node* tmpPre = tmp->prev;
			tmpNext->prev = nullptr;
			tmpPre->next = nullptr;
			tmp->next = nullptr;
			tmp->prev = nullptr;
			delete tmp;
			return;
		}

	}

}
//VUA XOA TAI VI TRI BAT KI XONG SE CHINH LAI TMP TRỎ TỚI NODE TIẾP THEO
void delX(DoublyLinkedList& l, Node*& tmp) {
	if (l.head != nullptr) {
		Node* toDel = tmp;
		//neu node can xoa la node dau
		if (tmp == l.head) {
			//neu ds chi con 1 phan tu
			if (l.head == l.tail) {
				l.head = l.tail = nullptr;
				tmp = nullptr;
				delete toDel;
				return;
			}
			l.head = l.head->next;
			tmp = l.head;
			toDel->next = nullptr;
			delete toDel;
			return;
		}
		//neu node can xoa la node cuoi
		if (tmp == l.tail) {
			l.tail = tmp->prev;
			l.tail->next = nullptr;
			tmp = nullptr;
			toDel->prev = nullptr;
			delete toDel;
			return;
		}
		//neu node can xoa o giua
		tmp = tmp->next;
		Node* toDelNext = toDel->next;
		Node* toDelPrev = toDel->prev;
		toDelNext->prev = toDel->prev;
		toDelPrev->next = toDel->next;
		toDel->next = nullptr;
		toDel->prev = nullptr;
		delete toDel;
		return;


	}
}


//xoa sinh vien bat ki
void delSV(DoublyLinkedList& l, string lop) {
	if (l.head != nullptr) {
		Node* tmp = l.head;
		while (tmp != nullptr) {
			if (tmp->info.lop == lop) {
				//delNode(l,tmp->info); //sau khi xoa neu khong dieu chinh tmp thi se mat dau 
				////FIX LAI NEU GAP SV DUNG LOP CAN TIM DE XOA -> Tao toDel luu sv can xoa, doi tmp sang sv ke tiep va xoa toDel ( trien khai bang ham moi: delX(...) )
				//tmp = l.head; //dieu chinh lai tmp sau khi xoa 1 node trong list
				delX(l, tmp);

			}
			else {
				tmp = tmp->next; //neu khon thoa dieu kien thi xet tmp ke tiep
			}
			
		}
	}
}

//Viết hàm sắp xếp danh sách sinh viên theo thứ tự giảm dần theo điểm trung bình.
int compare(SinhVien a, SinhVien b) {
	return a.dtb - b.dtb > 0 ? 1 : (a.dtb-b.dtb< 0? -1 : 0);
}

void interchangeSort(DoublyLinkedList& l, int func(SinhVien, SinhVien)) {
	for (Node* i = l.head; i->next != nullptr; i = i->next) {
		for (Node* j = i->next; j != nullptr; j = j->next) {
			if (func(i->info, j->info) < 0) {
				swap(i->info, j->info);
			}
		}
	}
}
/*Cho phép người dùng chèn thêm 1 sinh viên mới vào danh sách nhưng không làm thay đổi 
thứ tự đã sắp xếp.*/
void insOdered(DoublyLinkedList& l, SinhVien x) {
	Node* p = createNode(x);
	//neu ds rong -> coi nhu da co thu tu
	if (l.head == nullptr) {
		l.head = l.tail = p;
		return;
	}
	//neu diem trung binh sinh vien can them lon hon diem trung binh sinh vien dau danh sach
	if (x.dtb > l.head->info.dtb) {
		p->next = l.head;
		l.head->prev = p;
		l.head = p;
		return;
	}
	Node* tmp = l.head;
	//tim vi tri them o giua cho toi khi tmp = l.tail thi dung
	while (tmp->next != nullptr) {
		//neu diem trung binh sinh vien can them nho hon diem trung binh sinh vien truoc va lon hon diem trung binh sinh vien sau thi add giua
		if (tmp->info.dtb > x.dtb && tmp->next->info.dtb < x.dtb) {
			p->next = tmp->next;
			tmp->next->prev = p;
			p->prev = tmp;
			tmp->next = p;
			return;                         
		}
		tmp = tmp->next;
	}
	//them vao cuoi sau khi duyet qua toan bo vi tri o giua nhung khong tim thay vi tri phu hop de them
	tmp->next = p;
	p->prev = tmp;
	return;


}
/*Cho phép người dùng xem thông tin từng sinh viên, người dùng có thể linh hoạt chuyển 
đến sinh viên kế tiếp hoặc quay lại sinh viên đã xem trước đó. */
void xemLinhHoat(DoublyLinkedList l) {
	Node* tmp = l.head;
	int c;
	
	do {
		if (tmp != nullptr) {
			cout << "Ban muon coi sinh vien hien tai ( bam 1 ) / Ban muon coi sinh vien ke tiep ( bam 2 ) / quay lai sinh vien truoc do ( bam 3 ) / ket thuc ( bam 0 ): ";
			cin >> c;
			
			switch (c)
			{
			case 1: {
				system("cls");
				xuat1SV(tmp->info);
				break;
			}
			case 2: {
				system("cls");
				tmp = tmp->next;
				if (tmp == nullptr) {
					cout << "Da vuot ngoai pham vi danh sach \n";
					return;
				}
				xuat1SV(tmp->info);
				break;
			}
			case 3: {
				system("cls");
				tmp = tmp->prev;
				if (tmp == nullptr) {
					cout << "Da vuot ngoai pham vi danh sach \n";
					return;
				}
				xuat1SV(tmp->info);
				break;
			}
			case 0: {
				system("cls");
				cout << "Cam on ban da su dung he thong \n";
				return;
			}
			default:
				cout << "Khong co chuc nang ban vua chon trong he thong \n";
				break;

			}
			
		}
		
	} while (tmp != nullptr && c != 0);
}
//Viết hàm xuất danh sách ra tập tin để lưu trữ trên đĩa.
void ghiData(DoublyLinkedList l) {
	ofstream fout;
	fout.open("NewSinhVien.txt");
	if (fout.is_open()) {
		Node* tmp = l.head;
		while (tmp != nullptr) {
			fout << tmp->info.mssv << " " << tmp->info.hoten << " " << tmp->info.lop << " " << tmp->info.sdt << " " << tmp->info.dtb << " ";
			if (tmp->next != nullptr) {
				fout << endl;
			}
			tmp = tmp->next;
		}
		cout << "Da ghi data vao file txt ! \n";
		fout.close();
	}


}


int main() {
	DoublyLinkedList l;
	init(l);
	readFile(l);
	string dieukien;
	
	/*int c;
	do{
		cout << "Nhap thong tin ban chon de xuat(mssv,hoten,lop,sdt,dtb): ";
		getline(cin, dieukien);
		xuatRutGon(l, toLower(dieukien));
		
		cout << "Tiep tuc ( bam 1 ) / ket thuc ( bam 0 ): ";
		cin >> c;
		if (c == 0) {
			cout << "Da thoat chuong trinh xuat \n";
		}
		system("cls");
		cin.ignore();
	} while (c != 0);*/
	
	/*string hoten;
	string lop;
	cout << "Nhap ho ten sinh vien de kiem tra: ";
	getline(cin, hoten);
	cout << "Nhap ten lop sinh vien de kiem tra: ";
	getline(cin, lop);

	Node* res = search(l, lop);
	if (res != nullptr) {
		xuat1SV(res->info);
	}
	else {
		cout << "Khong ton tai sv do trongg ds !\n";
		
	}*/
	xuatDS(l);
	string lop;
	
	/*cout << "Nhap lop can xoa: ";
	getline(cin, lop);
	delSV(l, lop);
	cout << "============== sau khi xoa==================\n";
	xuatDS(l);
	
	interchangeSort(l, compare);
	cout << "=================KQ SAU KHI SAP XEP======================\n";
	xuatDS(l);
	

	cout << "Nhap thong tin sinh vien can them: \n";
	SinhVien sv;
	nhap1SV(sv);
	insOdered(l, sv);
	cout << "=================KQ SAU KHI THEM======================\n";
	xuatDS(l);*/

	xemLinhHoat(l);
	ghiData(l);
	return 0;
}