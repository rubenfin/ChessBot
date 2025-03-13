#include <iostream>
#include <array>
#include <random>
#include <cstdint>
#include <unordered_map>
#include  "types.hpp"
#include "position.hpp"

class Zobrist {
private:
    std::array<std::array<uint64_t, 12>, 64> pieceKeys;
    std::array<uint64_t, 16> castlingKeys;
    std::array<uint64_t, 8> enPassantKeys;
    uint64_t sideKey;
    std::mt19937_64 rng;

    uint64_t random64() {
        return rng();
    }

public:
    std::unordered_map<uint64_t, int> BoardHistory;
    Zobrist();
    uint64_t computeHash(const struct position *pos) const;
};
extern Zobrist *zobrist;

