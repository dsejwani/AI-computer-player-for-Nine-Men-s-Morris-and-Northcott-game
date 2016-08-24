#ifndef POSITION_H
#define POSITION_H
#include <string>
#include "gamecontroller.h"

class Position {
private:
	int _location;
public:
	static int positionsGenerated;
	static int positionsDeleted;
	GameController::Player player;
	Position *up;
	Position *down;
	Position *right;
	Position *left;
	Position(int location);
	Position(const Position& p);
	~Position();
	void setPlayer(GameController::Player p);
	int getLocation();
	std::string getPlayer();
};

#endif