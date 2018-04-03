#include "Node.h"

Node::Node(Tree& tree) {
	_tree = &tree;
}



void Node::AddChild(Node& node) {
	_children.push_back(&node);
	node.Set_Parent(*this);
}

Node& Node::Get_Parent() { return *_parent; }

Data_Play& Node::Get_PlayData() { return _data_play; }

Data_MinMax & Node::Get_MinMaxData() { return _data_minmax; }

std::vector<Node*>& Node::Get_Children() { return _children; }

void Node::Set_Parent(Node& node) { _parent = &node; }

void Node::Set_Tree(Tree& tree) { _tree = &tree; }
