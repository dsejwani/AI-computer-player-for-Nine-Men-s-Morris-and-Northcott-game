#include "pch.h"
#include "GameNode.h"
#include "Move.h"

GameNode::GameNode(int s, Move *m) : score(s), move(m) {}

GameNode::~GameNode() {
	if (move != NULL) {
		delete move;
	}
}