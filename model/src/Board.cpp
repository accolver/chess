#include "Board.h"
//#include "UnitTest.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

#include <set>
#include <vector>
#include "Position.h"
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------
Board::Board() {
}

//------------------------------------------------------------------------------------------------
Board::~Board() {
	ClearBoard();
}


//------------------------------------------------------------------------------------------------
vector<Position> Board::GetValidMovesForPiece(int row, int col, PC curPlayersColor) {
	
	vector<Position> vec(0);

	Piece* p = grid[row][col];
	if (p != NULL && p->GetColor() == curPlayersColor) {
		vec = p->GetValidMoves(this);
		vec = RemoveOffBoardMoves(vec);
		vec = RemoveMovesThatLeaveInCheck(vec, p, curPlayersColor);
	}

	return vec;
}

//------------------------------------------------------------------------------------------------
void Board::UpdateBoard(Move* move) {
	//cout << "Updating Board" << endl;

	int srow = move->GetStart().GetRow();
	int scol = move->GetStart().GetCol();
	int erow = move->GetEnd().GetRow();
	int ecol = move->GetEnd().GetCol();

	if (move->GetCaptured() != NOTYPE)
		delete grid[erow][ecol];

	grid[erow][ecol] = grid[srow][scol];
	grid[srow][scol] = NULL;
	(grid[erow][ecol])->GetPosition()->SetRow(erow);
	(grid[erow][ecol])->GetPosition()->SetCol(ecol);

}

//------------------------------------------------------------------------------------------------
void Board::UpdateBoardUndo(Move* move) {
	int srow = move->GetStart().GetRow();
	int scol = move->GetStart().GetCol();
	int erow = move->GetEnd().GetRow();
	int ecol = move->GetEnd().GetCol();

	grid[srow][scol] = grid[erow][ecol];
	grid[erow][ecol] = NULL;
	(grid[srow][scol])->GetPosition()->SetRow(srow);
	(grid[srow][scol])->GetPosition()->SetCol(scol);

	if(move->GetCaptured() != NOTYPE) {
		//ImageName captured = GetImageNameCaptured(move);
		switch(move->GetColor()) {
			case WHITE :
			switch(move->GetCaptured()) {
				case PAWN   : grid[erow][ecol] = new Pawn   (BLACK, erow, ecol); break;
				case KNIGHT : grid[erow][ecol] = new Knight (BLACK, erow, ecol); break;
				case BISHOP : grid[erow][ecol] = new Bishop (BLACK, erow, ecol); break;
				case ROOK   : grid[erow][ecol] = new Rook   (BLACK, erow, ecol); break;
				case QUEEN  : grid[erow][ecol] = new Queen  (BLACK, erow, ecol); break;
				case KING   : grid[erow][ecol] = new King   (BLACK, erow, ecol); break;
			}
			break;

			case BLACK :
			switch(move->GetCaptured()) {
				case PAWN   : grid[erow][ecol] = new Pawn   (WHITE, erow, ecol); break;
				case KNIGHT : grid[erow][ecol] = new Knight (WHITE, erow, ecol); break;
				case BISHOP : grid[erow][ecol] = new Bishop (WHITE, erow, ecol); break;
				case ROOK   : grid[erow][ecol] = new Rook   (WHITE, erow, ecol); break;
				case QUEEN  : grid[erow][ecol] = new Queen  (WHITE, erow, ecol); break;
				case KING   : grid[erow][ecol] = new King   (WHITE, erow, ecol); break;
			}
			break;
		}
	}
}

//------------------------------------------------------------------------------------------------
vector<Position> Board::RemoveOffBoardMoves(vector<Position> v) {
	vector<Position>::iterator it;
	for (it=v.begin(); it< v.end();) {
		//Checks if position is off the board
		if ((*it).GetRow() > 7 || (*it).GetRow() < 0 || 
		    (*it).GetCol() > 7 || (*it).GetCol() < 0) 
			v.erase(it);

		else
			it++;
	}
	return v;
}

//------------------------------------------------------------------------------------------------
vector<Position> Board::RemoveMovesThatLeaveInCheck(
			vector<Position> v, Piece* p, PC curPlayersColor) {
	Move* m = new Move();	
	vector<Position>::iterator it;
	for (it=v.begin(); it< v.end();) {
		// Set up the Move object
		m->SetType(p->GetType());
		m->SetColor(p->GetColor());
		Position pos1;
		pos1.SetRow(p->GetPosition()->GetRow());
		pos1.SetCol(p->GetPosition()->GetCol());
		m->SetStart(pos1);

		Position pos2;
		pos2.SetRow((*it).GetRow());
		pos2.SetCol((*it).GetCol());
		m->SetEnd(pos2);
		Piece* posCaptured = GetPieceAt((*it).GetRow(), (*it).GetCol());
		if (posCaptured != NULL)
			m->SetCaptured(posCaptured->GetType());
		else
			m->SetCaptured(NOTYPE);

		// Make the move
		UpdateBoard(m);

		//Check to see if that move left my king in check
		if (curPlayersColor == WHITE) {
			int WKrow = whiteKing->GetPosition()->GetRow();
			int WKcol = whiteKing->GetPosition()->GetCol();
			if (whiteKing->InCheck(WKrow, WKcol, this))
				v.erase(it);
			else
				it++;
		}
		else { 
			int BKrow = blackKing->GetPosition()->GetRow();
			int BKcol = blackKing->GetPosition()->GetCol();
			if (blackKing->InCheck(BKrow, BKcol, this))
				v.erase(it);
			else
				it++;
		}

		// Undo the move
		UpdateBoardUndo(m);
	}
	delete m;
	return v;
}

//------------------------------------------------------------------------------------------------
Piece* Board::GetPieceAt(int row, int col) {
	if (row > 7 || row < 0 || col > 7 || col < 0)
		return NULL;
	return grid[row][col];
}

//------------------------------------------------------------------------------------------------
void Board::SetUpBoard() {

	whiteKing = new King   (WHITE, 7, 4);
	blackKing = new King   (BLACK, 0, 4);

	grid[0][0] = new Rook  (BLACK, 0, 0);
	grid[0][1] = new Knight(BLACK, 0, 1);
	grid[0][2] = new Bishop(BLACK, 0, 2);
	grid[0][3] = new Queen (BLACK, 0, 3);
	//grid[0][4] = new King  (BLACK, 0, 4);
	grid[0][4] = blackKing;

	//blackKing = grid[0][4];

	grid[0][5] = new Bishop(BLACK, 0, 5);
	grid[0][6] = new Knight(BLACK, 0, 6);
	grid[0][7] = new Rook  (BLACK, 0, 7);
	for (int i = 0; i < 8; i++)
		grid[1][i] = new Pawn (BLACK, 1, i);

	for (int i = 2; i < 6; i++)
		for (int j = 0; j < 8; j++)
			grid[i][j] = NULL;

	for (int i = 0; i < 8; i++)
		grid[6][i] = new Pawn (WHITE, 6, i);
	grid[7][0] = new Rook  (WHITE, 7, 0);
	grid[7][1] = new Knight(WHITE, 7, 1);
	grid[7][2] = new Bishop(WHITE, 7, 2);
	grid[7][3] = new Queen (WHITE, 7, 3);
	//grid[7][4] = new King  (WHITE, 7, 4);
	grid[7][4] = whiteKing;

	//whiteKing = grid[7][4];

	grid[7][5] = new Bishop(WHITE, 7, 5);
	grid[7][6] = new Knight(WHITE, 7, 6);
	grid[7][7] = new Rook  (WHITE, 7, 7);
	
	//Piece* invalid = new Piece(WHITE, -1, -1);
}

//------------------------------------------------------------------------------------------------
void Board::ClearBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid[i][j] != NULL) 
				delete grid[i][j];
				grid[i][j] = NULL;
		}
	}
}

King* Board::GetWhiteKing() {
	return whiteKing;
}

King* Board::GetBlackKing() {
	return blackKing;
}
//------------------------------------------------------------------------------------------------

bool Board::Test(ostream & os) {	
	bool success = true;

	//TEST(true);

	return success;
}
