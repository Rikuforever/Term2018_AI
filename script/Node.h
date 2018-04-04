#pragma once

#include <vector>
#include "Tree.h"
#include "Data_Play.h"
#include "Data_MinMax.h"

class Tree;

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
	void Set_Parent(Node& node);
	void Set_Tree(Tree& tree);
	Node& Get_Parent();
	std::vector<Node*>& Get_Children();
	// Data Function
	Data_Play& Get_PlayData();
	void Set_PlayData(Data_Play data_play);
	void Set_MinMaxData(Data_MinMax data_minmax);
	Data_MinMax& Get_MinMaxData();

};