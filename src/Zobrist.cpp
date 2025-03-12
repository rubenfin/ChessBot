#include "Zobrist.hpp"

Zobrist::Zobrist() {
    std::random_device rd;
    rng.seed(rd());

    for (int square = 0; square < 64; square++) {
        for (int piece = 0; piece < 12; piece++) {
            pieceKeys[square][piece] = random64();
        }
    }
}


uint64_t Zobrist::computeHash(const int board[64]) const
{
    uint64_t hash = 0;

    for (int square = 0; square < 64; square++)
    {
        int piece = board[square];
        if (piece >= 0 && piece < 12)
            hash ^= pieceKeys[square][piece];
    }
    return (hash);
}

Zobrist *zobrist = new Zobrist();

