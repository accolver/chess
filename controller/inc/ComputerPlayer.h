#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "IChessPlayer.h"
#include "IChessController.h"
#include "ChessController.h"
#include "ChessGame.h"

class ComputerPlayer : public IChessPlayer {

	public : 
		ComputerPlayer(ChessController* cont);
		~ComputerPlayer();

		/**
		 * Indicate to the player that the user clicked on the given
		 * row and column with the mouse.
		 */
		virtual void on_CellSelected(int row, int col, int button);

		/**
		 * Handle when the timeout duration has passed.
		 */
		virtual void on_TimerEvent();
	
	private :
		ChessController* cont;
};

#endif
