#include "search.hpp"
#include "evaluate.hpp"
#include "generate.hpp"
#include "Zobrist.hpp"
#include "logger.hpp"


#include <limits.h>

struct search_result alpha_beta(int alpha, int beta, int depth, const struct position *pos) {
	struct search_result result;
	uint64_t hash = zobrist->computeHash(pos);

    zobrist->BoardHistory[hash]++;

	// TODO: add some check for end of game
	if (depth == 0) {
		/* we have reached our search depth, so evaluate the position.       */
		result.score = get_score(pos);
	} else {
		struct move moves[MAX_MOVES];
		size_t count = generate_legal_moves(pos, moves);

		for (size_t index = 0; index < count; ++index) {

			struct position copy = *pos;
			do_move(&copy, moves[index]);

			int score = -alpha_beta(-beta, -alpha, depth -1, &copy).score;


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

struct move search(const struct search_info *info) {
	return alpha_beta(-100000, 100000, 4, info->pos).move;
}
