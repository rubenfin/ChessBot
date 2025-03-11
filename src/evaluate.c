
#include "pst.h"
#include "evaluate.h"
#include "types.h"
// #include "../include/pst.h"
// #include "../include/evaluate.h"
// #include "../include/types.h"

static const int piece_value[6] = { 100, 300, 300, 500, 900, 1000000 };

//todo
// - Implement for black by 64 - square
// - Scaling the values
// - Phase value for knowing which phase of game

int getSquarePostitionValue(const struct position *pos, int square)
{
	int piece = pos->board[square];
	int color = COLOR(piece);
	int type = TYPE(piece);
	int value = 0;
	switch (type)
	{
		case PAWN:
			value = pawn_table[square];
			break;
		case KNIGHT:
			value = knight_table[square];
			break;
		case BISHOP:
			value = bishop_table[square];
			break;
		case ROOK:
			value = rook_table[square];
			break;
		case QUEEN:
			value = queen_table[square];
			break;
		case KING:
			value = king_table[square];
			break;
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

	return score[pos->side_to_move] - score[1 - pos->side_to_move];
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
// 			NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE, NO_PIECE,
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
