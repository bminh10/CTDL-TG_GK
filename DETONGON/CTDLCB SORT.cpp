#include <iostream>
#include <stack>
#include <fstream>
using namespace std;
#define MAX 100
struct DS {
	int a[MAX];
	int n;
};

void init(DS& a) {
	a.n = -1;
}

void readFile(DS& a) {
	ifstream fin;
	fin.open("number.txt");
	if (fin.is_open()) {
		
		fin >> a.n;
		for (int i = 0; i < a.n; i++) {
			fin >> a.a[i];
			fin.ignore();
		}

		fin.close();
	}
}



void selectionSort(DS& a) {
	int pos;
	for (int i = 0; i < a.n - 1; i++) {
		pos = i;
		for (int j = i + 1; j < a.n; j++) {
			if (a.a[pos] < a.a[j]) {
				pos = j;
			}
		}
		swap(a.a[i], a.a[pos]);
	}
}

void insertionSort(DS& a) {
	int pos,x;
	for (int i = 1; i < a.n; i++) {
		x = a.a[i];
		pos = i - 1;

		while (pos >= 0 && a.a[pos] < x) {
			a.a[pos + 1] = a.a[pos];
			pos--;
		}

		a.a[pos + 1] = x;
	}

}

void bubbleSort(DS& a) {
	for (int i = 0; i < a.n - 1; i++) {
		for (int j = a.n - 1; j > i; j--) {
			if (a.a[j] > a.a[j - 1]) {
				swap(a.a[j], a.a[j - 1]);
			}
		}
	}
}

void quickSort(DS& a,int left , int right) {
	int l = left;
	int r = right;
	int pivot = a.a[(l + r) / 2];
	while (l <= r) {
		while (a.a[l] > pivot) {
			l++;
		}
		while (a.a[r] < pivot) {
			r--;
		}
		if (l <= r) {
			swap(a.a[l], a.a[r]);
			l ++;
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
void heapify(DS& a, int n, int i) {
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int jmax = i;
	if (l < n && a.a[l] < a.a[jmax]) {
		jmax = l;
	}
	if (r < n && a.a[r] < a.a[jmax]) {
		jmax = r;
	}
	if (jmax != i) {
		swap(a.a[i], a.a[jmax]);
		heapify(a, n, jmax);
	}

}

void heapSort(DS& a) {
	int i = a.n / 2 - 1;
	while (i >= 0) {
		heapify(a, a.n, i);
		i--;
	}

	for( int right = a.n-1; right > 0; right--) {
		swap(a.a[0], a.a[right]);
		heapify(a, right, 0);
	}

}
void phanHoach(DS& a, int& l, int& r) {
	int pivot = a.a[(l + r) / 2];
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

}

void quickSortNoRec(DS& a) {
	int left = 0;
	int right = a.n;

	stack<pair<int, int>>s;
	s.push({ left,right });
	while (!empty(s)) {
		int l = s.top().first;
		int r = s.top().second;
		s.pop();
		left = l;
		right = r;
		phanHoach(a, l, r);
		if (l < right) {
			s.push({ l,right });
		}
		if (r > left) {
			s.push({ left,r });
		}



	}

}

void print(DS a) {
	for (int i = 0; i < a.n; i++) {
		cout << a.a[i] << " ";
	}
	cout << endl;
}


int main() {
	DS a;
	init(a);
	readFile(a);
	quickSortNoRec(a);
	print(a);


	return 0;
}