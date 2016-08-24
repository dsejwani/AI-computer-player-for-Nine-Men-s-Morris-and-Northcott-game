#include "pch.h"
#include "position.h"

int Position::positionsDeleted = 0;
int Position::positionsGenerated = 0;
Position::Position(int location) : _location(location), player(GameController::NEUTRAL), up(NULL), down(NULL), left(NULL), right(NULL) {
	positionsGenerated++;
}
Position::Position(const Position& p) {
	positionsGenerated++;
}
Position::~Position() {
	positionsDeleted++;
}
void Position::setPlayer(GameController::Player p) {
	player = p;
}
int Position::getLocation() {
	return _location;
}
std::string Position::getPlayer() {
	if (player == GameController::NEUTRAL)
		return "+";
	else if (player == GameController::BLACK)
		return "B";
	else
		return "W";
}
