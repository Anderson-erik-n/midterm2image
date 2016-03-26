#include <iostream>
#include <string>

#include "BST.h"
#include "BST.cpp"

#include "Node.cpp"

using namespace std;

int main() {
	BST* tree = new BST();

	tree->add(8);
	tree->add(4);
	tree->add(12);
	tree->add(2);
	tree->add(6);
	tree->add(10);
	tree->add(14);
	tree->add(1);
	tree->add(3);
	tree->add(5);
	tree->add(7);
	tree->add(9);
	tree->add(11);
	tree->add(13);
	tree->add(15);
	
	tree->print();

	int SIZE = 16;
	int arr[16] = {8,7,6,5};

	for (int i=0; i<4; i++) {
		cout << "REMOVING " << arr[i] << ": " << tree->remove(arr[i]) << endl;
		tree->print();
	}



	return 0;
}