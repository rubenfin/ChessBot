// #include "Zobrist.hpp"
#include "../include/Zobrist.hpp"

Zobrist::Zobrist() {
    std::random_device rd;
    rng.seed(rd());

    for (int square = 0; square < 64; square++) {
        for (int piece = 0; piece < 12; piece++) {
            pieceKeys[square][piece] = random64();
        }
    }

        for (int i = 0; i < 16; i++) {
        castlingKeys[i] = random64();
    }

    for (int i = 0; i < 8; i++) {
        enPassantKeys[i] = random64();
    }

        sideKey = random64();
    }

uint64_t Zobrist::computeHash(const struct position *pos) const {
    uint64_t hash = 0;

    for (int square = 0; square < 64; square++)
    {
        int piece = pos->board[square];
        if (piece >= 0 && piece < 12) {
            hash ^= pieceKeys[square][piece];
        }
    }

    if (pos->side_to_move == BLACK)
    {
        hash ^= sideKey;
    }

    int castlingIndex = (pos->castling_rights[WHITE] << 2) | pos->castling_rights[BLACK];
    hash ^= castlingKeys[castlingIndex];

    if (pos->en_passant_square != NO_SQUARE)
    {
        int file = pos->en_passant_square % 8;
        hash ^= enPassantKeys[file];
    }

    return hash;
}


Zobrist *zobrist = new Zobrist();

