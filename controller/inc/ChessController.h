#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H

#include "IChessController.h"
#include "IChessView.h"
#include "IChessPlayer.h"
#include "ChessGame.h"
#include "Position.h"
#include "Move.h"
#include <string>
#include <vector>
#include <deque>
using namespace std;

class ChessController : public IChessController
{
public:

	/**
	 * Constructor
	 */
	ChessController(int option);

	/**
	 * Destructor
	 */
	virtual ~ChessController();
	
	/**
	 * Switches which player is in currently in control
	 */
	void SwitchTurns();

	/**
	 * Indicate to the player that the user clicked on the given
	 * row and column with the mouse.
	 */
	virtual void on_CellSelected(int row, int col, int button);
		
	/**
	 * Handle when a timer event has been signaled.
	 */
	virtual void on_TimerEvent();
	
	///@param row where drag began
	///@param col where drag began
	virtual void on_DragStart(int row,int col);

	///@param row where drag ended
	///@param col where drag ended
	///@return true if the drag resulted in a successful drop
	virtual bool on_DragEnd(int row,int col);

	/**
	 * Handle when the user selected the new game button.
	 */
	virtual void on_NewGame();

	/**
	 * Handle when the user selected the save game button.
	 */
	virtual void on_SaveGame();

	/**
	 * Handle when the user selected the save game as button.
	 */
	virtual void on_SaveGameAs();

	/**
	 * Handle when the user selected the load game button.
	 */
	virtual void on_LoadGame();

	/**
	 * Handle when the user selected the undo move button.
	 */
	virtual void on_UndoMove();
		
	/**
	 * Handle when the user selects to quit the game, either through the
	 * quit button, the close X button, or the file menu.
	 */
	virtual void on_QuitGame();
	
	/**
	 * Set the IChessView that this IChessController will handle inputs for.
	 */
	virtual void SetView(IChessView* view);

	/**
	 * Updates the View to reflect the player's move.
	 */
	void UpdateView();

	/**
	 * Clears all squares of highlights
	 */
	void ClearHighlightedSquares();

	/*
	 * Has the GUI clear any existing pieces and highlights then initializes a new
	 * Chess board
	 */
	void SetUpInitialBoard();

	/*
	 * Returns a pointer to the facade
	 */
	ChessGame* GetGame();

	/*
	 * Returns a copy of curPossibleMoves
	 */
	vector<Position> GetCurPossibleMoves();

	/*
	 * Sets the class variable to a vector of Position objects
	 */
	void SetCurPossibleMoves(vector<Position> v);

	/*
	 * Returns the class variable of the current Move object
	 */
	Move* GetMove();
	
	/*
	 * Updates the GUI when given a Move object (includes setting labels)
	 */
	void UpdateView(Move* move);

	/*
	 * Calls the ChessGame (facade) to update the internal board structure given a Move object
	 */
	void UpdateBoard(Move* move);

private: 
	IChessView* view;
	ChessGame* game;
	IChessPlayer* player1;
	IChessPlayer* player2;
	IChessPlayer** curPlayer;
	string saveFile;
	string loadFile;
	vector<Position> curPossibleMoves;
	Move* move;
	deque<Move> moves;

	
	void ClearAllPieces();
	void UpdateViewUndo(Move* m);
	void UpdateBoardUndo(Move* m);
	ImageName GetImageName(Move* m);
	ImageName GetImageNameCaptured(Move* m);
	void SetBoardFromLoad();
	void UpdateStatus(Status s);
};

#endif

