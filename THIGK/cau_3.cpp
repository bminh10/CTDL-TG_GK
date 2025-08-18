#include <iostream>
using namespace std;

//bool isNguyenTo(int n) {
//    if (n < 2) {
//        return false;
//    }
//    for (int i = 2; i <= sqrt(n); i++) {
//        if (n % i == 0) {
//            return false;
//        }
//    }
//    return true;
//}
//
//
//struct Node {
//    int info;
//    Node* next;
//};
//
//struct CircularLinkedList {
//    Node* head;
//    Node* tail;
//};
//
//void init(CircularLinkedList& l) {
//    l.head = l.tail = nullptr;
//}
//
//Node* createNode(int x) {
//    Node* p = new Node();
//    p->info = x;
//    p->next = nullptr;
//    return p;
//}
//
//void addLast(CircularLinkedList& l,int x) {
//    Node* p = createNode(x);
//    if (l.head == nullptr) {
//        l.head = l.tail = p;
//        l.tail->next = l.head;
//        return;
//    }
//    l.tail->next = p;
//    l.tail = p;
//    l.tail->next = l.head;
//}
//
//
//void delNode(CircularLinkedList& l, int x) {
//    if (l.head != nullptr) {
//        Node* tmp = l.head;
//        Node* pre = nullptr;
//        while (tmp->next != l.head && tmp->info != x) {
//            pre = tmp;
//            tmp = tmp->next;
//        }
//        //nut can xoa o vi tri dau tien
//        if (pre == nullptr) {
//            l.head = l.head->next;
//            l.tail->next = l.head;
//            tmp->next = nullptr;
//            delete tmp;
//        }
//        //xoa cuoi
//        else if (tmp == l.tail) {
//            l.tail = pre;
//            l.tail->next = l.head;
//            tmp->next = nullptr;
//            delete tmp;
//
//        }
//        //xoa giua
//        else {
//            pre->next = tmp->next;
//            tmp->next = nullptr;
//            delete tmp;
//        }
//    }
//}
//
//void delNode2(CircularLinkedList& l, Node*&tmp) {
//    if (l.head != nullptr) {
//        
//        Node* toDelete = tmp;
//        if (toDelete == l.head) {
//            l.head = l.head->next;
//            tmp = toDelete->next;
//            l.tail->next = l.head;
//            toDelete->next = nullptr;
//            delete toDelete;
//            return;
//        }
//
//        if (toDelete == l.tail) {
//            tmp = toDelete->next;
//            Node* pre = l.head;
//            while (pre->next != l.tail) {
//                pre = pre->next;
//            }
//            l.tail = pre;
//            l.tail->next = l.head;
//            toDelete->next = nullptr;
//            delete toDelete;
//            return;
//        }
//
//        tmp = toDelete->next;
//        Node* pre = l.head;
//        while (pre->next != toDelete) {
//            pre = pre->next;
//        }
//        pre->next = tmp;
//        toDelete = nullptr;
//        delete toDelete;
//        return;
//    }
//
//
//}
//
//
//
//
//
////nguoi dau tien dem 1 thi nguoi thu may la nguoi thang cuoc ?
//void createSTT(CircularLinkedList& l, int n) {
//    
//    for (int i = 1; i <= n; i++) {
//        addLast(l, i);
//    }
//
//
//}
//
//
//int countSL(CircularLinkedList l) {
//
//   
//
//    if (l.head != nullptr) {
//        if (l.head->next == l.tail) {
//            return 1;
//        }
//        int count = 0;
//        Node* tmp = l.head;
//        while (tmp!=l.tail) {
//            count++;
//            tmp = tmp->next;
//        }
//        count = count + 1;
//        return count;
//    }
//    return 0;
//
//}
//
//Node* findWinner(CircularLinkedList& l) {
//    Node* tmp = l.head;
//    int i = 1;
//    
//    while (countSL(l) > 1) {
//        if (isNguyenTo(i)) {
//            delNode2(l, tmp);
//        }
//        else {
//            tmp = tmp->next;
//        }
//        i++;
//    }
//
//    return tmp;
//
//}

struct Node {
    int info;
    Node* next;

};

struct CircularLinkedList {
    Node* head;
    Node* tail;
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

void addLast(CircularLinkedList& l,int x) {
    Node* p = createNode(x);
    if (l.head == nullptr) {
        l.head = l.tail = p;
        l.tail->next = l.head;
        return;
    }
    p->next = l.head;
    l.tail->next = p;
    l.tail = p;
    return;
}

void delFirst(CircularLinkedList& l) {
    if (l.head != nullptr) {
        Node* tmp = l.head;
        if (l.head == l.tail) {
            
            l.head = l.tail = nullptr;
            delete tmp;
            
        }
        else {
            l.head = l.head->next;
            l.tail->next = l.head;
            tmp->next = nullptr;

            delete tmp;
        }
       
      

    }
}



//tạo danh sách player
void createList(CircularLinkedList& l,int n) {
    for (int i = 1; i <= n; i++) {
        addLast(l, i);
    }

}

//kiểm tra snt
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

//xoá player r dời tmp tới vị trí tiếp theo
void delPlayer(CircularLinkedList& l, Node*& tmp) {
    if (l.head == nullptr) {
        return;
    }
    //nếu ds chỉ còn 1 người
    if (l.head == l.tail && tmp == l.head) {
        l.head = l.tail = nullptr;
        delete tmp;
        tmp = nullptr;
        return;
    }

    Node* toDel = tmp;
    //xoá ng ở vị trí head
    if (tmp == l.head) {
        //dời tmp tới người tiếp theo
        l.head = tmp->next;
        tmp = l.head;
        //điều chỉnh liên kết next tail trỏ về head mới
        l.tail->next = l.head;
        //xoá player trước đó của tmp
        toDel->next = nullptr;
        delete toDel;
        return;
    }


    //xoá ng ở vị trí tail
    if (tmp == l.tail) {
        //tìm vị trí trước tail để dời tail
        Node* pre = l.head;
        while (pre->next != l.tail) {
            pre = pre->next;
        }
        //dời tail 
        l.tail = pre;
        //điều chỉnh liên kết tail mới trỏ về head
        l.tail->next = l.head;
        //dời tmp vòng về head
        tmp = l.head;
        //xoá player trước đó của tmp
        toDel->next = nullptr;
        delete toDel;
        return;
    }

    //xoá người ở vị trí giữa
    //tìm vị trí trước player cần xoá để chỉnh liên kết tới player tiếp theo
    Node* pre = l.head;
    while (pre->next != tmp) {
        pre = pre->next;
    }
    //chỉnh liên kết tới player tiếp theo
    pre->next = tmp->next;
    //dời tmp tới player tiếp theo
    tmp = tmp->next;
    //xoá player trước đó của tmp
    toDel->next = nullptr;
    delete toDel;
    return;


}
//đếm sl người chơi
int countSL(CircularLinkedList l) {
    int count = 0;
    Node* tmp = l.head;
    while (tmp->next !=l. head) {
        count++;
        tmp = tmp->next;
    }
    count++;
    return count;
}

//tìm người còn lại trong vòng tròn nếu người đầu tiên đếm 1
Node* findWinner(CircularLinkedList &l) {
    int i = 1;
    
    Node* tmp = l.head;
    while (countSL(l) > 1) {
        
        if (isPrime(i)==true) {
            //xoá player đó và dời tmp tới player tiếp theo
            delPlayer(l, tmp);
        }
        else {
            tmp = tmp->next;
        }
        i++;

    }
    return tmp;
}










void printList(CircularLinkedList l) {
    
    Node* tmp = l.head;
    while (tmp->next != l.head) {
        cout << tmp->info << " ";
        tmp = tmp->next;
    }
    cout << tmp->info << endl;

}


void clearNode(CircularLinkedList& l) {
    while (l.head != nullptr) {
        delFirst(l);
    }
}
/*Nếu người chiến thắng là người thứ k vậy người bắt đầu đếm từ 1 là người thứ mấy? */
Node* findKWin(CircularLinkedList l, int k) {
    Node* batDau = l.head;
    //chạy lại game nhiều lần để tìm người đếm 1 cho k thắng
    do {
        //tạo danh sách mới sau mỗi lần chuyển player khác đếm 1 
        CircularLinkedList tmp;
        init(tmp);
        Node* cur = batDau;
        do {
            addLast(tmp, cur->info);
            cur = cur->next;
        } while (cur != batDau);

        //tìm người thắng cuộc thoả k khi người thứ tmp->info đếm 1 đầu tiên
        Node* res = findWinner(tmp);
        //nếu tìm được người đếm 1 để k thắng
        if (res->info == k) {
            clearNode(tmp);
            return batDau;
        }
        //giải phóng danh sách để tạo lại bản sao danh sách
        clearNode(tmp);
        //lặp lại trò chơi và người tiếp theo sẽ đếm 1 đầu tiên
        batDau = batDau->next;
    } while (batDau != l.head);
    //không tồn tại người đếm 1 để k thắng
    return nullptr;
}

int main()
{
    int n;
    cout << "Nhap sl nguoi choi: ";
    cin >> n;
    CircularLinkedList l;
    init(l);
    
    createList(l,n);
    
    printList(l);
    
    
    int k;
    cout << "Nhap nguoi chien thang: ";
    cin >> k;
    if (findKWin(l, k) == nullptr) {
        cout << "Khong co ai dem 1 de k thang";
        
    }
    else {
        cout << "Nguoi dem 1 la nguoi thu " << findKWin(l, k)->info << " de nguoi choi " << k << " thang \n";
    }
    

   

    

    clearNode(l);
    if (l.head == nullptr) {
        cout << "rong \n";
    }


    return 0;
}
