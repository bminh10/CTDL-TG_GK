#include <iostream>
#include <stack>
#define MAX 100
using namespace std;

struct DS {
    int a[MAX];
    int n;
};

void init(DS& a) {
    a.n = -1;
}


void nhapDS(DS& a) {
    cout << "Nhap so luong phan tu: ";
    cin >> a.n;
    if (a.n > MAX || a.n < 1) {
        return;
    }
    for (int i = 0; i < a.n; i++) {
        cout << "a[" << i << "] = ";
        cin >> a.a[i];
    }

}

int search(DS a, int x) {
    for(int i = 0 ; i < a.n ; i ++){
        if (a.a[i] == x) {
            return i;
        }
    }
}

int binarySearch(DS a, int x) {
    int l = 0;
    int r = a.n - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a.a[mid] == x) {
            return mid;
        }
        if (x > a.a[mid]) {
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }
    return -1;
}

void delLast(DS& a) {
    if (a.n < 1) {
        return;
    }
    a.n--;
}


void addLast(DS& a, int x) {
    if (a.n < MAX) {
        a.a[a.n ] = x;
        a.n++;
    }
}

void addX(DS& a, int x , int index) {
    if (index >= 0 && index <= a.n) {
        if (index < a.n) {
            for (int i = a.n; i > index; i--) {
                a.a[i] = a.a[i - 1];
            }
            
        }
        a.a[index] = x;
        a.n++;
    }
}
void delX(DS& a, int index) {
    if (index >= 0 && index < a.n) {
        if (index < a.n - 1) {
            for (int i = index; i < a.n - 1; i++) {
                a.a[i] = a.a[i + 1];
            }
        }
        a.n--;

    }
}

bool ASC(int a, int b) {
    return a > b;
}
bool DESC(int a, int b) {
    return a < b;
}
   


void selectionSort(DS& a,bool func(int,int)) {
    int pos;
    for (int i = 0; i < a.n - 1; i++) {
        pos = i;
        for (int j = i + 1; j < a.n; j++) {
            if (func(a.a[pos],a.a[j])) {
                pos = j;
            }
        }
        swap(a.a[i], a.a[pos]);
    }
}


void insertionSort(DS& a,bool func(int ,int)) {
    int pos;
    for (int i = 1; i < a.n; i++) {
        int x = a.a[i];
        pos = i - 1;
        while (pos >= 0 && func(a.a[pos],x)) {
            a.a[pos + 1] = a.a[pos];
            pos--;
        }
        a.a[pos + 1] = x;
    }

}

void bubbleSort(DS& a) {
    bool flag = true;
    for (int i = 0; i < a.n - 1; i++) {
        for (int j = a.n; j > i; j--) {
            if (a.a[j - 1] < a.a[j]) {
                swap(a.a[j - 1], a.a[j]);
                flag = false;
            }
        }
        if (flag == true) {
            return;
        }
    }
}

void quickSortRec(DS& a,int left , int right,bool func(int,int)) {
    int l = left;
    int r = right;
    while (l <= r) {
        int pivot = a.a[(l + r) / 2];
        while (func(pivot,a.a[l])) {
            l++;
        }
        while (func(a.a[r], pivot)) {
            r--;
        }

        if (l <= r) {
            swap(a.a[l], a.a[r]);
            l++;
            r--;
        }
    }

    if (l < right) {
        quickSortRec(a, l, right,func);
    }
    if (r > left) {
        quickSortRec(a, left, r,func);
    }
}

void heapify(DS& a, int n, int i,bool func(int,int)) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int jmax = i;

    if (l < n && func(a.a[l], a.a[jmax]) ) {
        jmax = l;
    }
    if (r < n && func(a.a[r], a.a[jmax]) ) {
        jmax = r;
    }
    if (jmax != i) {
        swap(a.a[i], a.a[jmax]);
        heapify(a, n, jmax,func);
    }
}

void heapSort(DS& a,bool func(int,int)) {
    int i = a.n / 2 - 1;
    while (i >= 0) {
        heapify(a, a.n, i,func);
        i--;
    }
    for (int right = a.n - 1; right > 0; right--) {
        swap(a.a[0], a.a[right]);
        heapify(a, right, 0,func);
    }

}

void phanHoach(DS& a, int& l, int& r,bool func(int,int)) {
    int pivot = a.a[(l + r) / 2];
    while (l <= r) {
        while (func(pivot,a.a[l])) {
            l++;
        }
        while (func(a.a[r],pivot)) {
            r--;
        }

        if (l <= r) {
            swap(a.a[l], a.a[r]);
            l++;
            r--;
        }

    }
}


void quickSortNoRec(DS& a,bool func(int,int)) {
    stack<pair<int, int>>s;
    int left = 0;
    int right = a.n-1;
    s.push({ left,right });
    while (!empty(s)) {
        int l = s.top().first;
        int r = s.top().second;
        s.pop();
        left = l;
        right = r;
        phanHoach(a, l, r,func);
        if (l < right) {
            s.push({ l,right });
        }
        if (r > left) {
            s.push({ r,left });
        }


    }

}


void xuatDS(DS a) {
    if (a.n < 1) {
        return;
    }

    for (int i = 0; i < a.n; i++) {
        cout << a.a[i] << " ";
        
    }
    cout << endl;
}




int main()
{
    DS a;
    init(a);

    nhapDS(a);
    quickSortNoRec(a,ASC);
    xuatDS(a);

    int res1 = search(a, 2);
    int res2 = binarySearch(a, 5);
    if (res1 != -1) {
        cout << "Ton tai trong danh sach ! \n";
    }
    else {
        cout << "Khong ton tai \n";
    }

    if (res2 != -1) {
        cout << "Ton tai trong ds \n";
    }
    else {
        cout << "Khong ton tai \n";
    }



    return 0;
}


