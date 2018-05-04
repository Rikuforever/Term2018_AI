/**
 *  Board.cc
 *  Author: Oskar Werkelin Ahlin
 */
#include "Board.h"
#include <cstdio>
#include <cstdlib>
#include <intrin.h>
#include <bitset>

#define COLS 7LL
#define ROWS 6LL

#define ROW_SHIFT 1
#define COL_SHIFT 8
#define DIAG_SHIFT1 7
#define DIAG_SHIFT2 9

#define VAL_NULL 0
#define VAL_ME 1
#define VAL_OPPONENT 2

#pragma region Custom

void printBits(size_t const size, void const * const ptr) {
	unsigned char *b = (unsigned char*)ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}

void excludeDummy(std::bitset<64>* bs, int offset) {
	static int dummy[] = { 7,15,23,31,39,47 };

	if (bs->count() != 0) {
		for (int i = 0; i < 6; i++) {
			if ((*bs)[dummy[i] + offset] == true) {
				bs->set(dummy[i] + offset, false);
			}	
		}
	}
}

#pragma endregion 

Board::Board() {
    bricks[0] = 0;
    bricks[1] = 0;
}

Board::Board(Board& b, int c, int p) {
    bricks[0] = b.bricks[0];
    bricks[1] = b.bricks[1];
    makeMove(c,p);
}

std::vector<int> Board::validMoves() {
    std::vector<int> result;
	unsigned long long all = bricks[0] | bricks[1];
    for (int i = 0; i < COLS; ++i) if (!(all & (1<<i))) result.push_back(i);
    return result;
}

bool Board::validMove(int c) {
    if (c < 0 || c >= COLS) return false;
    return !((bricks[0] | bricks[1]) & (1<<c));
}

void Board::makeMove(int c, int p) {
	unsigned long long bit = 1LL<<(c+(COLS+1)*(ROWS-1));
    unsigned long long all = bricks[0] | bricks[1];
    while (all & bit) {
        bit >>= (COLS+1);
    }   
    bricks[p] |= bit;
}

void Board::plot() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            bool printed = false;
            for (int p = 0; p < 2; ++p) {
                if (bricks[p] & (1LL<<((COLS+1)*i+j))) {
                    printed = true;
                    printf("%c ",p?'X':'O');
                }   
            }
            if (!printed) printf(". ");
        }
        printf("\n");
    }
}

int Board::result() {
    unsigned long long temp;

    for (int p = 0; p < 2; ++p) {
        temp = bricks[p] & (bricks[p]<<1);
        if (temp & (temp<<2)) return p;
        temp = bricks[p] & (bricks[p]<<(COLS+1));
        if (temp & (temp<<(2*(COLS+1)))) return p;
        temp = bricks[p] & (bricks[p]<<(COLS+1+1));
        if (temp & (temp<<(2*(COLS+1+1)))) return p;
        temp = bricks[p] & (bricks[p]<<(COLS+1-1));
        if (temp & (temp<<(2*(COLS+1-1)))) return p;
    }
    if (validMoves().size() == 0) return 2;
    return -1;
}

int Board::score() {
    int result_check = result();
    if (result_check != -1) {
        if (result_check == 2) return 0;
        if (result_check == 0) return 1<<15;
        else return -(1<<15);
    }

    int ret = 0;
    unsigned long long all = bricks[0] | bricks[1];
	unsigned long long tmp1,tmp2,tmp3;

    int shifts[3] = {ROW_SHIFT,DIAG_SHIFT1,DIAG_SHIFT2}; // ignore vertical
	
	for (int p = 0; p < 2; ++p) {
        for (int ss = 0; ss < 3; ++ss) {
            
            // O--O
            tmp1 = bricks[p]&(bricks[p] << 3*shifts[ss]);
            tmp2 = ~bricks[!p];
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= tmp1;
			std::bitset<64> cnt1(tmp2);
			switch (shifts[ss]) {
			case ROW_SHIFT:
				excludeDummy(&cnt1, 1);
				excludeDummy(&cnt1, 2);
				break;
			case DIAG_SHIFT1:	// 왼쪽 아래
				excludeDummy(&cnt1, -1);
				excludeDummy(&cnt1, -2);
				break;
			case DIAG_SHIFT2:	// 오른쪽 아래
				excludeDummy(&cnt1, 1);
				excludeDummy(&cnt1, 2);
				break;
			default:
				break;
			}
			ret += 3 * (p ? -1 : 1)*cnt1.count();

            // OO
            tmp3 = bricks[p] & (bricks[p]<<(1*shifts[ss]));
			std::bitset<64> cnt2(tmp3);
            ret += 2*(p?-1:1)*cnt2.count();

            // OOO
            tmp3 = bricks[p] & (bricks[p]<<(1*shifts[ss])) & (bricks[p]<<(2*shifts[ss]));
			std::bitset<64> cnt3(tmp3);
            ret += 7*(p?-1:1)*cnt3.count();

            // O-OO / OO-O
            tmp1 = bricks[p]&(bricks[p] << 3*shifts[ss]);
            tmp2 = ~bricks[!p];
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= (tmp2<<shifts[ss]);
            tmp2 &= tmp1;
            tmp2 &= (bricks[p]<<(2*shifts[ss])|bricks[p]<<(shifts[ss]));
			std::bitset<64> cnt4(tmp2);
			switch (shifts[ss]) {
			case ROW_SHIFT:
				excludeDummy(&cnt4, 1);
				excludeDummy(&cnt4, 2);
				break;
			case DIAG_SHIFT1:	// 왼쪽 아래
				excludeDummy(&cnt4, -1);
				excludeDummy(&cnt4, -2);
				break;
			case DIAG_SHIFT2:	// 오른쪽 아래
				excludeDummy(&cnt4, 1);
				excludeDummy(&cnt4, 2);
				break;
			default:
				break;
			}
            ret += 10*(p?-1:1)*cnt4.count();   
        }
    }
    return ret;
}

std::vector<std::vector<int>> Board::getvector(int playerID) {
	std::vector<std::vector<int>> result;
	std::bitset<64> bit0(bricks[0]);
	std::bitset<64> bit1(bricks[1]);

	for (int x = 0; x < COLS; x++) {
		std::vector<int> col;
		for (int y = 0; y < ROWS; y++) {
			int idx = x + (COLS + 1) * (ROWS - 1 - y);
			if (bit0[idx] == true)
				col.push_back((playerID == 0) ? VAL_ME : VAL_OPPONENT);
			else if (bit1[idx] == true)
				col.push_back((playerID == 1) ? VAL_ME : VAL_OPPONENT);
			else
				col.push_back(VAL_NULL);
		}
		result.push_back(col);
	}
	return result;
}

bool Board::isempty() {
	return !(bricks[0] + bricks[1]);
}

