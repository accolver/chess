#include "ChessController.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <iostream>
using namespace std;


//------------------------------------------------------------------------------------------------
ChessController::ChessController(int option) {

	switch (option) {
		case 0 : player1 = new HumanPlayer(this); 
			 player2 = new HumanPlayer(this); break;
		case 1 : player1 = new HumanPlayer(this); 
			 player2 = new ComputerPlayer(this); break;
		case 2 : player1 = new ComputerPlayer(this); 
			 player2 = new HumanPlayer(this); break;
		case 3 : player1 = new ComputerPlayer(this); 
			 player2 = new ComputerPlayer(this); break;
	}

	game = 0;
	move = new Move();
	curPlayer = &player1;

	saveFile = "";
}

//------------------------------------------------------------------------------------------------
ChessController::~ChessController() {
	delete player1;
	delete player2;
	curPlayer = NULL;
	delete move;

	delete game;
	game = 0;
}

//------------------------------------------------------------------------------------------------
void ChessController::SwitchTurns() {
	if ((*curPlayer) == player1) {
		curPlayer = &player2;
		view->SetTopLabel("Black's Turn");
	}
	else {
		curPlayer = &player1;
		view->SetTopLabel("White's Turn");
	}
	game->SwitchTurns();
}

//------------------------------------------------------------------------------------------------
void ChessController::on_CellSelected(int row, int col, int button) {
	
	ChessController::ClearHighlightedSquares();

	(*curPlayer)->on_CellSelected(row, col, button);

	vector<Position>::iterator it;
	for (it=curPossibleMoves.begin(); it<curPossibleMoves.end(); it++)
		view->HighlightSquare((*it).GetRow(), (*it).GetCol(), BLUE_SQUARE);
}

//------------------------------------------------------------------------------------------------	
void ChessController::on_TimerEvent() {
	(*curPlayer)->on_TimerEvent();
}


//------------------------------------------------------------------------------------------------
void ChessController::on_DragStart(int row,int col) {
}


//------------------------------------------------------------------------------------------------
bool ChessController::on_DragEnd(int row,int col) {
	return true;
}

//------------------------------------------------------------------------------------------------
void ChessController::on_NewGame() {
	if (game != 0) {
		delete game;
		game = 0;
	}
	game = new ChessGame();
	curPlayer = &player1;

	view->SetTopLabel("White's Turn");
	game->on_NewGame();
	SetUpInitialBoard();
	curPossibleMoves = vector<Position>(0);
	moves = deque<Move>(0);
}

//------------------------------------------------------------------------------------------------
void ChessController::on_SaveGame() {
	if (saveFile != "") {
		game->on_SaveGame(saveFile, moves);
	}
	else {
		on_SaveGameAs();
	}
	view->SetTopLabel("Game Saved");
}

//------------------------------------------------------------------------------------------------
void ChessController::on_SaveGameAs() {
	saveFile = view->SelectSaveFile();
	game->on_SaveGameAs(saveFile, moves);
	view->SetTopLabel("Game Saved");
}

//------------------------------------------------------------------------------------------------
void ChessController::on_LoadGame() {
	loadFile = view->SelectLoadFile();
	if (loadFile != "") {
		on_NewGame();
		moves = game->on_LoadGame(loadFile);
		SetBoardFromLoad();
	}
}

//------------------------------------------------------------------------------------------------
void ChessController::SetBoardFromLoad() {

	deque<Move> movesCopy = moves;
	moves = deque<Move>(0);
	while (!movesCopy.empty()) {
		Move m = movesCopy.back();
		movesCopy.pop_back();

		UpdateView(&m);
		ClearHighlightedSquares();
	}
}

//------------------------------------------------------------------------------------------------
void ChessController::on_UndoMove() {
	//game->on_UndoMove();
	curPossibleMoves = vector<Position>(0);
	if (!moves.empty()) {
		view->SetBottomLabel("Last Move Undone");
		Move m = moves.front();
		moves.pop_front();

		UpdateViewUndo(&m);
		UpdateBoardUndo(&m);
		SwitchTurns();
		ClearHighlightedSquares();
	}
	else 
		view->SetBottomLabel("No More Moves To Undo");
}

//------------------------------------------------------------------------------------------------	
void ChessController::UpdateViewUndo(Move* m) {

	
	int srow = m->GetStart().GetRow();
	int scol = m->GetStart().GetCol();
	int erow = m->GetEnd().GetRow();
	int ecol = m->GetEnd().GetCol();

	view->ClearPiece(erow, ecol);

	if (m->GetCaptured() != NOTYPE) {
		ImageName captured = GetImageNameCaptured(m);
		view->PlacePiece(erow, ecol, captured);
	}

	ImageName original = GetImageName(m);
	view->PlacePiece(srow, scol, original);
}

//------------------------------------------------------------------------------------------------
void ChessController::UpdateBoardUndo(Move* m) {
	game->UpdateBoardUndo(m);
}

//------------------------------------------------------------------------------------------------
void ChessController::on_QuitGame() {
	game->on_QuitGame();
}

//------------------------------------------------------------------------------------------------
void ChessController::SetView(IChessView* view) {
	this->view = view;
}

//------------------------------------------------------------------------------------------------
void ChessController::UpdateView() {
}

//------------------------------------------------------------------------------------------------
void ChessController::UpdateView(Move* m) {
	//Checks that a valid move was made
	if (m->GetEnd().GetRow() != -1) {
		view->ClearPiece(m->GetStart().GetRow(), m->GetStart().GetCol());
		
		ImageName img = GetImageName(m);
		view->PlacePiece(m->GetEnd().GetRow(), m->GetEnd().GetCol(), img);

		UpdateBoard(m);
		//Make a copy of move object and add to history
		moves.push_front(*m);
		
		//view->SetBottomLabel(""); //@
		SwitchTurns();
		game->DetermineKingsStatus();
		UpdateStatus(game->GetStatus());
	}
	//Reset Cont's move object
	move->Reset();
}

//------------------------------------------------------------------------------------------------
void ChessController::UpdateStatus(Status s) {
	switch (s) {
		case NORMAL    :
			view->SetBottomLabel("");
			break;
		case CHECK     :
			view->SetBottomLabel("Check!");
			break;
		case CHECKMATE :
			view->SetBottomLabel("Checkmate!");
			break;
		case STALEMATE :
			view->SetBottomLabel("Stalemate...");
			break;
	}
}

//------------------------------------------------------------------------------------------------
ImageName ChessController::GetImageName(Move* m) {
	switch (m->GetColor()) {
		case WHITE : 
			switch	(m->GetType()) {
				case PAWN   : return W_PAWN;   break;
				case KNIGHT : return W_KNIGHT; break;
				case BISHOP : return W_BISHOP; break;
				case ROOK   : return W_ROOK;   break;
				case QUEEN  : return W_QUEEN;  break;
				case KING   : return W_KING;   break;
			}		
		break;

		case BLACK : 
			switch	(m->GetType()) {
				case PAWN   : return B_PAWN;   break;
				case KNIGHT : return B_KNIGHT; break;
				case BISHOP : return B_BISHOP; break;
				case ROOK   : return B_ROOK;   break;
				case QUEEN  : return B_QUEEN;  break;
				case KING   : return B_KING;   break;
			}		
		break;
		return NO_IMAGE;
	}
}

//------------------------------------------------------------------------------------------------
ImageName ChessController::GetImageNameCaptured(Move* m) {
	switch (m->GetColor()) {
		case BLACK : 
			switch	(m->GetCaptured()) {
				case PAWN   : return W_PAWN;   break;
				case KNIGHT : return W_KNIGHT; break;
				case BISHOP : return W_BISHOP; break;
				case ROOK   : return W_ROOK;   break;
				case QUEEN  : return W_QUEEN;  break;
				case KING   : return W_KING;   break;
			}		
		break;

		case WHITE : 
			switch	(m->GetCaptured()) {
				case PAWN   : return B_PAWN;   break;
				case KNIGHT : return B_KNIGHT; break;
				case BISHOP : return B_BISHOP; break;
				case ROOK   : return B_ROOK;   break;
				case QUEEN  : return B_QUEEN;  break;
				case KING   : return B_KING;   break;
			}		
		break;
		return NO_IMAGE;
	}
}

//------------------------------------------------------------------------------------------------
void ChessController::UpdateBoard(Move* m) {
	game->UpdateBoard(m);
}

//------------------------------------------------------------------------------------------------
void ChessController::ClearHighlightedSquares() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			view->UnHighlightSquare(i,j);
}

//------------------------------------------------------------------------------------------------
void ChessController::SetUpInitialBoard() {
	ClearAllPieces();
	ClearHighlightedSquares();
	view->PlacePiece(0, 0, B_ROOK);
	view->PlacePiece(0, 1, B_KNIGHT);
	view->PlacePiece(0, 2, B_BISHOP);
	view->PlacePiece(0, 3, B_QUEEN);
	view->PlacePiece(0, 4, B_KING);
	view->PlacePiece(0, 5, B_BISHOP);
	view->PlacePiece(0, 6, B_KNIGHT);
	view->PlacePiece(0, 7, B_ROOK);
	for (int i = 0; i < 8; i++)
		view->PlacePiece(1, i, B_PAWN);


	for (int j = 0; j < 8; j++)
		view->PlacePiece(6, j, W_PAWN);
	view->PlacePiece(7, 0, W_ROOK);
	view->PlacePiece(7, 1, W_KNIGHT);
	view->PlacePiece(7, 2, W_BISHOP);
	view->PlacePiece(7, 3, W_QUEEN);
	view->PlacePiece(7, 4, W_KING);
	view->PlacePiece(7, 5, W_BISHOP);
	view->PlacePiece(7, 6, W_KNIGHT);
	view->PlacePiece(7, 7, W_ROOK);
}

//------------------------------------------------------------------------------------------------
ChessGame* ChessController::GetGame() {
	return game;
}

//------------------------------------------------------------------------------------------------
vector<Position> ChessController::GetCurPossibleMoves() {
	return curPossibleMoves;
}

//------------------------------------------------------------------------------------------------
void ChessController::SetCurPossibleMoves(vector<Position> v) {
	curPossibleMoves = v;
}

//------------------------------------------------------------------------------------------------
Move* ChessController::GetMove() {
	return move;
}

//------------------------------------------------------------------------------------------------
void ChessController::ClearAllPieces() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			view->ClearPiece(i,j);
}
//------------------------------------------------------------------------------------------------
