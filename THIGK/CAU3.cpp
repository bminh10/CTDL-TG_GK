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
        return;
    }
    l.tail->next = p;
    l.tail = p;
    l.tail->next = l.head;
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

void createList(CircularLinkedList& l,int n) {
    for (int i = 1; i <= n; i++) {
        addLast(l, i);
    }

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


void delPlayer(CircularLinkedList& l, Node*& tmp) {
    if (l.head != nullptr) {
        Node* toDel = tmp;
        if (tmp == l.head) {
            l.head = l.head->next;
            tmp = tmp->next;
            toDel->next = nullptr;
            l.tail->next = l.head;
            delete toDel;
            return;
        }
        if (tmp == l.tail) {
            Node* pre = l.head;
            while (pre->next != tmp) {
                pre = pre->next;
            }
            l.tail = pre;
            l.tail->next = l.head;
            toDel->next = nullptr;
            tmp = tmp->next;
            delete toDel;
            return;
        }
        Node* pre = l.head;
        while (pre->next != tmp) {
            pre = pre->next;
        }
        tmp = tmp->next;
        pre->next = tmp;
        toDel->next = nullptr;
        delete toDel;
        return;

    }


}

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


Node* findWinner(CircularLinkedList &l) {
    int i = 1;
    
    Node* tmp = l.head;
    while (countSL(l) > 1) {
        
        if (isPrime(i)==true) {
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

int main()
{
    int n;
    cout << "Nhap sl nguoi choi: ";
    cin >> n;
    CircularLinkedList l;
    init(l);
    
    createList(l,n);
    
    printList(l);
    cout << countSL(l) << endl;
    Node* res = findWinner(l);
    cout << "Nguoi thang cuoc la nguoi thu: " << res->info << endl;
    clearNode(l);
    if (l.head == nullptr) {
        cout << "ok\n";
    }


    return 0;
}
