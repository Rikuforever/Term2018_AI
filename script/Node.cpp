#include "Node.h"

Node::Node(Tree& tree) {
	_tree = &tree;
	_parent = NULL;
}


// Tree Functions
void Node::AddChild(Node& node) {
	_children.push_back(&node);
	node.Set_Parent(*this);
}

void Node::Set_Parent(Node& node) { _parent = &node; }
void Node::Set_Tree(Tree& tree) { _tree = &tree; }

Node& Node::Get_Parent() { return *_parent; }
std::vector<Node*>& Node::Get_Children() { return _children; }


// Data Functions
Data_Play& Node::Get_PlayData() { return _data_play; }
void Node::Set_PlayData(Data_Play data_play) { _data_play = data_play; }

Data_MinMax & Node::Get_MinMaxData() { return _data_minmax; }
void Node::Set_MinMaxData(Data_MinMax data_minmax) { _data_minmax = data_minmax; }
