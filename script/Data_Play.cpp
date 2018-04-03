#include "Data_Play.h"

// Constructor
Data_Play::Data_Play(Grid grid, Player player, int column, bool isEnd) {
	_grid = grid;
	_player = player;
	_column = column;
}

Grid& Data_Play::Get_Grid() { return _grid; }

Grid Data_Play::Copy_Grid() { return _grid; }
