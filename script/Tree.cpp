#include "Tree.h"
#include "Node.h"

Tree::Tree() {
	Node rootNode(*this);
	Data_Play& data_play
}
Tree::Tree(Node& root) {
	root.Set_Tree(*this);
	_root = &root;
}
