//Binary Search Tree
#include <iostream>
#include <stdlib.h>
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
	Node* insert(int, Node*); // helper
	int getSize(Node*); // helper
	void displayInOrder(Node*); // helper
	void displayPreOrder(Node*); // helper
	void display(Node*, int); // display helper
	int count(int, Node*); // count helper
	int countLeaves(Node*); // countLeaves helper
	int getHeight(Node*); // getHeight helper
	bool isLeaf(Node*); 
public:
	BST();
	void insert(int);
	void displayInOrder();
	int getSize();
	int maxValue();
	Node* find(int);
	void deleteNode(int); 
	void load(int, int, int);
	void displayPreOrder(); 
	void display(); 
	void insertNonRecursive(int);
	int count(int);
	int countLeaves();
	int getHeight();
}; //BST class

int main() {
	int input, num;
	Node* temp;
	BST bst = BST();
	while (1) {
		cout << endl << endl;
		cout << ">>>>>>>>>>>>>>>>>>>>>" << endl;
		cout << "Choose Your Function:" << endl;
		cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
		cout << "1.Insert Recursive" << endl;
		cout << "2.Delete Node" << endl;
		cout << "3.Load" << endl;
		cout << "4.Preorder Display (VLR)" << endl;
		cout << "5.Pretty Tree Display" << endl;
		cout << "6.Display in Order" << endl;
		cout << "7.Find Max Value in BST" << endl;
		cout << "8.Get Number of Nodes (getSize)" << endl;
		cout << "9.Find a Node" << endl;
		cout << "10.Quit" << endl;
		cout << endl <<"Enter your choice : ";
		cin >> input;
		switch (input) {
		case 1:
			cout << "Insert (enter int): ";
			cin >> num;
			bst.insert(num);
			break;
		case 2:
			cout << "Enter int to delete: ";
			cin >> num;
			bst.deleteNode(num);
			break;
		case 3:
			int howMany, min, max;
			cout << "Enter howMany, min, and max: ";
			cin >> howMany >> min >> max; 
			bst.load(howMany, min, max);
			break;
		case 4:
			cout << endl << "Pre Order Display tree:" << endl
				<< "--------------------" << endl;
			bst.displayPreOrder();
			break;
		case 5:
			cout << endl << "Display pretty tree:" << endl 
				 << "--------------------" << endl;
			bst.display();
			break;
		case 6:
			cout << endl << "Display In Order:" << endl
				<< "--------------------" << endl;
			bst.displayInOrder();
			break;
		case 7:
			cout << "The max value in the BST is: " << bst.maxValue(); 
			break; 
		case 8: 
			cout << "The number of nodes are: " << bst.getSize();
			break;
		case 9:
			Node* target;
			cout << "Enter the int of the node you want to find: ";
			cin >> num;
			target = bst.find(num);
			cout << "Node* target->data: " << target->data; 
			break;  
		case 10:
			cout << "Program TERMINATED" << endl;
			exit (0);
			break; 
		}

	}
	return 0;
}

// ------------------------Function Definitions ------------------------

// Constructor
BST::BST() {
	root = nullptr;
} //BST

// inserters
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
		r->right = insert(v, r->right); // r->right is assigned the new node that will be created to the right
		return r;
	}
} //insert helper

void BST::insert(int v) {
	root = insert(v, root);
} //insert (recursive)

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

// displayers
void BST::displayInOrder(Node* r) {
	if (r != nullptr) {
		displayInOrder(r->left);
		cout << r->data << endl;
		displayInOrder(r->right);
	}
} //displayInOrder helper

void BST::displayInOrder() {
	displayInOrder(root);
} //displayInOrder

void BST::displayPreOrder(Node* r) {
	if (root == nullptr)
	{
		cout << "ERROR: Tree does not exist" << endl;
		return;
	}
	if (r != nullptr)
	{
		cout << r->data << "  " << endl;
		displayPreOrder(r->left);
		displayPreOrder(r->right);
	}
} //displayPreOrder helper

void BST::displayPreOrder() {
	displayPreOrder(root);
}

void BST::display(Node* ptr, int level)
{
	if (ptr != nullptr)
	{
		display(ptr->right, level + 1);
		cout << endl;
		if (ptr == root)
			cout << "Root->:  ";
		else
		{
			for (int i = 0; i < level; i++)
				cout << "       ";
		}
		cout << ptr->data;
		display(ptr->left, level + 1);
	}
} // display helper

void BST::display() {
	display(root, 1);
} // display (pretty tree)

// getters
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
} //getHeight helper

int BST::getHeight() {
	return getHeight(root);
}

int BST::getSize(Node* r) {
	if (r == nullptr) return 0;
	else return 1 + getSize(r->left) + getSize(r->right);
} //getSize helper

int BST::getSize() {
	return getSize(root);
} 

int BST::maxValue() {
	Node* r = root;
	Node* parent = r;
	while (r != nullptr) {
		parent = r;
		r = r->right;
	}
	int target = parent->data;
	return target;
}

// utility
void BST::deleteNode(int v) {
	Node* target = root;
	Node* parent = nullptr;

	// find node
	while (target != nullptr) {
		if (v > target->data) {
			parent = target;
			target = target->right;
			if (target->data == v) break;
		}
		else if (v < target->data) {
			parent = target;
			target = target->left;
			if (target->data == v) break;
		}
	}

	if (root->data < v) {
		if (target->left == nullptr && target->right == nullptr) { //delete leaf Node
			if (parent->left == target) parent->left = nullptr;
			else parent->right = nullptr;
			return;
		}
		else if (target->left == nullptr || target->right == nullptr) { //delete node w/ one child
			if (target->left == nullptr) parent->right = target->right;
			else if (target->right == nullptr) parent->right = target->left;
		}
		else { // delete node that has two children
			Node* runner = target->left;
			parent = target;
			if (runner->right != nullptr) {
				while (runner->right != nullptr) {
					parent = runner;
					runner = runner->right;
				}
				target->data = runner->data;
				parent->right = nullptr;
			}
			else if (runner->right == nullptr) {
				target->data = runner->data;
				parent->left = nullptr;
			}
		}
	}
	else if (root->data > v) {
		if (target->left == nullptr && target->right == nullptr) { //delete leaf Node
			if (parent->left == target) parent->left = nullptr;
			else parent->right = nullptr;
			return;
		}
		else if (target->left == nullptr || target->right == nullptr) { //delete node w/ one child
			if (target->left == nullptr) parent->left = target->right;
			else if (target->right == nullptr) parent->left = target->left;
		}
		else { // delete node that has two children
			Node* runner = target->right;
			parent = target;
			if (runner->right != nullptr) {
				while (runner->right != nullptr) {
					parent = runner;
					runner = runner->right;
				}
				target->data = runner->data;
				parent->right = nullptr;
			}
			else if (runner->left == nullptr) {
				target->data = runner->data;
				parent->right = nullptr;
			}
		}
	}
}

Node* BST::find(int v) {
	Node* r = root;
	Node* errorPtr = nullptr;
	while (r != nullptr) {
		if (r->data == v)
			return r;
		else if (v > r->data)
			r = r->right;
		else if (v < r->data)
			r = r->left;
	}
	cout << v << " is not in this BST!" << endl;
	errorPtr->data = INT_MAX;
	return errorPtr; 
}

void BST::load(int howMany, int minVal, int maxVal) {
	if (root == nullptr) {
		int newRoot = (minVal + maxVal) / 2;
		insert(newRoot);
	}
	insert(minVal);
	insert(maxVal);
	howMany--;
	howMany--;
	if (howMany != 0) {
		while (howMany != 0) {
			insert(((rand() % (maxVal - minVal + 1)) + minVal));
			howMany--;
		}
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
} // countLeaves helper

int BST::countLeaves() {
	return countLeaves(root);
}

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
} // count helper

int BST::count(int v) {
	return count(v, root);
}

bool BST::isLeaf(Node* n) {
	if (n->left == nullptr && n->right == nullptr) {
		return true;
	}
	return false;
}
