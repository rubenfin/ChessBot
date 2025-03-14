#include "../include/search.hpp"
#include "../include/evaluate.hpp"
#include "../include/generate.hpp"
#include "../include/Zobrist.hpp"
#include "../include/logger.hpp"


#include <limits.h>

struct search_result alpha_beta(int alpha, int beta, int depth, const struct position *pos) {
	struct search_result result;
	result.score = -1000000;
	uint64_t hash = zobrist->computeHash(pos);
    zobrist->BoardHistory[hash]++;
	if (depth == 0) {
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




struct move search(struct search_info *info) {
	return alpha_beta(-100000, 100000, 4, info->pos).move;
}
