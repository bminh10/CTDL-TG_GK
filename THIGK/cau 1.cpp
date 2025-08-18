#include <iostream>
#include<stack>
#define MAX 100
using namespace std;

struct DS {
	int a[MAX];
	int n;
};

void init(DS& l) {
	l.n = -1;
}

void nhapDS(DS& a) { 
	for (int i = 0; i < a.n; i++) {
		cout << "a[" << i << "] = ";
		cin >> a.a[i];
	}
}


void addFirst(DS &l,int x) {
	if (l.n < MAX) {
		for (int i = l.n; i >= 0; i--) {
			l.a[i] = l.a[i - 1];
		}
		l.a[0] = x;
		l.n++;
	}
	


}
void addLast(DS& l, int x) {
	if (l.n < MAX) {
		l.a[l.n] = x;
		l.n++;
	}
	
}

//thêm tại vị trí bất kì
//1 2 3 4 -> n=4 -> idx lần lượt : 0 1 2 3
void addX(DS& l, int index,int x) {
	//chỉ thêm khi n còn nhỏ hơn MAX và vị trí cần thêm không được vượt quá n
	if (l.n < MAX && index < l.n) {
		//vi tri can them la vi tri cuoi cung
		if (index == l.n) {
			l.a[l.n] = x; //gán phần tử vào vị trí cuối mảng
			l.n++;//tăng số lượng phần tử mảng
			return; //kết thúc không xét ở dưới 
		}

		for (int i = l.n; i > index; i--) {
			l.a[i] = l.a[i - 1]; //chuyển dời phần tử sang phải cho tới khi i = index thì dừng
		}
		l.a[index] = x; //gán tại vị trí cần thêm giá trị x
		l.n++;//tăng số lượng phần tử
	}
}

int  findMax(DS a) {
	
	int max = INT_MIN; //gán giá trị max là số nguyên nhỏ nhất ( dùng thư viện #include <climits>
	for (int i = 0; i < a.n; i++) {
		if (max < a.a[i]) { //nếu giá trị max nhỏ hơn giá trị mảng tại index i thì gán max = giá trị đó
			max = a.a[i]; //gán max
		}
	}
	return max;//Trả về giá trị lớn nhất
}


int timMax2(DS l) {
	int max1 = INT_MIN;
	for (int i = 0; i < l.n; i++) {
		if (l.a[i] > max1) {
			max1 = l.a[i];
		}
	}
	
	int max2 = INT_MIN;
	for (int j = 0; j < l.n; j++) {
		if (l.a[j] == max1) {
			continue;
		}
		else {
			if (l.a[j] > max2) {
				max2 = l.a[j];
			}
		}
	}
	return max2;


}
//vd: 1 2 3 4 -> n = 4 -> lan luot idx la 0 1 2 3 
//Xoa tai index bat ki
void delIdx(DS& a, int index) {
	//neu mang rong
	if (a.n <= 0) {
		return;
	}
	//index can xoa la vi tri cuoi mang
	if (index == a.n - 1) {
		a.n--; //giảm kích thước mảng
		return;
	}

	for (int i = index; i < a.n - 1; i++) {
		a.a[i] = a.a[i + 1]; //chuyển dời phần tử 
	}
	a.n--;//giảm kích thước mảng
	return;

}





void selectionSort(DS& a) {
	int max;
	for (int i = 0; i < a.n-1; i++) {
		max = i;
		for (int j = i; j < a.n; j++) {
			if (a.a[i] < a.a[j]) {
				max = j;
			}
		}
		swap(a.a[i], a.a[max]);
	}

}



void insertionSort(DS& a) {
	int pos,x;
	for (int i = 1; i < a.n; i++) {
		x = a.a[i];
		pos = i - 1;
		while (pos >= 0 && x > a.a[pos]) {
			a.a[pos + 1] = a.a[pos];
			pos--;
		}
		a.a[pos + 1] = x;
		

	}

}

void interchangeSort(DS& a) {
	for (int i = 0; i < a.n - 1; i++) {
		for (int j = i; j < a.n; j++) {
			if (a.a[i] < a.a[j]) {
				swap(a.a[i], a.a[j]);
			}
		}
	}
}


void bubbleSort(DS& a) {
	bool flag = true;
	for (int i = 0; i < a.n - 1; i++) {
		for (int j = a.n - 1; j > i; j--) {
			if (a.a[j - 1] < a.a[j]) {
				swap(a.a[j], a.a[j - 1]);
				flag = false;
			}
			
		}
		if (flag == true) {
			return;
		}

	}
}


void quickSort(DS& a,int left, int right) {
	int l = left;
	int r = right;
	int pivot = a.a[(left + right) / 2];
	while (l <= r) {
		while (a.a[l] > pivot) {
			l++;
		}
		while (a.a[r] < pivot) {
			r--;
		}

		if (l <= r) {
			swap(a.a[l], a.a[r]);
			l++;
			r--;
		}
	}
	if (l < right) {
		quickSort(a, l, right);
	}
	if (r > left) {
		quickSort(a, left, r);
	}
}

//quickSort không đệ quy

//linh hoạt thay đổi tăng hoặc giảm dần
bool ASC(int a, int b) {
	return a < b;
}
bool DESC(int a, int b) {
	return a > b;
}


//phân hoạch dãy
void phanHoach(DS &a, int &l, int &r,bool func(int,int)) {
	//cập nhật chốt
	int pivot = a.a[(l + r) / 2];

	/*Điều chỉnh dãy con trái < pivot 
				dãy con phải > pivot */
	while (l <= r) {
		while (func(a.a[l], pivot)) {
			l++;
		}
		while (func(pivot, a.a[r]) ) {
			r--;
		}
		
		if (l <= r) {
			swap(a.a[l], a.a[r]);
			l++;
			r--;
		}
	}

}
//quickSort dùng stack thay cho đệ quy
void quickSortStack(DS&list,bool func(int,int)) {
	int left = 0;
	int right = list.n - 1;

	//stack lưu dãy cần phân hoạch 
	stack<pair<int, int>>s;
	s.push({ left,right });
	do {
		left = s.top().first;
		right = s.top().second;

		int  l = left;
		int r = right;

		s.pop();
		phanHoach(list, l, r,func);

		//kiểm tra dãy còn phân hoạch được hay không
		if (l < right) {
			s.push({ l,right });
		}
		if (r > left) {
			s.push({ left,r  });
		}

		//lặp lại cho tới khi stack rỗng
	} while (!empty(s));
}



void heapify(DS& a,int n, int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int jmax = i;

	if (left < n && a.a[jmax] > a.a[left]) {
		jmax = left;
	}

	if (right< n && a.a[jmax] > a.a[right]) {
		jmax = right;
	}


	if(jmax != i) {
		swap(a.a[i], a.a[jmax]);

		heapify(a,n, jmax);

	}



}


void heapSort(DS &a) {
	//tim min heap
	int i = a.n / 2 - 1;
	while (i >= 0) {
		heapify(a, a.n,i);
		i--;
	}

	for (int right = a.n - 1; right > 0; right--) {
		swap(a.a[0], a.a[right]);
		heapify(a, right,0);
	}



}
//tiem kiem tuan tu
int search(DS a, int key) {
	for (int i = 0; i < a.n; i++) {
		if (a.a[i] == key) {
			return i;
		}
	}
	return -1;
}
//tim kiem nhi phan
int binarySearch(DS a, int key) {
	int l = 0;
	int r = a.n - 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (a.a[mid] == key) {
			return mid;
		}
		if (a.a[mid] < key) {
			l = mid +1; //key nam trong doan ben phai mid
		}
		else {
			r = mid - 1; //key nam trong doan ben trai mid
		}
	}
	return -1; //khong tim thay
}




void printList(DS a) {
	if (a.n == -1) {
		cout << "DS RONG\n";
		return;
	}
	for (int i = 0; i < a.n; i++) {
		cout << a.a[i] << " ";
	}
	cout << endl;
}





int main() {
	DS l;
	init(l);
	cout << "Nhap so luong phan tu: ";
	cin >> l.n;

	nhapDS(l);
	printList(l);
	quickSortStack(l,DESC);
	cout << "==============KQ SAU SAP XEP===========\n";
	printList(l);

	return 0;
}