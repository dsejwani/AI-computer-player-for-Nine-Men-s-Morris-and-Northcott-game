#include "pch.h"
#include "EvalSettings.h"
using std::string;

EvalSettings::EvalSettings() :
	mill_formable(50),
	mill_formed(70),
	mill_blocked(60),
	mill_opponent(-80),
	captured_piece(70),
	lost_piece(-110),
	adjacent_spot(2),
	blocked_opponent_spot(2),
	worst_score(-10000),
	best_score(10000) {}

EvalSettings::EvalSettings(std::string& file) {
}