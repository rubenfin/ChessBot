#include <iostream>
#include "Bitboard.hpp"

int main() {
    ChessBoard board = {
        .white_pawns   = 0x00FF000000000000ULL,
        .white_knights = 0x4200000000000000ULL,
        .white_bishops = 0x2400000000000000ULL,
        .white_rooks   = 0x8100000000000000ULL,
        .white_queens  = 0x0800000000000000ULL,
        .white_king    = 0x1000000000000000ULL,

        .black_pawns   = 0x000000000000FF00ULL,
        .black_knights = 0x0000000000000042ULL,
        .black_bishops = 0x0000000000000024ULL,
        .black_rooks   = 0x0000000000000081ULL,
        .black_queens  = 0x0000000000000008ULL,
        .black_king    = 0x0000000000000010ULL,
};
    board.white_pawns |= (1ULL << 28);

    std::cout << "White pawns: " << board.white_pawns << std::endl;

}