NAME := chessbot  # Default executable name
CFLAGS := -Wall -Wextra -pedantic -std=c89
# CFLAGS := -Wall -Wextra -pedantic -std=c89 -O3 -flto -march=native

HEADERS := include/uci.h include/perft.h include/search.h include/evaluate.h include/generate.h include/move.h include/position.h include/parse.h include/types.h include/pst.h include/logger.h

# Default target
OUTPUT := $(NAME)

build/%.o: src/%.c $(HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ -c -Iinclude

$(OUTPUT): build/uci.o build/perft.o build/search.o build/evaluate.o build/generate.o build/move.o build/position.o build/parse.o build/main.o build/logger.o
	$(CC) $(CFLAGS) $^ -o $@

# Target to build with a custom name
new:
	$(eval OUTPUT := $(name))  # Use the name argument
	$(MAKE)

clean:
	rm -rf build/

fclean:
	rm -rf build/
	rm -f $(OUTPUT)

re:
	${MAKE} fclean
	${MAKE}
