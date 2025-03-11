#include "BoardHistory.hpp"

BoardHistory::BoardHistory() : index(0), count(0) {

}
BoardHistory::~BoardHistory() {
    std::cout << "destructed" << std::endl;
}

void BoardHistory::addBoard(const int board[64]) {
    std::cout << "werkt1" << std::endl;
    std::copy(board, board + 64, history[index]);
    std::cout << "werkt2" << std::endl;

    index = (index + 1) % 3;
    std::cout << "werkt3" << std::endl;
    if (count < 3) {
        count++;
    }
    std::cout << "werkt4" << std::endl;

}

void BoardHistory::printTest() const {
std::cout << "hallo het werkt" << std::endl;
}
// void BoardHistory::printAllBoards() const {
//     for (int i = 0; i < count; i++) {
//         for (int j = 0; j < 63; j++) {
//             std::cout << history[i][j] << " ";
//             if ((j + 1) % 8 == 0) {
//                 std::cout << std::endl;
//             }
//         }
//         std::cout << std::endl;
//     }
// }

BoardHistory *boardHistory = nullptr;
