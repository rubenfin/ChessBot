#include "../include/BoardHistory.hpp"

int main() {
    // Create a new BoardHistory object
    BoardHistory boardHistory;

    // Create a sample board
    int board1[64] = {
        6, 2, 4, 8, 10, 4, 2, 6,
        0, 0, 0, 0, 0, 0, 0, 0,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 1111, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        1, 1, 1, 1, 1, 1, 1, 1,
        7, 3, 5, 9, 11, 5, 3, 7
    };
    int board2[64] = {
        6, 2, 4, 8, 10, 4, 2, 6,
        0, 0, 0, 0, 0, 0, 0, 0,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 2222, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        1, 1, 1, 1, 1, 1, 1, 1,
        7, 3, 5, 9, 11, 5, 3, 7
    };
    int board3[64] = {
        6, 2, 4, 8, 10, 4, 2, 6,
        0, 0, 0, 0, 0, 0, 0, 0,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 3333, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        1, 1, 1, 1, 1, 1, 1, 1,
        7, 3, 5, 9, 11, 5, 3, 7
    };
    int board4[64] = {
        6, 2, 4, 8, 10, 4, 2, 6,
        0, 0, 0, 0, 0, 0, 0, 0,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 21312312, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1,
        1, 1, 1, 1, 1, 1, 1, 1,
        7, 3, 5, 9, 11, 5, 3, 7
    };
    // Add boards to the history
    boardHistory.addBoard(board1);
    boardHistory.addBoard(board2);
    boardHistory.addBoard(board3);
    boardHistory.addBoard(board4);

    // Print all boards
    boardHistory.printAllBoards();

    // Test printTest function
    boardHistory.printTest();

    return 0;
}