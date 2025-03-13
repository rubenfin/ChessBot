#include "../include/perft.hpp"
#include "../include/uci.hpp"
#include "../include/OpeningBook.hpp"

#define PERFT 0

int main(void) {
    struct position pos;
    parse_position(&pos, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    struct position pos2;
    parse_position(&pos2, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // OpeningBook OpeningBook("openingbooks/openings.txt");
    uint64_t hash = computeZobristHash(pos);
    std::cout << "hash1: " << hash << std::endl;
    uint64_t hash2 = computeZobristHash(pos2);
    std::cout << "hash2: " << hash2 << std::endl;
    #if PERFT
        perft_run();
    #else
        uci_run("example engine", "csteenvo");
    #endif

    return EXIT_SUCCESS;
}
