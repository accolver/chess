#ifndef CS240_ChessGame_H
#define CS240_ChessGame_H

#include "Board.h"
#include "Move.h"
#include <deque>
#include <set>
#include <string>

enum Status {NORMAL, CHECK, CHECKMATE, STALEMATE};

class ChessGame {

	public :
		ChessGame();
		~ChessGame();

		/*
		 * Sets up the Board object and initialized all pieces
		 */
		void on_NewGame();

		/*
		 * Saves the current game in XML format given the location to save and
		 * a deque of all the Moves made
		 */
		void on_SaveGame(string & saveLocation, deque<Move> m);

		/*
		 * Same as save but can change the location of the save file
		 */
		void on_SaveGameAs(string & saveLocation, deque<Move> m);

		/*
		 * Loads a game when given a string loadLocation (game is saved in XML format)
		 */
		deque<Move> on_LoadGame(string & loadLocation);

		/*
		 * Undoes the last move
		 */
		void on_UndoMove();

		/*
		 * Destructs objects as needed and exits the program
		 */
		void on_QuitGame();

		/*
		 * Changes the turn to the other player
		 */
		void SwitchTurns();

		/*
		 * Returns a pointer to the Board
		 */
		Board* GetBoard();

		/*
		 * Returns the Status of the game
		 */
		Status GetStatus();

		/*
		 * Updates the Board when given a Move object
		 */
		void UpdateBoard(Move* move);

		/*
		 * Undoes the last move when given a Move object
		 */
		void UpdateBoardUndo(Move* move);

		/*
		 * Sets the Status of the game (eg. NORMAL, CHECK, CHECKMATE, STALEMATE)
		 */
		void DetermineKingsStatus();

		/*
		 * Returns a vector of valid Positions when given a Position (row and column), 
		 * a vector of Positions, and a Move object
		 */
		vector<Position> HumanClick(int row, int col, vector<Position> moves, Move* move);

	private :
		Board* board;
		PC curPlayersColor;
		Status curStatus;
		bool kingInCheck;
		bool noMovesPossible;

		bool SaveToDisk(string & saveLocation, deque<Move> m);
};

#endif
