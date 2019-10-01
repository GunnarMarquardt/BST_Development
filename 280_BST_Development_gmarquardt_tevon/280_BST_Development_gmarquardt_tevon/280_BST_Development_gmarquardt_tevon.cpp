/*
280
BST Development
Gunnar Marquardt Thomas Evon
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
	int data;
	Node* left, * right;
};

class BST {
private:
	Node* root;
	Node* insert(int, Node*); //helper
	int getSize(Node*); //helper
	void displayInOrder(Node*); //helper
	int count(int, Node*);
	int countLeaves(Node*);
	int getHeight(Node*);
	bool isLeaf(Node*);
public:
	BST();
	void insert(int);
	void displayInOrder();
	int getSize();
	void insertNonRecursive(int);
	int count(int);
	int countLeaves();
	int getHeight();
}; //BST class

bool BST::isLeaf(Node* n) {
	if (n->left == nullptr && n->right == nullptr) {
		return true;
	}
	return false;
}

//helper functions
Node* BST::insert(int v, Node* r) {
	if (r == nullptr) {
		r = new Node;
		r->left = r->right = nullptr;
		r->data = v;
		return r;
	}
	else if (v < r->data) {
		r->left = insert(v, r->left);
		return r;
	}
	else {
		r->right = insert(v, r->right);
		return r;
	}
} //insert helper

void BST::displayInOrder(Node* r) {
	if (r != nullptr)
	{
		displayInOrder(r->left);
		cout << r->data << endl;
		displayInOrder(r->right);
	}
} //displayInOrder helper

int BST::getSize(Node* r) {
	if (r == nullptr)
		return 0;
	else
		return 1 + getSize(r->left) + getSize(r->right);
} //getSize helper

int BST::count(int v, Node* n) {
	if (n == nullptr) {
		return 0;
	}
	else {
		int c = 0;
		if (n->data == v) {
			c = 1;
		}
		return count(v, n->left) + count(v, n->right) + c;
	}
}

int BST::getHeight(Node* n) {
	if (n == nullptr) {
		return 0;
	}
	else if (isLeaf(n)) {
		return 1;
	}
	else {
		return max(getHeight(n->left), getHeight(n->right)) + 1;
	}
}

int BST::countLeaves(Node* n) {
	if (n == nullptr) {
		return 0;
	}
	else if (isLeaf(n)) {
		return 1;
	}
	else {
		return countLeaves(n->left) + countLeaves(n->right);
	}
}

//constructors
BST::BST() {
	root = nullptr;
} //BST


//setters
void BST::insert(int v) {
	root = insert(v, root);
} //insert

void BST::insertNonRecursive(int v) {
	Node* prev = nullptr;
	Node* r = root;
	while (r != nullptr) {
		prev = r;
		if (v < r->data) {
			r = r->left;
			prev->left = r;
		}
		else {
			r = r->right;
			prev->right = r;
		}
	}
	r = new Node;
	r->data = v;
	r->left = r->right = nullptr;
}

//getters
int BST::getSize() {
	return getSize(root);
} //getSize

int BST::count(int v) {
	return count(v, root);
}

int BST::countLeaves() {
	return countLeaves(root);
}

int BST::getHeight() {
	return getHeight(root);
}

//utility
void BST::displayInOrder() {
	displayInOrder(root);
} //displayInOrder

int main() {
	BST bst1 = BST();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(20);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(10);
	bst1.insert(30);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(5);
	bst1.insert(40);
	bst1.insert(25);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;

	bst1.insert(0);
	bst1.insert(2);
	bst1.insert(-5);
	bst1.insert(-2);
	bst1.displayInOrder();
	cout << "Size: " << bst1.getSize() << endl << endl;
} //main

