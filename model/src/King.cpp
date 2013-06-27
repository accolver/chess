#include "King.h"
#include "Board.h"

//------------------------------------------------------------------------------------------------
King::King(PC col, int r, int c) : Piece(KING, col, r, c) {
}

//------------------------------------------------------------------------------------------------
King::~King() {
}

//------------------------------------------------------------------------------------------------
vector<Position> King::GetValidMoves(Board* board) {
	
	vector<Position> vec;
	Position* curPos = this->GetPosition();
	int row = curPos->GetRow();
	int col = curPos->GetCol();

	if ((board->GetPieceAt(row - 1, col - 1) == NULL ||
	   (board->GetPieceAt(row - 1, col - 1))->GetColor() != this->GetColor()) &&
	   !InCheck(row - 1, col - 1, board)) {
		Position pos(row - 1, col - 1);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row - 1, col) == NULL ||
	   (board->GetPieceAt(row - 1, col))->GetColor() != this->GetColor())  &&
	   !InCheck(row - 1, col , board)) {
		Position pos(row - 1, col);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row - 1, col + 1) == NULL ||
	   (board->GetPieceAt(row - 1, col + 1))->GetColor() != this->GetColor())  &&
	   !InCheck(row - 1, col + 1, board)) {
		Position pos(row - 1, col + 1);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row, col + 1) == NULL ||
	   (board->GetPieceAt(row , col + 1))->GetColor() != this->GetColor())  &&
	   !InCheck(row, col + 1, board)) {
		Position pos(row, col + 1);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row + 1, col + 1) == NULL ||
	   (board->GetPieceAt(row + 1, col + 1))->GetColor() != this->GetColor())  &&
	   !InCheck(row + 1, col + 1, board)) {
		Position pos(row + 1, col + 1);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row + 1, col) == NULL ||
	   (board->GetPieceAt(row + 1, col))->GetColor() != this->GetColor())  &&
	   !InCheck(row + 1, col , board)) {
		Position pos(row + 1, col);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row + 1, col - 1) == NULL ||
	   (board->GetPieceAt(row + 1, col - 1))->GetColor() != this->GetColor())  &&
	   !InCheck(row + 1, col - 1, board)) {
		Position pos(row + 1, col - 1);
		vec.push_back(pos);
	}

	if ((board->GetPieceAt(row, col - 1) == NULL ||
	   (board->GetPieceAt(row, col - 1))->GetColor() != this->GetColor())  &&
	   !InCheck(row, col - 1, board)) {
		Position pos(row, col - 1);
		vec.push_back(pos);
	}

	//pass vec by reference to another method in this class and check for valid moves.

	return vec;
}

//------------------------------------------------------------------------------------------------
bool King::InCheck(int r, int c, Board* b) {
	if(QueenBishopCheck(r,c,b))
		return true;
	if(QueenRookCheck(r,c,b))
		return true;
	if(KnightCheck(r,c,b))
		return true;
	if(PawnCheck(r,c,b))
		return true;
	if(KingCheck(r,c,b))
		return true;
	return false;
}


//------------------------------------------------------------------------------------------------
bool King::QueenBishopCheck(int r, int c, Board* b) {
	int rcpy = r;
	int ccpy = c;

	// Check Down and Right
	r = rcpy + 1;
	c = ccpy + 1;
	while (r < 8 && c < 8) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)		// It's my own piece
				break;
			else if (p->GetType() == BISHOP || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}

		r++;
		c++;	
	}

	// Check Down and Left
	r = rcpy + 1;
	c = ccpy - 1;
	while (r < 8 && c > -1) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)		// It's my own piece
				break;
			else if (p->GetType() == BISHOP || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}

		r++;
		c--;	
	}

	// Check Up and Left
	r = rcpy - 1;
	c = ccpy - 1;
	while (r > -1 && c > -1) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)		// It's my own piece
				break;
			else if (p->GetType() == BISHOP || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}

		r--;
		c--;	
	}

	// Check Up and Right
	r = rcpy - 1;
	c = ccpy + 1;
	while (r > -1 && c < 8) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)		// It's my own piece
				break;
			else if (p->GetType() == BISHOP || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}

		r--;
		c++;	
	}
	return false;
}

//------------------------------------------------------------------------------------------------
bool King::QueenRookCheck(int r, int c, Board* b) {

	int rcpy = r;
	int ccpy = c;

	// Checks Down for Rooks and Queens
	r = rcpy + 1;
	c = ccpy;
	while (r < 8) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)//own piece
				break;
			else if (p->GetType() == ROOK || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}
		r++;	
	}

	// Checks Up for Rooks and Queens
	r = rcpy - 1;
	c = ccpy;
	while (r > -1) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)//own piece
				break;
			else if (p->GetType() == ROOK || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}
		r--;	
	}

	// Checks Right for Rooks and Queens
	r = rcpy;
	c = ccpy + 1;
	while (c < 8) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)//own piece
				break;
			else if (p->GetType() == ROOK || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {}
			else			// Enemy piece not in check
				break;
		}
		c++;	
	}

	// Checks Left for Rooks and Queens
	r = rcpy;
	c = ccpy - 1;
	while (c > -1) {
	
		Piece* p = b->GetPieceAt(r, c);
		if (p != NULL) {	//There's a piece here
			if (p->GetColor() == this->GetColor() && p->GetType() != KING)//own piece
				break;
			else if (p->GetType() == ROOK || p->GetType() == QUEEN) {// Enemy piece in check
				return true;
			}
			else if (p->GetColor() == this->GetColor() && p->GetType() == KING) {} //own king
			else			// Enemy piece not in check
				break;
		}
		c--;	
	}
	return false;
}

//------------------------------------------------------------------------------------------------
bool King::KnightCheck(int r, int c, Board* b) {
	int rcpy = r;
	int ccpy = c;

	r = rcpy + 1;
	c = ccpy + 2;
	Piece* p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy + 1;
	c = ccpy - 2;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy - 1;
	c = ccpy + 2;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy - 1;
	c = ccpy - 2;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy + 2;
	c = ccpy + 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy + 2;
	c = ccpy - 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy - 2;
	c = ccpy + 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	r = rcpy - 2;
	c = ccpy - 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == KNIGHT)
		return true;

	return false;
}

//------------------------------------------------------------------------------------------------
bool King::PawnCheck(int r, int c, Board* b) {

	int rcpy = r;
	int ccpy = c;

	Piece* p;
	// White King against Black Pawns
	if (this->GetColor() ==	 WHITE) {
		r = rcpy - 1;
		c = ccpy + 1;
		p = b->GetPieceAt(r, c);
		if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == PAWN)
			return true;

		r = rcpy - 1;
		c = ccpy - 1;
		p = b->GetPieceAt(r, c);
		if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == PAWN)
			return true;
	}
	
	// Black King against White Pawns
	else {
		r = rcpy + 1;
		c = ccpy + 1;
		p = b->GetPieceAt(r, c);
		if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == PAWN)
			return true;

		r = rcpy + 1;
		c = ccpy - 1;
		p = b->GetPieceAt(r, c);
		if (p != NULL && p->GetColor() != this->GetColor() && p->GetType() == PAWN)
			return true;
	}

	return false;
}

//------------------------------------------------------------------------------------------------
bool King::KingCheck(int r, int c, Board* b) {
	
	int rcpy = r;
	int ccpy = c;
	PC MyKingsColor = this->GetColor();

	r = rcpy - 1;
	c = ccpy - 1;
	Piece* p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy - 1;
	c = ccpy;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy - 1;
	c = ccpy + 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy;
	c = ccpy + 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy + 1;
	c = ccpy + 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy + 1;
	c = ccpy;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy + 1;
	c = ccpy - 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	r = rcpy;
	c = ccpy - 1;
	p = b->GetPieceAt(r, c);
	if (p != NULL && p->GetType() == KING && p->GetColor() != MyKingsColor)
		return true;

	return false;
}
//------------------------------------------------------------------------------------------------
