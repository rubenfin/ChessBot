// #include "../include/Zobrist.hpp"

// int main() {
//     Zobrist zobrist;

//     // Example board: -1 means empty, 0-11 are piece types (pawns, knights, etc.)
//     int board[64] = { -1 }; // Empty board for simplicity
//     board[0] = 0;  // White rook
//     board[7] = 0;  // Another white rook
//     board[60] = 6; // White king
//     board[4] = 12; // Black king


//     uint64_t hash = zobrist.computeHash(board);
//     std::cout << "Zobrist Hash: " << hash << std::endl;

//     return 0;
// }
