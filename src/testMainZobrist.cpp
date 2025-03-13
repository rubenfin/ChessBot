#include "../include/Zobrist.hpp"
#include "../include/position.hpp"
#include "../include/types.hpp"

int main() {
    Zobrist zobrist;
        struct position *pos = new struct position;
        for (int i = 0; i < 64; ++i) {
            std::cout << i << std::endl;
            pos->board[i] = NO_PIECE;
        }

        for (int i = 8; i < 16; ++i) {
            pos->board[i] = PAWN;
        }
        for (int i = 48; i < 56; ++i) {
            pos->board[i] = PAWN;
        }

        pos->side_to_move = WHITE;
        pos->castling_rights[0] = 1; // White can castle
        pos->castling_rights[1] = 1; // Black can castle
        pos->en_passant_square = NO_SQUARE;


    uint64_t hash = zobrist.computeHash(pos);
        // uint64_t hash = zobrist.computeHash(pos);
        zobrist.BoardHistory[hash]++;
    zobrist.BoardHistory[hash]++;
    zobrist.BoardHistory[hash]++;

    if (zobrist.BoardHistory[hash] >= 3) {
        std::cout << "✅ Threefold repetition detected!" << std::endl;
    } else {
        std::cerr << "❌ Threefold repetition NOT detected!" << std::endl;
    }


    std::cout << "Zobrist Hash: " << hash << std::endl;

    return 0;
}
