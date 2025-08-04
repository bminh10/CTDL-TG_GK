#include <iostream>
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
void addX(DS& l, int index,int x) {

	if (l.n < MAX && index < l.n) {
		if (index == l.n) {
			l.a[l.n] = x;
			l.n++;
			return;
		}

		for (int i = 0; i < l.n; i++) {
			if (i == index) {

				for(int j = l.n; j >= index; j--) {
					l.a[j] = l.a[j - 1];
				}
				l.a[index] = x;
				l.n++;
				return;

			}
		}
	


	}
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
	while (a.a[l] > pivot) {
		l++;
	}
	while (a.a[r] < pivot) {
		r--;
	}

	while (l <= r) {
		swap(a.a[l], a.a[r]);
		l++;
		r--;
	}
	
	if (l < right) {
		quickSort(a, l, right);
	}
	if (r > left) {
		quickSort(a, left, r);
	}
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
	
	cout << timMax2(l) << endl;
	
	heapSort(l);
	printList(l);
	

	return 0;
}