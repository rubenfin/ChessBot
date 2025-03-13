#include "search.hpp"
#include "evaluate.hpp"
#include "generate.hpp"
#include "Zobrist.hpp"
#include "logger.hpp"


#include <limits.h>

struct search_result alpha_beta(int alpha, int beta, int depth, const struct position *pos, int phase) {
	struct search_result result;
	result.score = -1000000;
	uint64_t hash = zobrist->computeHash(pos);

    zobrist->BoardHistory[hash]++;
	if (depth == 0) {
		result.score = get_score(pos, phase);
	} else {
		struct move moves[MAX_MOVES];
		size_t count = generate_legal_moves(pos, moves);

		for (size_t index = 0; index < count; ++index) {

			struct position copy = *pos;
			do_move(&copy, moves[index]);

			int score = -alpha_beta(-beta, -alpha, depth -1, &copy, phase).score;


			if (score > alpha) {
				alpha = score;
			}
			if (score > result.score) {
				result.move = moves[index];
				result.score = score;
			}

			if (alpha >= beta)
				break ;
		}
	}
	return result;
}


int countPieces(const int board[64])
{
	int total = 0;

	for (int i = 0; i < 64; i++)
	{
		if (board[i] == KNIGHT)
			total += 1;
		else if (board[i] == BISHOP)
			total += 1;
		else if (board[i] == ROOK)
			total += 2;
		else if (board[i] == QUEEN)
			total += 4;
	}
	return(total);
}

int getPhase(const struct search_info *info)
{
	int total = countPieces(info->pos->board);
	return ((total * 256) / 24);
}

struct move search(struct search_info *info) {
	info->phase = getPhase(info);
	return alpha_beta(-100000, 100000, 4, info->pos, info->phase).move;
}
