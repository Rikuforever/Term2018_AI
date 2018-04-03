#pragma once
#include <vector>

class Grid {
private:
	int _xLength;
	int _yLength;
	std::vector<std::vector<int>> _item;
public:
	// Constructor
	Grid();
	Grid(int xLen, int yLen);
	// Operator
	std::vector<int>& operator[] (int x);
};