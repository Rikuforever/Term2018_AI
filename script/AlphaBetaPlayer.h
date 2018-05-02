/**
 *  AlphaBetaPlayer.hh
 *  Author: Oskar Werkelin Ahlin
 *
 *  An AI player using alpha-beta pruning for finding good moves. 
 *  Instantiate the class with a board, then use getMove to retrieve
 *  moves.
 **/
#ifndef ALPHABETAPLAYER_HH
#define ALPHABETAPLAYER_HH

#include "Player.h"
#include "Board.h"
#include "Rule.h"

#include <vector>
#include <cstdio>
#include <algorithm>

#define MAXDEPTH 8

class AlphaBetaPlayer: public Player {
    public:
        /**
         * The main function for alpha-beta pruning.
         *
         * @param cur The current board.
         * @param d Current number of max depth steps left.
         * @param alpha Alpha in 'alpha-beta pruning'.
         * @param beta Beta in 'alpha-beta pruning'.
         * @param turn The current turn.
         * @return Best evaluation for sub tree.
         */
        int alphaBeta(Board cur, int d, int alpha, int beta, int turn) {
            if (!d || cur.result() != -1) { 
                int ret = cur.score()*(playerid?-1:1);
                return ret; 
            }
            std::vector<int> possibleMoves = cur.validMoves();
            if ((playerid&&turn)||(!playerid&&(!turn))) { /* maximizing player */
                for (int i = 0; i < (int)possibleMoves.size(); ++i) {
                    Board newBoard(cur, possibleMoves[i], turn);
                    alpha = std::max(alpha, alphaBeta(newBoard, d-1, alpha, beta, turn^1));
                    if (beta <= alpha) break;
                }
                return alpha;
            } else { /* minimizing player */
                for (int i = 0; i < (int)possibleMoves.size(); ++i) {
                    Board newBoard(cur, possibleMoves[i], turn);
                    beta = std::min(beta, alphaBeta(newBoard, d-1, alpha, beta, turn^1));
                    if (beta <= alpha) break;
                }
                return beta;
            }
            return 0;
        }

        /** 
         * getMove uses alpha-beta pruning for calculating evaluation
         * for possible moves, and makes the move which most benefits 
         * the agent. Also prints the evaluation of the best possible move.
         *
         * See Player.hh
         *
         * @param Board The current game board.
         * @return The decided move.
         **/
        int getMove(Board& curboard) {
			bool doRule;

			// 1. Select method
			char inputChar = EOF;
			do {
				printf("Computer  | (1) Heuristic\n");
				printf("Computer  | (2) Rule\n");
				printf("Computer  | Choose method : ");

				switch (inputChar = getchar()) {
				case '1':
				case NULL:
					printf("Computer  | Computing by heuristic...\n");
					doRule = false;
					break;
				case '2':
					printf("Computer  | Computing by rule...\n");
					doRule = true;
					break;
				default:
					printf("Computer  | Invalid input.\n");
					inputChar = EOF;
					break;
				}

				while (getchar() != '\n') {}	// Clear buffer
			} while (inputChar == EOF);

			// 2. Compute 
			std::vector<int> moves = curboard.validMoves();
			std::vector<int> candMoves;

			if (doRule) {		// Rule
				std::vector<std::vector<int>> vecboard = curboard.getvector(playerid);
				candMoves.push_back(Rule(vecboard));
			}
			else {				// Heuristic
				int bestScore = playerid ? -(1 << 25) : -(1 << 25);
				for (int i = (int)moves.size() - 1; i + 1; --i) {
					Board newboard = Board(curboard, moves[i], playerid);
					int curScore = alphaBeta(newboard, MAXDEPTH + 2 * (7 - moves.size()), -(1 << 15), 1 << 15, playerid ^ 1);
					if (curScore > bestScore) {
						candMoves.clear();
						bestScore = curScore;
						candMoves.push_back(moves[i]);
					}
					else if (curScore == bestScore) {
						candMoves.push_back(moves[i]);
					}
					printf("Computer  | Heuristic | MOVE %d has SCORE %d\n", moves[i] + 1, curScore);
				}
				printf("Computer  | Heuristic | Result : DEPTH %d (player %d) EVAL %d\n", MAXDEPTH + 2 * (7 - (int)moves.size()), playerid, bestScore);
			}

			return candMoves[(rand()%((int)candMoves.size()))];
        }
};

#endif // ALPHABETAPLAYER_HH
