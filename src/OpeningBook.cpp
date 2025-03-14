#include "../include/OpeningBook.hpp"
#include <random>

uint64_t computeZobristHash(const struct position &pos) {
    static bool initialized = false;
    static uint64_t pieceKeys[64][12];
    static uint64_t castlingKeys[16];
    static uint64_t enPassantKeys[8];
    static uint64_t sideKey;
    static std::mt19937_64 rng;

    // Initialize keys if not already done
    if (!initialized) {
        std::random_device rd;
        rng.seed(12345);
        // Lambda for generating random 64-bit numbers
        auto random64 = []() -> uint64_t {
            return rng();
        };

        // Initialize piece keys
        for (int square = 0; square < 64; square++) {
            for (int piece = 0; piece < 12; piece++) {
                pieceKeys[square][piece] = random64();
            }
        }

        // Initialize castling keys
        for (int i = 0; i < 16; i++) {
            castlingKeys[i] = random64();
        }

        // Initialize en passant keys
        for (int i = 0; i < 8; i++) {
            enPassantKeys[i] = random64();
        }

        // Initialize side key
        sideKey = random64();

        initialized = true;
    }

    // Compute hash
    uint64_t hash = 0;

    // Hash pieces
    for (int square = 0; square < 64; square++) {
        int piece = pos.board[square];
        if (piece >= 0 && piece < 12) {
            hash ^= pieceKeys[square][piece];
        }
    }

    // Hash side to move
    if (pos.side_to_move == BLACK) {
        hash ^= sideKey;
    }

    // Hash castling rights
    int castlingIndex = (pos.castling_rights[WHITE] << 2) | pos.castling_rights[BLACK];
    hash ^= castlingKeys[castlingIndex];

    // Hash en passant
    if (pos.en_passant_square != NO_SQUARE) {
        int file = pos.en_passant_square % 8;
        hash ^= enPassantKeys[file];
    }

    return hash;
}

OpeningBook::OpeningBook(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << path << std::endl;
        return ;
    }

    // create starting position
    struct position pos;
    parse_position(&pos, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    uint64_t hash = computeZobristHash(pos);
    _book[hash] = FIRST_MOVE;


    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> moves;
        while (line.find(' ') != std::string::npos) {
            size_t space = line.find(' ');
            moves.push_back(line.substr(0, space));
            line = line.substr(space + 1);
        }
        if (line.size() > 0)
            moves.push_back(line);

        struct position pos_copy = pos;
        for (size_t i = 0; i < moves.size(); i++) {
            struct move move;

			parse_move(&move, moves[i].c_str());
			do_move(&pos_copy, move);

            uint64_t hash = computeZobristHash(pos_copy);
            if (_book.find(hash) == _book.end()) {
                if (i != moves.size() - 1) {
                    _book[hash] = moves[i + 1];
                }
            }
        }
    }
    file.close();

    // std::string line;
    // while (std::getline(file, line)) {
    //     std::shared_ptr<BookNode> curr = _root;
    //     std::vector<std::string> moves;
    //     while (line.find(' ') != std::string::npos) {
    //         size_t space = line.find(' ');
    //         moves.push_back(line.substr(0, space));
    //         line = line.substr(space + 1);
    //     }
    //     if (line.size() > 0)
    //         moves.push_back(line);

    //     for (std::string &move : moves) {
    //         // std::cout << "|" << move << "| ";
    //         if (curr->_followUpMoves.find(move) != curr->_followUpMoves.end()) {
    //             // std::cout << "Move already exists: " << move <<std::endl;
    //             curr = curr->_followUpMoves[move];
    //         }
    //         else {
    //             // std::cout << "Adding move: " << move << std::endl;
    //             curr = curr->addFollowUpMove(move);
    //         }
    //     }
    //     // std::cout << std::endl;
    // }
}

OpeningBook::~OpeningBook() {
    // std::cout << "Opening Book destructed" << std::endl;
    // std::cout << _book.size() << std::endl;
}


// std::string OpeningBook::getFirstMove() {
//     if (!_root->_followUpMoves.empty())
//     {
//         _lastMove = _root->_followUpMoves.begin()->second;
//         return _root->_followUpMoves.begin()->first;
//     }

//     // _active = false;
//     // _root = nullptr;
//     // _lastMove = nullptr;
//     return "";
// }

//Check if the opponent move is our book, and if we have a response to the opponents move
// check if lastMove has entry with oppResponse. if so, check whether we have a response to oppResponse, if so set lastMove to our Response

// std::string OpeningBook::getNextMove(const std::string &oppResponse) {
//     if (oppResponse.empty())
//     {
//         return getFirstMove();
//     }

//     std::cout << "oppResponse: " << oppResponse << std::endl;
//     const auto& it = _lastMove->_followUpMoves.find(oppResponse);
//     if  (it == _lastMove->_followUpMoves.end() || it->second->_followUpMoves.empty())
//     {
//         std::cout << "No response to oppResponse" << std::endl;
//         _active = false;
//         _root = nullptr;
//         _lastMove = nullptr;
//         return "";
//     }
//     std::cout << "FOUND" << std::endl;
//     std::string move = it->second->_followUpMoves.begin()->first;
//     _lastMove = it->second->_followUpMoves.begin()->second;
//     return move;
// }


std::string OpeningBook::getNextMove(const struct position& pos) {
    uint64_t hash = computeZobristHash(pos);
    if (_book.find(hash) == _book.end())
    {
        return "";
    }
    return _book[hash];
}

