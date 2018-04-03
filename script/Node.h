#pragma once

#include <vector>
#include "Tree.h"
#include "Data_Play.h"
#include "Data_MinMax.h"

class Node {
private:
	int _ID; // ID
	// Tree Variables 
	Tree* _tree;
	Node* _parent;
	std::vector<Node*> _children;
	// Data
	Data_Play _data_play;
	Data_MinMax _data_minmax;
public:
	Node(Tree& tree);
	// Tree Functions
	void AddChild(Node& node);
	// Call By Reference
	Node& Get_Parent();
	Data_Play& Get_PlayData();
	Data_MinMax& Get_MinMaxData();
	std::vector<Node*>& Get_Children();
	void Set_Parent(Node& node);
	void Set_Tree(Tree& tree);
};