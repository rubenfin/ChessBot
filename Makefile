NAME	:= chessbot
CFLAGS	:= -Wall -Wextra -pedantic -std=c++11
# CFLAGS := -Wall -Wextra -pedantic -std=c89 -O3 -flto -march=native

CC		:= c++

HEADERS := include/uci.hpp include/perft.hpp include/search.hpp include/evaluate.hpp include/generate.hpp include/move.hpp include/position.hpp include/parse.hpp include/types.hpp include/logger.hpp

build/%.o: src/%.cpp $(HEADERS) Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ -c -Iinclude

$(NAME): build/uci.o build/perft.o build/search.o build/evaluate.o build/generate.o build/move.o build/position.o build/parse.o build/main.o build/logger.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf build/

fclean:
	rm -rf build/
	rm -f $(NAME)

re:
	${MAKE} fclean
	${MAKE}
