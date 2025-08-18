#include "QueueTinhTien.h"
#include <stack>
#include <cmath>

//khoi tao rong cay
void initTree(Node*& root) {
	root = nullptr;
}

Node* createNode(int x) {
	Node* p = new Node();
	p->info = x;
	p->left = nullptr;
	p->right = nullptr;
	p->height = 1;
	return p;
}

//Thêm nút mới vào cây
void addNode(Node*& root, int x) {
	if (root == nullptr) {
		root = createNode(x);
		return;
	}
	else if (x > root->info) {
		addNode(root->right, x);
	}
	else {
		addNode(root->left, x);
	}

}
//Xoá một nút trong cây. (de quy)
void delNode(Node*& root, int x) {
	if (root != nullptr) {
		if (x > root->info) {
			delNode(root->right, x);
		}
		else if (x < root->info) {
			delNode(root->left, x);
		}
		else {
			if (root->left == nullptr && root->right == nullptr) {
				Node* p = root;
				root = nullptr;
				delete p;
				return;
			}
			else if (root->left != nullptr && root->right != nullptr) {
				Node* tmp = root->right;
				while (tmp->left != nullptr) {
					tmp = tmp->left;
				}
				root->info = tmp->info;
				delNode(root->right, tmp->info);
			}
			else {
				Node* p = root;
				if (root->left == nullptr) {
					root = root->right;
				}
				else {
					root = root->left;
				}
				delete p;
				return;
			}

		}
	}
}
//xoa mot nut trong cay ( khong de quy ) 
void delNode2(Node*& root, int x) {
	Node* tmp = root;
	Node* parent = nullptr;
	while (tmp != nullptr && tmp->info != x) {
		parent = tmp;
		if (x > tmp->info) {
			tmp = tmp->right;
		}
		else if (x < tmp->info) {
			tmp = tmp->left;
		}
	}
	//neu tim thay vi can can them
	if (tmp != nullptr) {
		//nut can xoa la nut la hoac nut bac 1
		if (tmp->left == nullptr || tmp->right == nullptr) {
			Node* q = tmp;
			if (tmp->left == nullptr) {
				q = tmp->right;
			}
			else {
				q = tmp->left;
			}
			//nut can xoa la nut goc
			if (parent == nullptr) {
				root = q;
				delete tmp;
				return;
			}
			else {
				if (parent->info > tmp->info) {
					parent->left = q;
				}
				else {
					parent->right = q;
				}
				delete tmp;
				return;
			}
		}
		else {
			//nut can xoa la nut bac 2
			Node* p = tmp->right;
			parent = NULL;
			while (p->left != nullptr) {
				parent = p;
				p = p->left;
			}
			tmp->info = p->info;

			if (parent == nullptr) {
				tmp->right = nullptr;
				delete p;
				return;
			}
			else {
				parent->left = p->right;
				delete p;
				return;
			}


		}

	}



}
//giai phong cay
void clearNode(Node*& root) {
	while (root != nullptr) {
		delNode(root, root->info);
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
///Duyệt cây: LNR, LRN, NLR dùng đệ quy 
//duyet trung tu (inoder,LNR)
void LNR(Node* root) {
	if (root != nullptr) {
		LNR(root->left);
		cout << root->info << " ";
		LNR(root->right);
	}
}
//Duyet tien tu ( preOder, NLR)
void NLR(Node* root) {
	if (root != nullptr) {
		cout << root->info << " ";
		NLR(root->left);
		NLR(root->right);
	}
}
//Duyet hau tu ( postOder, LRN) 
void LRN(Node* root) {
	if (root != nullptr) {
		LRN(root->left);
		LRN(root->right);
		cout << root->info << " ";

	}
}

//Duyệt cây: LNR, LRN, NLR không đệ quy
//Duyet Trung tu, inOder, LNR
void stackLNR(Node* root) {
	Node* tmp = root;
	stack<Node*>s;
	while (tmp != nullptr || !empty(s)) {
		while (tmp != nullptr) {
			s.push(tmp);
			tmp = tmp->left;
		}
		tmp = s.top();
		s.pop();
		cout << tmp->info << " ";
		tmp = tmp->right;


	}
	cout << endl;
}

//duyet tien tu, preOder, NLR
void stackNLR(Node* root) {
	Node* tmp = root;
	stack<Node*>s;
	while (tmp != nullptr || !empty(s)) {
		while (tmp != nullptr) {
			cout << tmp->info << " ";
			s.push(tmp);
			tmp = tmp->left;
		}
		tmp = s.top();
		s.pop();
		tmp = tmp->right;

	}
}
//Duyet hau tu, postOder, LRN
void stackLRN(Node* root) {
	Node* tmp = root;
	stack<Node*>s1;
	stack<Node*>s2;
	s1.push(tmp);
	while (!empty(s1)) {
		tmp = s1.top();
		s1.pop();
		s2.push(tmp);
		if (tmp->left != nullptr) {
			s1.push(tmp->left);
		}
		if (tmp->right != nullptr) {
			s1.push(tmp->right);
		}
	}
	while (!empty(s2)) {
		cout << s2.top()->info << " ";
		s2.pop();
	}
	cout << endl;
}
//Duyet chieu rong cua cay( dung queue)
//void duyetChieuRong(Node* root) {
//	if (root != nullptr) {
//		queue<Node*> s;
//		Node* tmp;
//		s.push(root);
//		
//		while (!empty(s)) {
//			tmp = s.front();
//			s.pop();
//			if (tmp->left != nullptr) {
//				s.push(tmp->left);
//			}
//			if (tmp->right != nullptr) {
//				s.push(tmp->right);
//			}
//			cout << tmp->info << " ";
//		}
//		cout << endl;
//	}
//}





//duyet cay theo chieu rong Queue( dung ds dac xu ly tran bang pp Vong)

//void duyetQueueVong(Node* root) {
//	Node* tmp;
//	Queue q;
//	init(q);
//
//	Push(q, root);
//	while (!isEmpty(q)) {
//		tmp = front(q);
//		pop(q);
//		cout << tmp->info << " ";
//		if (tmp->left != nullptr) {
//			Push(q, tmp->left);
//		}
//		if (tmp->right != nullptr) {
//			Push(q, tmp->right);
//		}
//	}
//
//
//}
//duyet cay theo chieu rong Queue( dung ds dac xu ly tran bang tinh tien) 
void duyetQueueTinhTien(Node* root) {
	Node* tmp;
	Queue q;
	init(q);
	push(q, root);
	while (!isEmpty(q)) {
		tmp = front(q);
		pop(q);
		cout << tmp->info << " ";
		if (tmp->left != nullptr) {
			push(q, tmp->left);
		}
		if (tmp->right != nullptr) {
			push(q, tmp->right);
		}
	}
	cout << endl;


}

//Viết hàm đếm số node chứa giá trị nguyên tố trong cây. 
bool isNguyenTo(int n) {
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


//dem nguyen to
int countPrime(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	if (isNguyenTo(root->info)) {
		return (countPrime(root->left) + countPrime(root->right)) + 1;
	}
	return countPrime(root->left) + countPrime(root->right);
}


//AVL
//tim max
int max(int a, int b) {
	return a > b ? a : b;
}
//lay chieu cao
int getHeight(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return root->height;
}
//cap nhat chieu cao
void updateHeight(Node*& root) {
	if (root != nullptr) {
		root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	}
}
//lay he so can bang
int getBalance(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return getHeight(root->left) - getHeight(root->right);
}
void leftRotate(Node*& root) {
	Node* q = root->right;
	Node* r = q->left;

	root->right = r;
	q->left = root;
	//cap nhat chieu cao 
	updateHeight(root);
	updateHeight(q);
	//q tro thanh nut goc moi
	root = q;
}

void rightRotate(Node*& root) {
	Node* q = root->left;
	Node* r = q->right;

	root->left = r;
	q->right = root;
	//cap nhatt chieu cao
	updateHeight(root);
	updateHeight(q);
	//q tro thanh nut goc moi
	root = q;

}
//them nhung van dam bao cay can bang
void addAVL(Node*& root, int x) {
	if (root == nullptr) {
		root = createNode(x);
	}
	else if (x > root->info) {
		addAVL(root->right, x);
	}
	else if (x < root->info) {
		addAVL(root->left, x);
	}
	else {
		return;
	}

	//cap nhat chieu cao
	updateHeight(root);

	//lay he so can bang
	int val = getBalance(root);

	if (val > 1 && x < root->left->info) {
		//mat can bang trai trai
		rightRotate(root);
	}
	else if (val < -1 && x > root->right->info) {
		//mat can bang phai phai
		leftRotate(root);
	}
	else if (val > 1 && x > root->left->info) {
		//mat can bang trai phai
		leftRotate(root->left);
		rightRotate(root);
	}

	else if( val < -1 && x < root->right->info){
		//mat can bang phai trai
		rightRotate(root->right);
		leftRotate(root);
	}
}

void searchStandFor(Node*& cur, Node*& temp) {
	//tim nut the mang
	if (temp->left != nullptr) {
		searchStandFor(cur, temp->left);
	}
	else {
		cur->info = temp->info;
		cur = temp;
		temp = temp->right;
	}
	
}



//xoa nhung van dam bao cay can bang
void delAVL(Node*& root, int x) {
		if(root==nullptr)
			return;
		if (x > root->info) {
			delAVL(root->right, x);
		}
		else if (x < root->info) {
			delAVL(root->left, x);
		}
		else {
			//nut can xoa la nut la hoac nutt bac 1
			Node* cur = root;

			if (root->right == nullptr || root->left == nullptr) {
				if (root->left == nullptr) {
					root = root->right;
				}
				else if (root->right == nullptr) {
					root = root->left;
				}

			}
			else {
				searchStandFor(cur, root->right);
			}
			delete cur;
		}
	
		//cap nhat chieu cao
		updateHeight(root);
		//lay he so can bang
		int val = getBalance(root);
		
		if (val < -1 && getBalance(root->right) <= 0) {
			//mat can bang phai phai
			leftRotate(root);

		}
		else if (val < -1 && getBalance(root->right)>0) {
			//mat can bang phai trai
			rightRotate(root->right);
			leftRotate(root);
		}
		else if (val > 1 && getBalance(root->left) >= 0) {
			//mat can bang trai trai
			rightRotate(root);

		}
		else if (val > 1 && getBalance(root->left) < 0) {
			//mat can bang trai phai
			leftRotate(root->left);
			rightRotate(root);
		}
}

//void searchStandFor(Node*& cur, Node*& temp) {
//	if (temp->left != NULL) {
//		searchStandFor(cur, temp->left);
//	}
//	else {
//		cur->info = temp->info;
//		cur = temp;
//		temp = temp->right;
//	}
//}
//
//void delNode3(Node*& root, const int key) {
//	if (root == NULL)
//		return;
//	if (key > root->info)
//		delNode(root->right, key);
//	else if (key < root->info)
//		delNode(root->left, key);
//	else {
//		//Tim thay node can xoa
//		Node* cur = root;
//		//TH1: node la hoac node bac
//		if (root->left == NULL)
//			root = root->right;
//		else if (root->right == NULL)
//			root = root->left;
//		else {
//			searchStandFor(cur, root->right);
//		}
//		delete cur;
//	}
//}




int main() {
	Node* root;
	initTree(root);
	addAVL(root, 30);
	addAVL(root, 20);
	addAVL(root, 50);
	addAVL(root, 60);
	addAVL(root, 70);
	
	
	/*duyetChieuRong(root);*/
	/*duyetQueueVong(root);*/
	/*duyetQueueTinhTien(root);
	cout << countPrime(root) << " ";*/
	
	duyetQueueTinhTien(root);
	
	cout << "Chieu cao cay: " << getHeight(root) << endl;
	cout << endl;



	clearNode(root);
	if (root == nullptr) {
		cout << "Xoa cay thanh cong \n";
	}

	return 0;
}