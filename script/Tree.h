#pragma once
#include "Node.h"

class Tree {
private:
	Node* _root;
public:
	Tree();
	Tree(Node& root);
	Node& Get_Root();
};