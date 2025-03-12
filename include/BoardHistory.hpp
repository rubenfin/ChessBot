#pragma once
#include <array>
#include <iostream>
#include <iomanip>


class BoardHistory {
    private:
     std::array<int [64], 3> history;
     int index = 0;
     int count = 0;
 public:
     BoardHistory();
     ~BoardHistory();
     void addBoard(const int board[64]);
    void printAllBoards() const;
    void printTest() const;
     // void addBoard(Board* board);
     // Board* getBoard(int index);
     // int getLength();
     // void clear();
};
extern BoardHistory *boardHistory;
