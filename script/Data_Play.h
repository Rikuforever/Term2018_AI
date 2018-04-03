#pragma once

#include "Grid.h"

enum Player {NONE, FIRST, SECOND};

class Data_Play {
private:
	Grid _grid;
	Player _player;
	int _column;
	bool _isEnd;
public:
	// Constructor
	Data_Play(Grid grid, Player player, int column, bool isEnd);
	// Call By Reference
	Grid& Get_Grid();
	// Call By Value
	Grid Copy_Grid();
};