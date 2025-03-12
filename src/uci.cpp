#include "uci.hpp"
#include "search.hpp"
#include "move.hpp"
#include "types.hpp"
#include "OpeningBook.hpp"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostream>

static char *get_line(FILE *stream) {
	size_t capacity = 1024;
	size_t size = 0;
	char *string = (char *) malloc(capacity);

	while (fgets(string + size, capacity - size, stream)) {
		size += strlen(string + size);

		if (string[size - 1] == '\n') {
			return string;
		}

		capacity *= 2;
		string = (char *) realloc(string, capacity);
	}

	free(string);

	return NULL;
}

static char *get_token(char *string, char *store) {
	string += strlen(string);
	*string = *store;

	while (isspace(*string)) {
		string++;
	}

	if (*string) {
		char *token = string;

		while (*string && !isspace(*string)) {
			string++;
		}

		*store = *string;
		*string = '\0';

		return token;
	}

	return NULL;
}

static void uci_position(struct position *pos, char *token, char *store) {
	token = get_token(token, store);

	if (token && !strcmp(token, "startpos")) {
		parse_position(pos, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		token = get_token(token, store);
	} else if (token && !strcmp(token, "fen")) {
		char *fen = get_token(token, store);
		int index;

		token = fen;

		for (index = 0; token && index < 5; index++) {
			token = get_token(token, store);
		}

		if (token) {
			parse_position(pos, fen);
			token = get_token(token, store);
		}
	}

	if (token && !strcmp(token, "moves")) {
		while ((token = get_token(token, store))) {
			struct move move;

			if (parse_move(&move, token) == SUCCESS) {
				do_move(pos, move);
			}
		}
	}
}

static void uci_go(const struct position *pos, char *token, char *store, OpeningBook& OpeningBook) {
	struct search_info info;
	struct move move_struct;

	info.pos = pos;
	info.time[WHITE] = 0;
	info.time[BLACK] = 0;
	info.increment[WHITE] = 0;
	info.increment[BLACK] = 0;

	while ((token = get_token(token, store))) {
		if (!strcmp(token, "searchmoves")) {
			break;
		} else if (!strcmp(token, "ponder")) {
			continue;
		} else if (!strcmp(token, "infinite")) {
			continue;
		} else if (!strcmp(token, "wtime")) {
			token = get_token(token, store);
			info.time[WHITE] = token ? atoi(token) : 0;
		} else if (!strcmp(token, "btime")) {
			token = get_token(token, store);
			info.time[BLACK] = token ? atoi(token) : 0;
		} else if (!strcmp(token, "winc")) {
			token = get_token(token, store);
			info.increment[WHITE] = token ? atoi(token) : 0;
		} else if (!strcmp(token, "binc")) {
			token = get_token(token, store);
			info.increment[BLACK] = token ? atoi(token) : 0;
		} else {
			token = get_token(token, store);
		}

		if (!token) {
			break;
		}
	}

	std::string move;
	
	move = OpeningBook.getNextMove(*pos);
	std::cout << "Selected move from book: \"" << move << "\"" << std::endl;
		// if (!move.empty())
			// std::cout << "Selected move from book: \"" << move << "\"" << std::endl;
	
	if (move.empty()) {
		// std::cout << "Using engine search (no book move available)" << std::endl;
		move_struct = search(&info);
	
		move +="abcdefgh"[FILE(move_struct.from_square)];
		move += '1' + RANK(move_struct.from_square);
		move += "abcdefgh"[FILE(move_struct.to_square)];
		move += '1' + RANK(move_struct.to_square);
	
		if (move_struct.promotion_type != NO_TYPE) {
			move += "pnbrqk"[move_struct.promotion_type];
		}
	} 
	std::cout << "bestmove " << move << std::endl;
}

// std::string grabLatestMove(char *readline) {
// 	std::string line(readline);
// 	if (line.find("moves") == std::string::npos)
// 	{
// 		return "";
// 	}

// 	std::string latestMove;

// 	size_t lastSpace = line.find_last_of(' ');
// 	if (lastSpace != std::string::npos) {
// 		latestMove = line.substr(lastSpace + 1);
		
// 		size_t start = latestMove.find_first_not_of(" \t\n\r");
// 		size_t end = latestMove.find_last_not_of(" \t\n\r");
		
// 		if (start != std::string::npos && end != std::string::npos) {
// 			latestMove = latestMove.substr(start, end - start + 1);
// 		} else if (start != std::string::npos) {
// 			latestMove = latestMove.substr(start);
// 		} else if (end != std::string::npos) {
// 			latestMove = latestMove.substr(0, end + 1);
// 		} else {
// 			latestMove = "";
// 		}
// 	}
// 	return latestMove;
// }

void uci_run(const char *name, const char *author) {
	char *line;
	int quit = 0;
	struct position pos;
	OpeningBook OpeningBook("openingbooks/opening.txt");

	while (!quit && (line = get_line(stdin))) {
		char *token = line;
		char store = *token;
		// static std::string lastMove;
		*token = '\0';

		while ((token = get_token(token, &store))) {
			if (!strcmp(token, "quit")) {
				quit = 1;
			} else if (!strcmp(token, "uci")) {
				printf("id name %s\n", name);
				printf("id author %s\n", author);
				printf("uciok\n");
			} else if (!strcmp(token, "isready")) {
				printf("readyok\n");
			} else if (!strcmp(token, "position")) {
				uci_position(&pos, token, &store);
				// lastMove = grabLatestMove(line);
			} else if (!strcmp(token, "go")) {
				uci_go(&pos, token, &store, OpeningBook);
			} else if (!strcmp(token, "setoption")) {
				break;
			} else if (!strcmp(token, "register")) {
				break;
			} else {
				continue;
			}

			break;
		}

		free(line);
		fflush(stdout);
	}
}
