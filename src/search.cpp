#include "../include/search.hpp"
#include "../include/evaluate.hpp"
#include "../include/generate.hpp"
#include "../include/Zobrist.hpp"
#include "../include/logger.hpp"


#include <cstddef>
#include <limits.h>

std::unordered_map<uint64_t, std::pair<size_t, struct move>> transitionTable;

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

		const auto& it = transitionTable.find(hash);
		if (it != transitionTable.end()) {
			moves[it->second.first] = moves[0];
			moves[0] = it->second.second;
			transitionTable.erase(it);
		}

		for (size_t index = 0;index < count; ++index) {

			struct position copy = *pos;
			do_move(&copy, moves[index]);

			int score = -alpha_beta(-beta, -alpha, depth -1, &copy).score;

			if (score > alpha) {
				alpha = score;
			}
			if (score > result.score) {
				result.move = moves[index];
				result.score = score;
				transitionTable[hash]= {index, moves[index]};
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
