#include "../include/perft.hpp"
#include "../include/uci.hpp"
#include "../include/logger.hpp"
#include "../include/BoardHistory.hpp"
#include "../include/Zobrist.hpp"

#include <stdlib.h>

#define PERFT 0

int main(void) {
	Zobrist zobrist;
	log_init("log.txt");
#if PERFT
	perft_run();
#else
	uci_run("example engine", "csteenvo");
#endif

	return EXIT_SUCCESS;
}
