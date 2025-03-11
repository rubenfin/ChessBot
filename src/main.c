#include "perft.h"
#include "uci.h"
#include "logger.h"

#include <stdlib.h>

#define PERFT 0

int main(void) {
	log_init("log.txt");
	log_write("Hello, world!\n");
#if PERFT
	perft_run();
#else
	uci_run("example engine", "csteenvo");
#endif

	return EXIT_SUCCESS;
}
