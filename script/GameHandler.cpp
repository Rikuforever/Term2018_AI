/**
 * GameHandler.cc
 * Author: Oskar Werkelin Ahlin
 */

#include "GameHandler.h"

#include "Player.h"
#include "HumanPlayer.h"
#include "AlphaBetaPlayer.h"

void GameHandler::play() {
    Player* p[2];

	// 1. Choose First
	char inputChar = NULL;
	do {
		printf("Game      | Computer First? (y/n) : ");

		switch (inputChar = getchar()) {
			case 'y':
			case 'Y':
				printf("Game      | Computer First!\n\n");
				p[0] = new AlphaBetaPlayer();
				p[0]->playerid = 0;
				p[1] = new HumanPlayer();
				p[1]->playerid = 1;
				break;
			case 'n':
			case 'N':
				printf("Game      | Computer Second!\n\n");
				p[0] = new HumanPlayer();
				p[0]->playerid = 0;
				p[1] = new AlphaBetaPlayer();
				p[1]->playerid = 1;
				break;
			default:
				printf("WRONG INPUT\n\n");
				inputChar = NULL;
				break;
		}

		char bufferChar = NULL;	// Flush buffer
		while ((bufferChar = getchar()) == '\n' && bufferChar == EOF) {}
	} while (inputChar == NULL);

	// 2. Initialize
    int turn = 0,move;

	// 3. Play
	printf("Game      | Game Start!\n");
	board.plot();
    while (board.result() == -1) {
        move = p[turn%2]->getMove(board);	// decide move
		board.makeMove(move, turn%2);		// execute move
        board.plot();						// output result
        ++turn;
    }
    int res;
    if ((res=board.result()) == 2) printf("Draw!\n");
    else printf("Player %d won!\n",res);
}
