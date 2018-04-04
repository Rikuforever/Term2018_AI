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
	Data_Play();
	Data_Play(Grid grid, Player player, int column, bool isEnd);
	// Data Function
	Grid& Get_Grid();
	Player& Get_Player();
	int& Get_Column();
	bool& Get_IsEnd();
};