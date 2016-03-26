#ifndef BST_H_
#define BST_H_

#include <string>

#include "BSTInterface.h"
#include "Node.h"

using namespace std;

class BST : public BSTInterface {
public:
	BST();
	~BST();

	virtual Node* getRootNode();
	virtual bool add(int data);
	virtual bool remove(int data);
	virtual void clear();

	/* DEBUGGING */
	void print();

private:
	bool contains(int data);
	Node* find(int data);
	Node* find(Node* n, int data);

	bool add(Node*& n, int data);
	bool remove(Node* n, int data, Node*& parent);
	bool clear(Node* n, Node*& parent);
	
	Node* getInorderPredecessor(Node* n, Node*& ip_parent);

	/* DEBUGING */
	int getBlanks(int level);
	int getSpaces(int level);
	int getLevels(Node* n);
	string makeBox(string s);
	string getNodeData(int index);
	bool getNodeData(Node* n, string& data, int row, int col, int desired_index);


	Node* root;
	
};

#endif