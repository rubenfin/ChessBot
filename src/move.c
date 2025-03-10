#include "move.h"
#include "generate.h"
#include "parse.h"
#include "types.h"

struct move make_move(int from_square, int to_square, int promotion_type) {
	struct move move;

	move.from_square = from_square;
	move.to_square = to_square;
	move.promotion_type = promotion_type;

	return move;
}

int parse_move(struct move *move, const char *string) {
	/* parse the from square.                                                */
	move->from_square = parse_square(string);

	if (move->from_square == NO_SQUARE) {
		return FAILURE;
	}

	/* parse the to square.                                                  */
	move->to_square = parse_square(string + 2);

	if (move->to_square == NO_SQUARE) {
		return FAILURE;
	}

	/* parse the promotion type.                                             */
	move->promotion_type = NO_TYPE;

	if (string[4]) {
		move->promotion_type = parse_type(string[4]);

		if (move->promotion_type == NO_TYPE) {
			return FAILURE;
		}
	}

	return SUCCESS;
}

void do_move(struct position *pos, struct move move) {
	int from_file = FILE(move.from_square);
	int from_rank = RANK(move.from_square);
	int to_file = FILE(move.to_square);
	int to_rank = RANK(move.to_square);
	int piece = pos->board[move.from_square];
	int color = pos->side_to_move;
	int a1 = SQUARE(FILE_A, RELATIVE(RANK_1, color));
	int h1 = SQUARE(FILE_H, RELATIVE(RANK_1, color));
	int a8 = SQUARE(FILE_A, RELATIVE(RANK_8, color));
	int h8 = SQUARE(FILE_H, RELATIVE(RANK_8, color));
	int en_passant_square = pos->en_passant_square;

	/* move the piece, promoting it if necessary.                            */
	pos->board[move.from_square] = NO_PIECE;

	if (move.promotion_type != NO_TYPE) {
		pos->board[move.to_square] = PIECE(color, move.promotion_type);
	} else {
		pos->board[move.to_square] = piece;
	}

	/* reset the en passant square.                                          */
	pos->en_passant_square = NO_SQUARE;

	/* update castling rights.                                               */
	if (move.from_square == h1) {
		pos->castling_rights[color] &= ~KING_SIDE;
	} else if (move.from_square == a1) {
		pos->castling_rights[color] &= ~QUEEN_SIDE;
	}

	if (move.to_square == h8) {
		pos->castling_rights[1 - color] &= ~KING_SIDE;
	} else if (move.to_square == a8) {
		pos->castling_rights[1 - color] &= ~QUEEN_SIDE;
	}

	/* update side to move.                                                  */
	pos->side_to_move = 1 - color;

	switch (TYPE(piece)) {
	case PAWN:
		/* set the en passant square for double pawn pushes.                 */
		if (RELATIVE(to_rank, color) - RELATIVE(from_rank, color) == 2) {
			pos->en_passant_square = SQUARE(to_file, RELATIVE(RANK_3, color));
		}

		/* also remove the captured pawn for en passant captures.            */
		if (move.to_square == en_passant_square) {
			pos->board[SQUARE(to_file, from_rank)] = NO_PIECE;
		}

		break;

	case KING:
		/* update castling rights for king moves.                            */
		pos->castling_rights[color] = 0;

		/* also move the rook for castling moves.                            */
		if (from_file == FILE_E && to_file == FILE_G) {
			pos->board[SQUARE(FILE_H, to_rank)] = NO_PIECE;
			pos->board[SQUARE(FILE_F, to_rank)] = PIECE(color, ROOK);
		} else if (from_file == FILE_E && to_file == FILE_C) {
			pos->board[SQUARE(FILE_A, to_rank)] = NO_PIECE;
			pos->board[SQUARE(FILE_D, to_rank)] = PIECE(color, ROOK);
		}

		break;
	}
}

int is_legal(const struct position *pos, struct move move) {
	struct position copy = *pos;
	struct move moves[MAX_MOVES];
	int piece = pos->board[move.from_square];
	size_t count;
	size_t index;

	/* make the move on a copy of the position.                              */
	do_move(&copy, move);

	/* for castling moves, pretend there is another king on all squares      */
	/* between the from square and the to square. this makes it illegal to   */
	/* castle through a square that is controlled by the opponent.           */
	if (TYPE(piece) == KING) {
		int from_file = FILE(move.from_square);
		int to_file = FILE(move.to_square);
		int rank = RELATIVE(RANK_1, pos->side_to_move);

		if (from_file == FILE_E && to_file == FILE_G) {
			copy.board[SQUARE(FILE_E, rank)] = piece;
			copy.board[SQUARE(FILE_F, rank)] = piece;
		} else if (from_file == FILE_E && to_file == FILE_C) {
			copy.board[SQUARE(FILE_E, rank)] = piece;
			copy.board[SQUARE(FILE_D, rank)] = piece;
		}
	}

	/* generate all pseudo-legal moves for the opponent.                     */
	count = generate_pseudo_legal_moves(&copy, moves);

	/* return false if any of those moves could capture the king.            */
	for (index = 0; index < count; index++) {
		int piece = copy.board[moves[index].to_square];

		if (piece == PIECE(pos->side_to_move, KING)) {
			return 0;
		}
	}

	/* return true if no moves could capture the king.                       */
	return 1;
}
