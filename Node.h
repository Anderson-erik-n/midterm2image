#ifndef NODE_H_
#define NODE_H_

#include "NodeInterface.h"

using namespace std;

class Node : public NodeInterface {
	friend class BST;
public:
	Node(const int data, Node* left = NULL, Node* right = NULL);
	~Node();

	virtual int getData();
	virtual Node* getLeftChild();
	virtual Node* getRightChild();

private:
	int data;
	Node* left;
	Node* right;
};

#endif