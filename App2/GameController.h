#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "pch.h"
#include <time.h>

class Board;
class Move;
class GameNode;
class EvalSettings;

// this class controls the running of the game
class GameController {
public:
	// pointer to an eval function
	typedef int (Board::*evalFunc)(EvalSettings& evals);
	// different states of the game
	enum GameState {
		WHITE_WINS,
		BLACK_WINS,
		ILLEGAL_MOVE,
		ONE,
		TWO,
		THREE
	};
	// different players of the game
	enum Player {
		WHITE,
		BLACK,
		NEUTRAL
	};
	// constructor for human vs. computer game
	GameController(int timeLimit, char firstToAct, char compColor);
	// constructor for evaluate vs. evalTest game.  evalGoes determines if evaluate goes first
	GameController(int timeLimit, int gamel, bool evalGoes);
	// the destructor
	virtual ~GameController();
	// takes a string (from user) and moves.  It will move the computer in response
	std::string move(std::string& strMove);
	// bool returns if game is over
	bool isOver();
	// prints game information
	void print();
private:
	// returns the a GameNode containing the best move and the score that move evaluated to
	GameNode *bestMove(clock_t start, EvalSettings& es);
	// has the computer make a move
	std::string computerMove(EvalSettings& es, evalFunc ev);
	// if the game is over
	bool myGameOver;
	// the time limit for each move
	int myTimeLimit;
	// the color for the computer player
	Player myComputerColor;
	// the color for the human player
	Player myHumanColor;
	// if we've hit a time cutoff while searching for the best move
	bool myHitTimeCutoff;
	// the eval settings to use when looking for a best move
	EvalSettings *myEvalSettings;
	// the eval function to use when looking for a best move
	evalFunc myEval;
	// the time we started looking for a best move
	clock_t myStartTime;
	// recursive alpha beta function to get the best move.  The first call argument
	// is used to determine if while expanding the moves we need to eliminate one that
	// generates the gamestate of our last move.
	GameNode *bestMove(Board *b, int depth, int mybest, int hisbest, bool firstCall);
	// the current state of the board
	Board *myBoard;
	// keep track of the last board we produced so we don't get stuck in a loop!
	Board *myLastBoard;
	// the current GameState
	GameState myState;
};
#endif