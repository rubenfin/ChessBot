#include "perft.hpp"
#include "uci.hpp"
#include "logger.hpp"
#include "BoardHistory.cpp"

#include <stdlib.h>

#define PERFT 0

int main(void) {
	BoardHistory boardHistory;
	log_init("log.txt");
	log_write("Hello, world!\n");
#if PERFT
	perft_run();
#else
	uci_run("example engine", "csteenvo");
#endif

	return EXIT_SUCCESS;
}
