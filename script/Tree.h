#pragma once
#include "Node.h"

class Node;

class Tree {
private:
	Node* _root;
public:
	// Constructor
	Tree();
	Tree(Node& root);
	// Tree Function
	Node& Get_Root();
	void Set_Root(Node& root);
	// Debug Function
	void PrintTree();
};