#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

#include "BST.h"

using namespace std;

BST::BST() {
	root = NULL;
}
BST::~BST() {
	BST::clear();
}

Node* BST::getRootNode() {
	return root;
}

bool BST::add(int data) {
	return BST::add(root, data);
}

bool BST::remove(int data) {
	// cout << "DATA TO REMOVE: " << data;
	bool removed = BST::remove(root, data, root);
	// cout << "; NEW ROOT ADDR " << root << endl;
	return removed;

}

void BST::clear() {
	BST::clear(root, root);
}

/****** PRIVATE *******/

bool BST::contains(int data) {
	return (BST::find(root, data) != NULL);
}

Node* BST::find(int data) {
	return BST::find(root, data);
}

Node* BST::find(Node* n, int data) {
	if (n == NULL) {
		return NULL;
	} else if (data == n->data) {
		return n;
	} else if (data < n->data) {
		return BST::find(n->left, data);
	} else if (data > n->data) {
		return BST::find(n->right, data);
	}
}

bool BST::add(Node*& n, int data) {
	if (n == NULL) {
		n = new Node(data);
		return true;
	} else if (data < n->data) {
		// balancing (?)
		// if (n->left != NULL && data > n->left->data) {
		// 	n->left = new Node(data, n->left);
		// 	return true;
		// } else {
			return BST::add(n->left, data);
		// }
	} else if (data > n->data) {
		// balancing (?)
		// if (n->right != NULL && data < n->right->data) {
		// 	n->right = new Node(data, n->right);
		// 	return true;
		// } else {
			return BST::add(n->right, data);
		// }
	} else {
		return false;
	}
}

bool BST::remove(Node* n, int data, Node*& parent) {
	if (!n) {
		return false;
	} else if (data == n->data) {
		bool is_left_child = n->data < parent->data;
		bool childless = !n->left && !n->right;
		bool has_only_right_child = !n->left && n->right;

		if (childless) {
			if (is_left_child) parent->left = NULL;
			else parent->right = NULL;

			// clear parent
			if (n == parent) parent = NULL;

			delete n;

		} else if (has_only_right_child) {
			if (is_left_child) parent->left = n->right;
			else parent->right = n->right;

			// reset parent
			if (n == parent) parent = n->right;

			delete n;

		} else {
			Node* ip_parent;
			Node* ip = BST::getInorderPredecessor(n, ip_parent);

			bool ip_has_only_left_child = ip->left && !ip->right;


			// cout << "IP: " << ip->data << endl;
			// if (ip_parent) cout << "IP PARENT: " << ip_parent->data << endl;

			int ip_data = ip->data;

			if (ip_has_only_left_child) {
				Node* temp_parent = (!ip_parent) ? n : ip_parent;
				if (ip->data < temp_parent->data) temp_parent->left = ip->left;
				else temp_parent->right = ip->left;

				delete ip;
			} else BST::remove(n, ip_data, n);

			n->data = ip_data;
		}

		// // } else if (has_only_left_child) {

		// 	// return BST::remove(n->left, data, n);

		// 	// if (parent != n) {
		// 	// 	if (is_left_child) parent->left = n->left;
		// 	// 	else parent->right = n->left;
		// 	// } else {
		// 	// 	parent = n->left;
		// 	// }

		// 	// delete n;
		// } else if (has_only_right_child) {

		// 	if (parent != n) {
		// 		if (is_left_child) parent->left = n->right;
		// 		else parent->right = n->right;
		// 	} else {
		// 		parent = n->right;
		// 	}

		// 	delete n;
		// // } else if (has_two_children) {
		// } else {

		// 	Node* ip_parent;
		// 	Node* inorder_predecessor = BST::getInorderPredecessor(n, ip_parent);

		// 	cout << "IP: " << inorder_predecessor->data << endl;

		// 	bool ip_childless = !inorder_predecessor->left && !inorder_predecessor->right;

		// 	if (ip_childless) {
		// 		if (ip_parent) ip_parent->right = NULL;
		// 		else n->left = NULL; // (because n is its parent)
		// 		n->data = inorder_predecessor->data;

		// 		delete inorder_predecessor;
		// 	} else {
		// 		int ip_data = inorder_predecessor->data;
		// 		BST::remove(n, ip_data, n);

		// 		n->data = ip_data;
		// 	}
		// }

		return true;
	} else if (data < n->data) {
		return BST::remove(n->left, data, n);
	} else if (data > n->data) {
		return BST::remove(n->right, data, n);
	}
}

bool BST::clear(Node* n, Node*& parent) {
	if (!n) {
		return false;
	} else if (!n->left && !n->right) {
		if (n != parent) {
			if (n->data < parent->data) parent->left = NULL;
			else parent->right = NULL;
		} else {
			parent = NULL;
		}

		delete n;
		return true;
	} else {
		bool left = BST::clear(n->left, n);
		bool right = BST::clear(n->right, n);
		bool current = BST::clear(n, parent);

		return left || right || current;
	}
}

Node* BST::getInorderPredecessor(Node* n, Node*& ip_parent) {
	Node* left_subtree = n->left;
	Node* inorder_predecessor = left_subtree;

	ip_parent = NULL;

	while (inorder_predecessor && inorder_predecessor->right) {
		ip_parent = inorder_predecessor;
		inorder_predecessor = inorder_predecessor->right;
	}

	return inorder_predecessor;
}


/******* DEBUG ********/

void BST::print() {
	int levels = BST::getLevels(root);
	int BOX_LEN = 3;
	int OVER_BOX = 0;

	for (int row=0; row<levels; row++) {
		// get spaces per side;
		// int spaces_per_side = 0;
		// for (int j=row; j<levels; j++) spaces_per_side += (2*(levels - (j+2)) + 1) + BOX_LEN;
		// spaces_per_side -= 2;

		int spaces_per_side = BST::getSpaces(levels - row);
		int dashes_per_side = spaces_per_side - BST::getBlanks( levels - row);

		// int dashes_per_side = 2*(levels - (row + 2)) + 1;
		int cols_in_row = pow(2, row);
		// cout << "L: " << row+1 << "; SPACES PER SIDE: " << spaces_per_side << "; DASHES PER SIDE: " << dashes_per_side << endl;
		for (int col=0; col<cols_in_row; col++) {
			cout << string(spaces_per_side - (dashes_per_side + OVER_BOX), ' ') << string(dashes_per_side + OVER_BOX, '-');
			int index = (row + col) + (cols_in_row - row) - 1;

			string data = BST::getNodeData(index);
			cout << BST::makeBox(data);
			cout << string(dashes_per_side + OVER_BOX, '-') << string(spaces_per_side - (dashes_per_side + OVER_BOX), ' ');

			if (spaces_per_side == 0 && (col % 2) == 0) {
				cout << string(1 + BOX_LEN + 1, ' ');
			} else {
				cout << " ";
			}

		}
		// cout << "S" << spaces_per_side << " D" << dashes_per_side << " B" << BST::getBlanks(levels - row) << endl;
		cout << endl;
	}
	cout << endl << endl;
	// cout << "LEVELS: " << BST::getLevels(root) << endl;
	// cout << root->data << "->" << root->right->data << "->" << root->right->right->data << endl;
	// cout << root->left->left->data << "<-" << root->left->data << "<-" << root->data << "->" << root->right->data << endl;
}

int BST::getBlanks(int level) {
	if (level == 1) {
		return 0;
	} else if (level == 2) {
		return 2;
	} else if (level == 3) {
		return 6;
	} else {
		return 2 * BST::getBlanks(level - 1);
	}
}

int BST::getSpaces(int level) {
	if (level == 1) {
		return 0;
	} else if (level == 2) {
		return 4;
	} else {
		return (BST::getBlanks(level) * 2) - 2;
	}
}

int BST::getLevels(Node* n) {
	if (n == NULL) {
		return 0;
	} else if (n->left == NULL && n->right == NULL) {
		return 1;
	} else if (n->left != NULL && n->right == NULL) {
		return BST::getLevels(n->left) + 1;
	} else if (n->left == NULL && n->right != NULL) {
		return BST::getLevels(n->right) + 1;
	} else {
		int left_count = BST::getLevels(n->left);
		int right_count = BST::getLevels(n->right);
		int count = (left_count > right_count) ? left_count : right_count;
		return count + 1;
	}
}

string BST::makeBox(string s) {
	if (s.length() == 1) {
		return "*" + s + "*";
	} else if (s.length() == 2) {
		return "*" + s;
	} else {
		return s;
	}
}


string BST::getNodeData(int index) {
	// cout << endl  << "GETTING INDEX: " << index << "!!!"  << endl;
	string data;
	if (BST::getNodeData(root, data, 0, 0, index)) {
		return data;
	}
}

bool BST::getNodeData(Node* n, string& data, int row, int col, int desired_index) {
	int cols_in_row = pow(2, row);
	int current_index = (row + col) + (cols_in_row - row) - 1;

	string none = " x ";

	bool debug = !true;

	if (debug) cout << endl << "ROW: " << row << "  COL: " << col << "  CUR: " << current_index << "  DES: " << desired_index;

	if (current_index == desired_index) {
		// positive base case
		if (debug) cout << " HERE!" << endl;

		if (n) {
			stringstream ss;
			ss << n->data;
			data = ss.str(); 
		} else {
			data = none;
		}
		return true;
	} else if (current_index > (desired_index)) {
		// negative base case
		if (debug) cout << " TOO BIG";
		data = none;
		// do backtracking prevention here?
		return false;
	} else if (!n) {
		if (debug) cout << " ITS NULL";
		data = none;
		return false;
	}

	//recursion
	if (BST::getNodeData(n->left, data, row+1, (col*2), desired_index)) {
		if (debug) cout << endl << "LEFT" << endl;
		return true;
	} else if (BST::getNodeData(n->right, data, row+1, ((col*2)+1), desired_index)) {
		if (debug) cout << endl << "RIGHT" << endl;
		return true;
	}

	// any thing else is false
	return false;
}