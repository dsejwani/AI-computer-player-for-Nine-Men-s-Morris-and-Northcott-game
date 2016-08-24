#ifndef EVALSETTINGS_H
#define EVALSETTINGS_H
#include "pch.h"

// class for storing the values for different parts of the evaluation function in board
class EvalSettings {
public:
	EvalSettings();
	EvalSettings(std::string& file);
	int mill_formable;
	int mill_formed;
	int mill_blocked;
	int mill_opponent;
	int captured_piece;
	int lost_piece;
	int adjacent_spot;
	int blocked_opponent_spot;
	int worst_score;
	int best_score;
};

#endif