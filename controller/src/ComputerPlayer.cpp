#include "ComputerPlayer.h"

#include <iostream>
using namespace std;

ComputerPlayer::ComputerPlayer(ChessController* cont) {

}
//------------------------------------------------------------------------------------------------

ComputerPlayer::~ComputerPlayer() {
	this->cont = NULL;
}

//------------------------------------------------------------------------------------------------
void ComputerPlayer::on_CellSelected(int row, int col, int button) {
	
}

//------------------------------------------------------------------------------------------------
void ComputerPlayer::on_TimerEvent() {
	// Implement AI here
}
//------------------------------------------------------------------------------------------------
