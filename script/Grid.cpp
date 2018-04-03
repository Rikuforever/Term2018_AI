#include "Grid.h"

#define XLength 7
#define YLength 6

// Constructor (default : X=7, Y=6)
Grid::Grid() : Grid(XLength,YLength) {}
Grid::Grid(int xLen, int yLen) {
	for (int x = 0; x < xLen; x++) {
		std::vector<int> obj;
		for (int y = 0; y < yLen; y++) {
			obj.push_back(0);
		}
		_item.push_back(obj);
	}

	_xLength = xLen;
	_yLength = yLen;
};

// Operator
std::vector<int>& Grid::operator[] (int x) { 
	return _item[x];
}
