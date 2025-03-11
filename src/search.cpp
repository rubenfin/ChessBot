#include "search.hpp"
#include "evaluate.hpp"
#include "generate.hpp"
#include "position.hpp"

// this function is always called as maximizer.
// just alternating as black or white - both are trying to maximize their own points
// their own points are = (-1) * points from other color perspective
// 	(e.g. black 10 white 7 = 3 from black perspective = -3 from white perspective)
// if we are black
// 	alpha represents the highest value (from black persective) that they can guarantee for their own color at this level of recursion
// 		black wants to maximize alpha
// 	beta represents the lowest value (from black perspective) that the other color (white) can guarantee at this level of recursion
// 		white wants to minimize beta
// 	if alpha >= beta it means that we found a value that is bigger than the minimal value the other color further up in the recursion
// 	can already guarantee. Since we are maximizing the score and the other color is minimizing the score, we know that the other color
// 	further up in the recursion will ignore our return value anyways

struct search_result alpha_beta(int alpha, int beta, int depth, const struct position *pos) {
	struct search_result result;
	result.score = -100000;

	// TODO: add some check for end of game
	if (depth == 0) {
		result.score = evaluate(pos);
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
