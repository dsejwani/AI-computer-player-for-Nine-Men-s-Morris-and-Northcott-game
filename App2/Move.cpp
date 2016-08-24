#include "pch.h"
#include "Move.h"
#include "Board.h"
using std::string;

int Move::ourMovesGenerated = 0;
int Move::ourMovesDeleted = 0;

Move::Move(MoveType type, int pos1) : myType(type), myEndPos(pos1) {
	init();
}
Move::Move(MoveType type, int pos1, int pos2) : myType(type) {
	if (type == DROP_AND_CAPTURE) {
		myEndPos = pos1;
		myCapPos = pos2;
	}
	else if (type == MOVE) {
		myStartPos = pos1;
		myEndPos = pos2;
	}
	init();
}
Move::Move(MoveType type, int startPos, int endPos, int capPos) : myType(type), myStartPos(startPos), myEndPos(endPos), myCapPos(capPos) {
	init();
}
Move::Move(const Move& m) {
	myStartPos = m.myStartPos;
	myEndPos = m.myEndPos;
	myCapPos = m.myCapPos;
	myType = m.myType;
	ourMovesGenerated++;
}
Move::~Move() {
	ourMovesDeleted++;
}
int Move::compareMoves(const void *a, const void *b) {
	Move * aa = *(Move **)a;
	Move * bb = *(Move **)b;
	return (aa->myType > bb->myType) ? -1 : (aa->myType < bb->myType) ? 1 : 0;
}
string Move::getHumanLocation(int index) {
	string ret;
	switch (index) {
	case 0:
		ret = "A1";
		break;
	case 1:
		ret = "D1";
		break;
	case 2:
		ret = "G1";
		break;
	case 3:
		ret = "B2";
		break;
	case 4:
		ret = "D2";
		break;
	case 5:
		ret = "F2";
		break;
	case 6:
		ret = "C3";
		break;
	case 7:
		ret = "D3";
		break;
	case 8:
		ret = "E3";
		break;
	case 9:
		ret = "A4";
		break;
	case 10:
		ret = "B4";
		break;
	case 11:
		ret = "C4";
		break;
	case 12:
		ret = "E4";
		break;
	case 13:
		ret = "F4";
		break;
	case 14:
		ret = "G4";
		break;
	case 15:
		ret = "C5";
		break;
	case 16:
		ret = "D5";
		break;
	case 17:
		ret = "E5";
		break;
	case 18:
		ret = "B6";
		break;
	case 19:
		ret = "D6";
		break;
	case 20:
		ret = "F6";
		break;
	case 21:
		ret = "A7";
		break;
	case 22:
		ret = "D7";
		break;
	case 23:
		ret = "G7";
		break;
	}
	return ret;
}
Move::MoveType Move::getType() {
	return myType;
}
int Move::getDropPos() {
	return myEndPos;
}
int Move::getStartPos() {
	return myStartPos;
}
int Move::getEndPos() {
	return myEndPos;
}
int Move::getCapPos() {
	return myCapPos;
}
string Move::getMove() {
	if (myType == DROP)
		return getHumanLocation(getEndPos());
	else if (myType == DROP_AND_CAPTURE)
		return getHumanLocation(getEndPos()) + "," + getHumanLocation(getCapPos());
	else if (myType == MOVE)
		return getHumanLocation(getStartPos()) + "-" + getHumanLocation(getEndPos());
	else
		return getHumanLocation(getStartPos()) + "-" + getHumanLocation(getEndPos()) + "," + getHumanLocation(getCapPos());
}
void Move::init() {
	ourMovesGenerated++;
}