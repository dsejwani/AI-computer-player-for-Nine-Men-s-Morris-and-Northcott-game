#ifndef MOVE_H
#define MOVE_H

#include "pch.h"
using std::string;

// class for a Move in the game
class Move {
public:
	static int ourMovesGenerated;
	static int ourMovesDeleted;
	// different types of moves
	enum MoveType {
		DROP,
		MOVE,
		DROP_AND_CAPTURE,
		MOVE_AND_CAPTURE
	};
	// constructor for DROP type
	Move(MoveType t, int pos1);
	// constructor for DROP_AND_CAPTURE or MOVE type
	Move(MoveType t, int pos1, int pos2);
	// constructor for MOVE_AND_CAPTURE
	Move(MoveType t, int sPos, int ePos, int cPos);
	// copy constructor
	Move(const Move& m);
	// destructor
	~Move();
	// gets the human readable representation of the move
	string getMove();
	// returns the type of the move
	MoveType getType();
	// returns the machine drop position
	int getDropPos();
	// returns the machine start position
	int getStartPos();
	// returns the machine end position
	int getEndPos();
	// returns the machine capture position
	int getCapPos();
	// function for comparing two moves.  Originally I was determining how to order moves by evaluating the boards
	// they produced, but this was too intensive.  So now I just return based on type.  Capture types are best
	static int compareMoves(const void *a, const void *b);
	// static function for translating a position into human readable location
	static string getHumanLocation(int index);
//private:
	// initialization function.  originally this would take the board and set the value of the move.
	// now all it does is just increment the number of moves generated
	void init();
	// the start position (only used for MOVE and MOVE_AND_CAPTURE)
	int myStartPos;
	// the end position (used for DROP, and MOVE)
	int myEndPos;
	// the capture position (used only for CAPTURE types)
	int myCapPos;
	// the type of move this is
	MoveType myType;
};

#endif