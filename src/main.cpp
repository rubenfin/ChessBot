#include "../include/perft.hpp"
#include "../include/uci.hpp"
#include "../include/OpeningBook.hpp"

#define PERFT 0

int main(void) {
    #if PERFT
        perft_run();
    #else
        uci_run("example engine", "csteenvo");
    #endif

    return EXIT_SUCCESS;
}
