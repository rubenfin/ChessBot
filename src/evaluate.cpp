
// #include "pst.hpp"
// #include "evaluate.hpp"
// #include "types.hpp"
// #include "logger.hpp"
#include "../include/pst.hpp"
#include "../include/evaluate.hpp"
#include "../include/types.hpp"
#include "../include/logger.hpp"
#include "../include/Zobrist.hpp"

static const int piece_value[6] = {100, 300, 300, 500, 900, 1000000};

// todo
//  - Implement for black by 64 - square
//  - Scaling the values
//  - Phase value for knowing which phase of game
//  - Make better test and debug environment

int getSquarePostitionValue(const struct position *pos, int square, int phase)
{
	int piece = pos->board[square];
	int color = COLOR(piece);
	int type = TYPE(piece);
	int mid_value = 0;
	int end_value = 0;
	if (color == BLACK)
	{
		square = square ^ 56;
	}
		switch (type)
		{
		case PAWN:
			mid_value = midgame_pawn[square];
			end_value = endgame_pawn[square];
			break;
		case KNIGHT:
			mid_value = midgame_knight[square];
			end_value = endgame_knight[square];
			break;
		case BISHOP:
			mid_value = midgame_bishop[square];
			end_value = endgame_bishop[square];
			break;
		case ROOK:
			mid_value = midgame_rook[square];
			end_value = endgame_rook[square];
			break;
		case QUEEN:
			mid_value = midgame_queen[square];
			end_value = endgame_queen[square];
			break;
		case KING:
			mid_value = midgame_king[square];
			end_value = endgame_king[square];
		break;
	}
	return ((mid_value * phase) + (end_value * (256 - phase))) / 256;;
}

int evaluate(const struct position *pos, int phase)
{
	int score[2] = {0, 0};
	int square;

	for (square = 0; square < 64; square++)
	{
		int piece = pos->board[square];

		if (piece != NO_PIECE)
		{
			score[COLOR(piece)] += piece_value[TYPE(piece)] + getSquarePostitionValue(pos, square, phase);
		}
	}
	return score[pos->side_to_move] - score[1 - pos->side_to_move];
}

int countPieces(const int board[64])
{
	int total = 0;

	for (int i = 0; i < 64; i++)
	{
		switch (board[i])
		{
		case KNIGHT:
			total += 1;
			break;
		case BISHOP:
			total += 1;
			break;
		case ROOK:
			total += 2;
			break;
		case QUEEN:
			total += 4;
			break;
		default:
			break;
		}
	}
	return total;
}

int getPhase(const int board[64]) { // aggressive bot
    int total = countPieces(board);
    double normalized = (double)total / 24.0;
    double phase = std::pow(normalized, 0.75) * 256;
    return (int)phase;
}

int get_score(const struct position *pos)
{
	int result;
	uint64_t hash = zobrist->computeHash(pos);
	int phase = getPhase(pos->board);
	result = evaluate(pos, phase);

	if (zobrist->BoardHistory[hash] >= 3)
	{
		result -= 500;
	}
	else if (zobrist->BoardHistory[hash] == 2)
	{
		result -= 100;
	}

	return result;
}

// int main() {
// 	struct position test_position_white = {
// 		.board = {
// 			  6 ,  2 ,  4 ,  8 , 10 ,  4 ,  2 ,  6 ,
//   0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//   1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,
//   7 ,  3 ,  5 ,  9 , 11 ,  5 ,  3 ,  7 ,
// 		},
// 		.side_to_move = WHITE,
// 		.castling_rights = { 0, 0 },
// 		.en_passant_square = NO_SQUARE
// 	};

// 		struct position test_position_black = {
// 		.board = {
//   6 ,  2 ,  4 ,  8 , 10 ,  4 ,  2 ,  6 ,
//   0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , -1 ,
//  -1 , -1 , -1 , -1 , -1 , -1 , -1 , 1 ,
//   1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  1 ,  -1 ,
//   7 ,  3 ,  5 ,  9 , 11 ,  5 ,  3 ,  7 ,
// 		},
// 		.side_to_move = BLACK,
// 		.castling_rights = { 0, 0 },
// 		.en_passant_square = NO_SQUARE
// 	};

// 	int score_white = get_score(&test_position_white);
// 	std::cout << "-------------------" << std::endl;
// 	int score_black = get_score(&test_position_black);

// 	printf("Evaluation score: %d\n", score_white);
// 	printf("Evaluation score: %d\n", score_black);

// 	return 0;
// }
