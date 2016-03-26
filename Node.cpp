#include "Node.h"

using namespace std;

Node::Node(const int data, Node* left, Node* right) 
: data(data), left(left), right(right) {}
Node::~Node() {
}

int Node::getData() {
	return data;
}

Node* Node::getLeftChild() {
	return left;
}

Node* Node::getRightChild() {
	return right;
}