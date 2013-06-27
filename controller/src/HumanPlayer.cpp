#include "HumanPlayer.h"

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------------------------
HumanPlayer::HumanPlayer(ChessController* cont) { 
	this->cont = cont;
}

//------------------------------------------------------------------------------------------------
HumanPlayer::~HumanPlayer() {
	this->cont = NULL;
}

//------------------------------------------------------------------------------------------------
void HumanPlayer::on_CellSelected(int row, int col, int button) {
	cont->SetCurPossibleMoves(cont->GetGame()->HumanClick(row, col, cont->GetCurPossibleMoves(), cont->GetMove()));

	cont->UpdateView(cont->GetMove());
}

//------------------------------------------------------------------------------------------------
void HumanPlayer::on_TimerEvent() {
}

//------------------------------------------------------------------------------------------------
