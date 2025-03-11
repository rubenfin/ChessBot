#ifndef PST_H
#define PST_H

#include "types.hpp"

int pawn_table[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
     10,  15,  15, -10, -10,  15,  15,  10,
      5,  10,  10,  20,  20,  10,  10,   5,
      0,   0,   0,  15,  15,   0,   0,   0,
      2,   5,  5,  10,  10,  5,   5,   2,
      5,   2, -5,   0,   0, -5,   2,   5,
      5,  10, 10, -30, -30, 10,  10,   5,
      0,   0,   0,   0,   0,   0,   0,   0
};

int knight_table[64] = {
    -50, -40, -30, -30, -30, -30, -40, -50,
    -40, -20,   0,   5,   5,   0, -20, -40,
    -30,   5,  10,  15,  15,  10,   5, -30,
    -30,   0,  15,  20,  20,  15,   0, -30,
    -30,   5,  15,  20,  20,  15,   5, -30,
    -30,   0,  10,  15,  15,  10,   0, -30,
    -40, -20,   0,   0,   0,   0, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50
};

int bishop_table[64] = {
    -20, -10, -10, -10, -10, -10, -10, -20,
    -10,   5,   0,   0,   0,   0,   5, -10,
    -10,  10,  10,  10,  10,  10,  10, -10,
    -10,   0,  10,  15,  15,  10,   0, -10,
    -10,   5,  10,  15,  15,  10,   5, -10,
    -10,   0,  10,  10,  10,  10,   0, -10,
    -10,   0,   0,   0,   0,   0,   0, -10,
    -20, -10, -10, -10, -10, -10, -10, -20
};

int rook_table[64] = {
      0,   0,   5,  10,  10,   5,   0,   0,
     -5,   0,   0,   0,   0,   0,   0,  -5,
     -5,   0,   0,   0,   0,   0,   0,  -5,
     -5,   0,   0,   0,   0,   0,   0,  -5,
     -5,   0,   0,   0,   0,   0,   0,  -5,
     -5,   0,   0,   0,   0,   0,   0,  -5,
      5,  10,  10,  10,  10,  10,  10,   5,
      0,   0,   0,   5,   5,   0,   0,   0
};

int queen_table[64] = {
    -20, -10, -10,  -5,  -5, -10, -10, -20,
    -10,   0,   5,   0,   0,   0,   0, -10,
    -10,   5,   5,   5,   5,   5,   0, -10,
      0,   0,   5,   5,   5,   5,   0,  -5,
     -5,   0,   5,   5,   5,   5,   0,  -5,
    -10,   0,   5,   5,   5,   5,   0, -10,
    -10,   0,   0,   0,   0,   0,   0, -10,
    -20, -10, -10,  -5,  -5, -10, -10, -20
};

// int king_table[64] = {
//     -50, -40, -30, -20, -20, -30, -40, -50,
//     -40, -20, -10,   0,   0, -10, -20, -40,
//     -30, -10,  20,  30,  30,  20, -10, -30,
//     -30, -10,  30,  40,  40,  30, -10, -30,
//     -30, -10,  30,  40,  40,  30, -10, -30,
//     -30, -10,  20,  30,  30,  20, -10, -30,
//     -40, -20, -10,   0,   0, -10, -20, -40,
//     -50, -40, -30, -20, -20, -30, -40, -50
// };

#endif
