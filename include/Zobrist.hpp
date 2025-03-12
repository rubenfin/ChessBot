#include <iostream>
#include <array>
#include <random>
#include <cstdint>
#include <unordered_map>

class Zobrist {
private:
    std::unordered_map<uint64_t, int> BoardHistory;
    std::array<std::array<uint64_t, 12>, 64> pieceKeys;
    std::mt19937_64 rng;

    uint64_t random64() {
        return rng();
    }

public:
    Zobrist();
    uint64_t computeHash(const int board[64]) const;
};
extern Zobrist *zobrist;

