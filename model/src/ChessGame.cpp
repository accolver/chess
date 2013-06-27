#include "ChessGame.h"
#include "Position.h"
#include "XMLWriter.h"
#include "XMLReader.h"
#include <vector>
#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------
ChessGame::ChessGame() {
	curPlayersColor = WHITE;
	curStatus = NORMAL;
	board = new Board();
}

//------------------------------------------------------------------------------------------------
ChessGame::~ChessGame() {
	delete board;
}

//------------------------------------------------------------------------------------------------
void ChessGame::on_NewGame() {
	board->SetUpBoard();
}

//------------------------------------------------------------------------------------------------
vector<Position> ChessGame::HumanClick(int row, int col, vector<Position> posMoves, Move* move) {
	bool clickedAHighlightedSquare = false;
	
	//Checks if you clicked on a highlighted square
	vector<Position>::iterator it;
	for (it=posMoves.begin(); it<posMoves.end(); it++) {
		if ((*it).GetRow() == row && (*it).GetCol() == col) {
			clickedAHighlightedSquare = true;
			move->SetEnd(*it);
			move->SetColor(curPlayersColor);
			if (board->GetPieceAt(row, col) != NULL) 
				move->SetCaptured(board->GetPieceAt(row, col)->GetType());
			else
				move->SetCaptured(NOTYPE);
			break;
		}
	}

	// Return an empty vector of possible moves
	if (clickedAHighlightedSquare) {
		vector<Position> v = vector<Position>(0);
		
		return v;
	}

	// Set controller's Move object to reflect
	else {
		Position p(row, col);
		move->SetStart(p);
		if (board->GetPieceAt(row, col) != NULL)
			move->SetType(board->GetPieceAt(row, col)->GetType());
		else 
			move->SetType(NOTYPE);
		return board->GetValidMovesForPiece(row, col, curPlayersColor);
	}
}


//------------------------------------------------------------------------------------------------
void ChessGame::UpdateBoard(Move* move) {
	board->UpdateBoard(move);
}

//------------------------------------------------------------------------------------------------
void ChessGame::UpdateBoardUndo(Move* move) {
	board->UpdateBoardUndo(move);
}

//------------------------------------------------------------------------------------------------
deque<Move> ChessGame::on_LoadGame(string & loadLocation) {
	XMLReader reader;
	return reader.Read(loadLocation);
}


//------------------------------------------------------------------------------------------------
void ChessGame::on_UndoMove() {
}
//------------------------------------------------------------------------------------------------
void ChessGame::on_QuitGame() {
}

//------------------------------------------------------------------------------------------------
void ChessGame::on_SaveGame(string & saveLocation, deque<Move> m) {
	SaveToDisk(saveLocation, m);
}
//------------------------------------------------------------------------------------------------
void ChessGame::on_SaveGameAs(string & saveLocation, deque<Move> m) {
	SaveToDisk(saveLocation, m);
}

//------------------------------------------------------------------------------------------------
bool ChessGame::SaveToDisk(string & saveLocation, deque<Move> m) {
	XMLWriter writer;
	writer.Write(saveLocation, m, board);
}

//------------------------------------------------------------------------------------------------
void ChessGame::SwitchTurns() {
	if (curPlayersColor == WHITE)
		curPlayersColor = BLACK;
	else
		curPlayersColor = WHITE;
}

//------------------------------------------------------------------------------------------------
Board* ChessGame::GetBoard() {
	return board;
}

//------------------------------------------------------------------------------------------------
Status ChessGame::GetStatus() {
	return curStatus;
}

//------------------------------------------------------------------------------------------------
void ChessGame::DetermineKingsStatus() {
	noMovesPossible = true;
	kingInCheck = false;

	// Goes through all pieces of the opposite player and determines if ANY of their 
	// pieces can be moved
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* piece = board->GetPieceAt(i, j);
			if (piece != NULL && piece->GetColor() == curPlayersColor) {
				vector<Position> v = board->GetValidMovesForPiece(i, j, curPlayersColor);
				if (!v.empty()) {
					noMovesPossible = false;
					break;
				}
			}
		}
	}

	// Determines if White King is in Check
	if (curPlayersColor == WHITE) {
		King* wk = board->GetWhiteKing();
		int wkrow = wk->GetPosition()->GetRow();
		int wkcol = wk->GetPosition()->GetCol();
		if (wk->InCheck(wkrow, wkcol, board))
			kingInCheck = true;
	}
	// Determines if Black King is in Check
	else {
		King* bk = board->GetBlackKing();
		int bkrow = bk->GetPosition()->GetRow();
		int bkcol = bk->GetPosition()->GetCol();
		if (bk->InCheck(bkrow, bkcol, board)) 
			kingInCheck = true;
	}
	
	// Assigns the game status accordingly
	if (noMovesPossible) {
		if (kingInCheck)
			curStatus = CHECKMATE;
		else
			curStatus = STALEMATE;
	}
	else if (kingInCheck)
		curStatus = CHECK;
	else
		curStatus = NORMAL;
}
//------------------------------------------------------------------------------------------------
