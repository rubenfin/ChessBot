#ifndef OPENING_BOOK_HPP
#define OPENING_BOOK_HPP

#include "BookNode.hpp"
#include <string>
#include <fstream>
#include <unordered_map>
#include <cstdint>
#include "position.hpp"
#include "move.hpp"
#include "types.hpp"
#include "parse.hpp"

class OpeningBook {
    private:
        std::unordered_map<uint64_t, std::string> _book;
    
    public:
        OpeningBook(const std::string& path);
        ~OpeningBook();

        std::string getNextMove(const struct position& pos);
};


uint64_t computeZobristHash(const struct position &pos);
/* 
When constructing the opening book, we will read in a file that contains the moves in the opening book.
We will then construct a tree of BookNodes, where each node contains a move and a map of follow up moves.
Make a root Node and set _lastmove equal to root node.

for everyline start at root node.
check if there is a move left if not go to the next line.
get the current move, check if it exists in the current nodes unordered_map. if it does, go to that node.
if it does not, make a new node and add it to the unordered map, then go to that node.
*/

#endif // OPENING_BOOK_HPP
