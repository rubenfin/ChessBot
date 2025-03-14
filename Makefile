NAME	:= chessbot
CFLAGS	:= -std=c++11 -O2
# CFLAGS := -Wall -Wextra -pedantic -std=c89 -O3 -flto -march=native

CC		:= c++

SRC_DIR		:= src
SRCS		:= $(shell find $(SRC_DIR) -iname "*.cpp")

OBJ_DIR		:= build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


HEADERS := include/uci.hpp include/perft.hpp include/search.hpp include/evaluate.hpp include/generate.hpp include/move.hpp include/position.hpp include/parse.hpp include/types.hpp include/logger.hpp include/Zobrist.hpp include/OpeningsBook.hpp

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf build/

fclean:
	rm -rf build/
	rm -f $(NAME)

re:
	${MAKE} fclean
	${MAKE}
