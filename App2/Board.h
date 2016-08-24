#ifndef BOARD_H
#define BOARD_H
#include "pch.h"
#include "GameController.h"

class Move;
class EvalSettings;
class Position;

// this class stores the state information for a particular board.
// the board can also generate possible moves, apply moves and return other stateful information.
class Board {
private:
	// the player who's turn it is on this board
	GameController::Player myPlayerTurn;
	// all the positions on the board.  this is the machine representation of the board
	Position * myPositions[24];
	// the number of unplaced pieces.  first element is WHITE, second is BLACK
	char myUnplaced[2];
	// the number of placed pieces.  first element is WHITE, second is BLACK
	char myPlaced[2];
	// returns true if the coordinate is one on the board
	bool isLegalCoord(char row, char col);
	// returns the index that a col/row combo is stored in (i.e. col A row 1 returns 0)
	int getArrayIndex(char row, char col);
	// returns true if a start position and end position are adjacent to each other (in the sense of a board move)
	bool isAdjacent(int startPos, int endPos);
	// returns true if having the player at that position would be a mill
	bool isMill(int pos, GameController::Player player);
	// returns true if having the player at that position would be a vertical mill
	bool isVerticalMill(int pos, GameController::Player player);
	// returns true if having the player at that position would be a horizontal mill
	bool isHorizontalMill(int pos, GameController::Player player);
	// adds all move and capture moves to the *moves array.
	void addMoveAndCaptureMoves(Move **moves, int &movesGenerated, int startPos, int endPos);
	// sets up the initial state of the board
	void initialize();
	// returns true if all of the passed in player pieces are in mills (for the exception rule)
	bool allPiecesInMills(GameController::Player player);
	// some functions that are used by the AI to change the board
	void drop(int pos);
	void capture(int pos);
	void move(int startPos, int endPos);
	void changeTurn();
	// counts the number of mills for the passed in player.  The start player specifies
	// what color to look at for the first piece.  This way the function is generic and can
	// count the number of mills for the player, the number of mills that the startPlayer has
	// blocked for the player, or the number of possible mills for the player
	int countMills(GameController::Player startPlayer, GameController::Player player);
	// specific eval functions for each stage of the game
	int evalOne(EvalSettings& evals);
	int evalOneTest(EvalSettings& evals);
	int evalTwo(EvalSettings& evals);
	int evalTwoTest(EvalSettings& evals);
	int evalThree(EvalSettings& evals);
	int evalThreeTest(EvalSettings& evals);
	// returns true if all the pieces on the board for the player are blocked
	bool blocked(GameController::Player player);
public:
	static const int MAX_MOVES = 50;
	static int ourBoardsGenerated;
	static int ourBoardsDeleted;
	// constructor creates a new board and sets the player turn to the passed in player
	Board(GameController::Player pplayer);
	// copy constructor that creates a deep copy
	Board(const Board& b);
	// destructor - deletes all positions on the board
	~Board();
	// returns the GameState representing the stage of the game.
	GameController::GameState getStage();
	// returns the total number of placedPieces on the board
	int placedPieces();
	// returns the number of unplaced pieces for the passed in player
	int getUnplacedPieces(GameController::Player player);
	// takes a move as a string.  validates that the move is legal, then makes the move
	GameController::GameState move(const std::string& command);
	// returns a string representation of which player's turn it is on this board
	std::string getPlayerTurn();
	// returns the enum of which player's turn it is on this board
	GameController::Player getTurn();
	// makes the move on the board.  Since this is a move object, its legality isn't verified
	void move(Move &m);
	// returns a pointer to an array of Move pointers.  Responsibility to clean up is in the hands of the caller.
	Move **getMoves();
	// determines if all the positions are the same in the passed in board as this one
	bool isSameBoardState(Board& b);
	// the main eval function.
	int evaluate(EvalSettings& evals);
	// an eval test function.  this is for writing new eval code and testing it out
	int evalTest(EvalSettings& evals);
	// returns true if the passed in player has won the game
	bool hasWon(GameController::Player player);
	// outputs the board configuration to cout
	void print();
};

#endif