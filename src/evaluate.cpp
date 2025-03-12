
// #include "pst.hpp"
// #include "evaluate.hpp"
// #include "types.hpp"
// #include "logger.hpp"
#include "../include/pst.hpp"
#include "../include/evaluate.hpp"
#include "../include/types.hpp"
#include "../include/logger.hpp"
#include "../include/Zobrist.hpp"

static const int piece_value[6] = { 100, 300, 300, 500, 900, 1000000 };

//todo
// - Implement for black by 64 - square
// - Scaling the values
// - Phase value for knowing which phase of game
// - Make better test and debug environment

int getSquarePostitionValue(const struct position *pos, int square)
{
	int piece = pos->board[square];
	int color = COLOR(piece);
	int sign = 1;
	// printf("COLOR: %d\n", color);
	int type = TYPE(piece);
	int value = 0;
	if (color == BLACK)
	{
		square = 63 - square;
		sign = -1;
	}
	switch (type)
	{
		case PAWN:
			// printf("PAWN square: %d\n", square);
			value = pawn_table[square] * sign;
			break;
		case KNIGHT:
			value = knight_table[square] * sign;
			break;
		case BISHOP:
			value = bishop_table[square] * sign;
			break;
		case ROOK:
			value = rook_table[square] * sign;
			break;
		case QUEEN:
			value = queen_table[square] * sign;
			break;
		// case KING:
		// 	value = king_table[square] * sign;
		// 	break;
	}

	return value;
}

int evaluate(const struct position *pos) {
	int score[2] = { 0, 0 };
	int square;

	for (square = 0; square < 64; square++) {
		int piece = pos->board[square];

		if (piece != NO_PIECE) {
			score[COLOR(piece)] += piece_value[TYPE(piece)] + getSquarePostitionValue(pos, square);
			// score[COLOR(piece)] += piece_value[TYPE(piece)];
		}
}
	// printf("%d | %d \n", score[WHITE], score[BLACK]);
	// return score[WHITE] - score[BLACK];
	return score[pos->side_to_move] - score[1 - pos->side_to_move];
}

int get_score(const struct position *pos) {
	int result;

	result = evaluate(pos);
	 uint64_t hash = zobrist->computeHash(pos->board);

    if (zobrist->BoardHistory[hash] >= 2)
    {
		std::cout << "small strike" << std::endl;
		result += 1000000;
	}
    // if (zobrist->BoardHistory[hash] >= 1)
    // {
	// 	log_write("3 strikes\n");
	// 	result -= 1000000;
	// }
	log_write("%d", result);
	return result;
}

// int main() {
// 	struct position test_position_white = {
// 		.board = {
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			PAWN, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE
// 		},
// 		.side_to_move = WHITE,
// 		.castling_rights = { 0, 0 },
// 		.en_passant_square = NO_SQUARE
// 	};
// 		struct position test_position_black = {
// 		.board = {
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			1, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE
// 		},
// 		.side_to_move = BLACK,
// 		.castling_rights = { 0, 0 },
// 		.en_passant_square = NO_SQUARE
// 	};

// 	int score_white = evaluate(&test_position_white);
// 	int score_black = evaluate(&test_position_black);

// 	printf("Evaluation score: %d\n", score_white);
// 	printf("Evaluation score: %d\n", score_black);

// 	return 0;
// }
