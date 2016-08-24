#ifndef GAMENODE_H
#define GAMENODE_H

class Move;

// this class is basically just a holder for a score and move.  This is what the bestMove function returns
class GameNode {
public:
	// basic constructor, we're responsible for cleaning up the move pointer
	GameNode(int s, Move *m);
	~GameNode();
	int score;
	Move *move;
};

#endif