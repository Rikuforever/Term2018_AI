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
			if (cnt1.count() != 0 && shifts[ss] == ROW_SHIFT) {
				int ignoreIdx[]{ 9,10,17,18,25,26,33,34,41,42 };
				for (int i = 0; i < 10; i++) {
					if (cnt1[ignoreIdx[i]] == true) {
						cnt1.set(ignoreIdx[i], false);
					}
				}
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
            ret += 10*(p?-1:1)*cnt4.count();   
        }
    }
    return ret;
}

