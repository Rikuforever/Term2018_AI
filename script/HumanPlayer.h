/**
 * HumanPlayer.hh
 * Author: Oskar Werkelin Ahlin
 **/

#ifndef HUMANPLAYER_HH
#define HUMANPLAYER_HH

#include "Player.h"
#include "Board.h"

#include <cstdio>
#include <iostream>

/** 
 * Simple class that makes moves by reading from stdin. Also
 * checks that the given moves are valid. 
 */
class HumanPlayer: public Player {
    public:
        /** 
         * Get a move. Read from stdin.
         *
         * @param Board current board
         * @return Desired move.
         **/
        int getMove(Board& board) {
            int move;
			while (true) {
				printf("Player    | Input column : ");
				scanf("%d", &move);
				while (getchar() != '\n') {}	// Clear buffer
				if (board.validMove(move - 1)) break;
				printf("Player    | Invalid move.\n");
			}

            return move - 1;
        }
};

#endif // HUMANPLAYER_HH
