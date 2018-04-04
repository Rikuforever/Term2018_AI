#include "Data_Play.h"

// Constructor
Data_Play::Data_Play() {}
Data_Play::Data_Play(Grid grid, Player player, int column, bool isEnd) {
	_grid = grid;
	_player = player;
	_column = column;
}
// Data Function
Grid& Data_Play::Get_Grid() { return _grid; }
Player& Data_Play::Get_Player() { return _player; }
int& Data_Play::Get_Column() { return _column; }
bool& Data_Play::Get_IsEnd() { return _isEnd; }