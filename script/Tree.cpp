#include "Tree.h"

#include <queue>

// Constructor
Tree::Tree() {
}
Tree::Tree(Node& root) {
	root.Set_Tree(*this);
	_root = &root;
}
// Tree Function
Node& Tree::Get_Root() { return *_root; }
void Tree::Set_Root(Node& root) { _root = &root; }
// Debug Function
void Tree::PrintTree() {
	std::queue<Node*> Q;
	Q.push(_root);

	while (!Q.empty()) {
		Node* N = Q.front();
		printf("%d\n",N->Get_PlayData().Get_Player());

		std::vector<Node*> L = N->Get_Children();
		for (int i = 0; i < L.size(); i++) { Q.push(L[i]); }

		Q.pop();
	}
}