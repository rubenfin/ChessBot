NAME	:= chessbot
# TODO: remove -g flag
CFLAGS	:= -Wall -Wextra -pedantic -std=c++11 -g
# CFLAGS := -Wall -Wextra -pedantic -std=c89 -O3 -flto -march=native

CC		:= c++

SRC		:= $(wildcard src/*.cpp)
OBJ		:= $(patsubst src/%.cpp, build/%.o, $(SRC))

build/%.o: src/%.cpp Makefile
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@ -c -Iinclude

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf build/

fclean:
	rm -rf build/
	rm -f $(NAME)

re:
	${MAKE} fclean
	${MAKE}
