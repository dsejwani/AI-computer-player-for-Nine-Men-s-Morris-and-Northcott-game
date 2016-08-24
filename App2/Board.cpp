#include "pch.h"
#include "Board.h"
#include "Move.h"
#include "Position.h"
#include "EvalSettings.h"
using std::endl;
using std::cout;
using std::string;

int Board::ourBoardsGenerated = 0;
int Board::ourBoardsDeleted = 0;

// returns the GameState representing the stage of the game.
GameController::GameState Board::getStage() {
	if (myUnplaced[GameController::WHITE] > 0 || myUnplaced[GameController::BLACK] > 0)
		return GameController::ONE;
	else if (myPlaced[GameController::WHITE] < 4 || myPlaced[GameController::BLACK] < 4)
		return GameController::THREE;
	else
		return GameController::TWO;
}
// returns true if the coordinate is one on the board
bool Board::isLegalCoord(char row, char col) {
	bool legal = false;
	if (row == '1' || row == '7') {
		if (col == 'A' || col == 'D' || col == 'G')
			legal = true;
	}
	else if (row == '2' || row == '6') {
		if (col == 'B' || col == 'D' || col == 'F')
			legal = true;
	}
	else if (row == '3' || row == '5') {
		if (col == 'C' || col == 'D' || col == 'E')
			legal = true;
	}
	else if (row == '4')
		if (col == 'A' || col == 'B' || col == 'C' || col == 'E' || col == 'F' || col == 'G')
			legal = true;
	return legal;
}
// returns the index that a col/row combo is stored in (i.e. col A row 1 returns 0)
int Board::getArrayIndex(char row, char col) {
	int index = 0;
	switch (row) {
	case '1':
		if (col == 'A') index = 0;
		else if (col == 'D') index = 1;
		else index = 2;
		break;
	case '2':
		if (col == 'B') index = 3;
		else if (col == 'D') index = 4;
		else index = 5;
		break;
	case '3':
		if (col == 'C') index = 6;
		else if (col == 'D') index = 7;
		else index = 8;
		break;
	case '4':
		if (col == 'A') index = 9;
		else if (col == 'B') index = 10;
		else if (col == 'C') index = 11;
		else if (col == 'E') index = 12;
		else if (col == 'F') index = 13;
		else index = 14;
		break;
	case '5':
		if (col == 'C') index = 15;
		else if (col == 'D') index = 16;
		else index = 17;
		break;
	case '6':
		if (col == 'B') index = 18;
		else if (col == 'D') index = 19;
		else index = 20;
		break;
	default:
		if (col == 'A') index = 21;
		else if (col == 'D') index = 22;
		else index = 23;
		break;
	}
	return index;
}
// returns true if a start position and end position are adjacent to each other (in the sense of a board move)
bool Board::isAdjacent(int startPos, int endPos) {
	if (myPositions[startPos]->up != NULL) {
		if (myPositions[startPos]->up->getLocation() == endPos)
			return true;
	}
	if (myPositions[startPos]->down != NULL) {
		if (myPositions[startPos]->down->getLocation() == endPos)
			return true;
	}
	if (myPositions[startPos]->left != NULL) {
		if (myPositions[startPos]->left->getLocation() == endPos)
			return true;
	}
	if (myPositions[startPos]->right != NULL) {
		if (myPositions[startPos]->right->getLocation() == endPos)
			return true;
	}
	return false;
}
bool Board::isMill(int pos, GameController::Player player) {
	bool ret = false;
	ret = isVerticalMill(pos, player);
	if (!ret)
		ret = isHorizontalMill(pos, player);
	return ret;
}
bool Board::isVerticalMill(int pos, GameController::Player player) {
	bool ret = false;
	if (myPositions[pos]->up == NULL) {  // both neighbors are below
		ret = (myPositions[pos]->down->player == myPositions[pos]->down->down->player) &&
			(myPositions[pos]->down->player == player);
	}
	else if (myPositions[pos]->down == NULL) {  // both above
		ret = (myPositions[pos]->up->player == myPositions[pos]->up->up->player) &&
			(myPositions[pos]->up->player == player);
	}
	else {
		ret = (myPositions[pos]->up->player == myPositions[pos]->down->player) &&
			(myPositions[pos]->up->player == player);
	}
	return ret;
}
bool Board::isHorizontalMill(int pos, GameController::Player player) {
	bool ret = false;
	if (myPositions[pos]->left == NULL) { // both to right
		ret = (myPositions[pos]->right->player == myPositions[pos]->right->right->player) &&
			(myPositions[pos]->right->player == player);
	}
	else if (myPositions[pos]->right == NULL) { // both to left
		ret = (myPositions[pos]->left->player == myPositions[pos]->left->left->player) &&
			(myPositions[pos]->left->player == player);
	}
	else {
		ret = (myPositions[pos]->left->player == myPositions[pos]->right->player) &&
			(myPositions[pos]->left->player == player);
	}
	return ret;
}
void Board::addMoveAndCaptureMoves(Move **moves, int &movesGenerated, int startPos, int endPos) {
	// change the start position to GameController::NEUTRAL, we'll change it back
	myPositions[startPos]->setPlayer(GameController::NEUTRAL);
	if (isMill(endPos, myPlayerTurn)) {
		int capMoves = 0;
		GameController::Player capPlayer = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
		for (int j = 0; j < 24; j++) {
			if (myPositions[j]->player == capPlayer && !isMill(j, myPositions[j]->player) && movesGenerated < MAX_MOVES) {
				capMoves++;
				Move *m = new Move(Move::MOVE_AND_CAPTURE, startPos, endPos, j);
				moves[movesGenerated++] = m;
			}
		}
		// exception rule.  if all the opponenet's pieces are in mills, we can pull one out
		if (capMoves == 0) {
			for (int j = 0; j < 24; j++) {
				if (myPositions[j]->player == capPlayer && movesGenerated < MAX_MOVES) {
					Move *m = new Move(Move::MOVE_AND_CAPTURE, startPos, endPos, j);
					moves[movesGenerated++] = m;
				}
			}
		}
	}
	else if (movesGenerated < MAX_MOVES) {
		Move *m = new Move(Move::MOVE, startPos, endPos);
		moves[movesGenerated++] = m;
	}
	myPositions[startPos]->setPlayer(myPlayerTurn);
}
void Board::initialize() {
	ourBoardsGenerated++;
	myUnplaced[GameController::WHITE] = 9;
	myUnplaced[GameController::BLACK] = 9;
	myPlaced[GameController::WHITE] = 0;
	myPlaced[GameController::BLACK] = 0;
	for (int i = 0; i < 24; i++)
		myPositions[i] = new Position(i);
	// now set the up, down, left, and right pointers for each position on board
	myPositions[0]->right = myPositions[1]; myPositions[0]->down = myPositions[9];
	myPositions[1]->left = myPositions[0]; myPositions[1]->down = myPositions[4]; myPositions[1]->right = myPositions[2];
	myPositions[2]->left = myPositions[1]; myPositions[2]->down = myPositions[14];
	myPositions[3]->right = myPositions[4]; myPositions[3]->down = myPositions[10];
	myPositions[4]->left = myPositions[3]; myPositions[4]->right = myPositions[5]; myPositions[4]->up = myPositions[1]; myPositions[4]->down = myPositions[7];
	myPositions[5]->left = myPositions[4]; myPositions[5]->down = myPositions[13];
	myPositions[6]->right = myPositions[7]; myPositions[6]->down = myPositions[11];
	myPositions[7]->left = myPositions[6]; myPositions[7]->right = myPositions[8]; myPositions[7]->up = myPositions[4];
	myPositions[8]->left = myPositions[7]; myPositions[8]->down = myPositions[12];
	myPositions[9]->right = myPositions[10]; myPositions[9]->up = myPositions[0]; myPositions[9]->down = myPositions[21];
	myPositions[10]->left = myPositions[9]; myPositions[10]->right = myPositions[11]; myPositions[10]->up = myPositions[3]; myPositions[10]->down = myPositions[18];
	myPositions[11]->left = myPositions[10]; myPositions[11]->up = myPositions[6]; myPositions[11]->down = myPositions[15];
	myPositions[12]->right = myPositions[13]; myPositions[12]->up = myPositions[8]; myPositions[12]->down = myPositions[17];
	myPositions[13]->left = myPositions[12]; myPositions[13]->right = myPositions[14]; myPositions[13]->up = myPositions[5]; myPositions[13]->down = myPositions[20];
	myPositions[14]->left = myPositions[13]; myPositions[14]->up = myPositions[2]; myPositions[14]->down = myPositions[23];
	myPositions[15]->right = myPositions[16]; myPositions[15]->up = myPositions[11];
	myPositions[16]->left = myPositions[15]; myPositions[16]->right = myPositions[17]; myPositions[16]->down = myPositions[19];
	myPositions[17]->left = myPositions[16]; myPositions[17]->up = myPositions[12];
	myPositions[18]->right = myPositions[19]; myPositions[18]->up = myPositions[10];
	myPositions[19]->left = myPositions[18]; myPositions[19]->right = myPositions[20]; myPositions[19]->up = myPositions[16]; myPositions[19]->down = myPositions[22];
	myPositions[20]->left = myPositions[19]; myPositions[20]->up = myPositions[13];
	myPositions[21]->right = myPositions[22]; myPositions[21]->up = myPositions[9];
	myPositions[22]->left = myPositions[21]; myPositions[22]->right = myPositions[23]; myPositions[22]->up = myPositions[19];
	myPositions[23]->left = myPositions[22]; myPositions[23]->up = myPositions[14];
}
Board::~Board() {
	for (int i = 0; i < 24; i++)
		delete myPositions[i];
	ourBoardsDeleted++;
}
Board::Board(GameController::Player pplayer) : myPlayerTurn(pplayer) {
	initialize();
}
Board::Board(const Board& b) {
	// first initialize as blank new board
	initialize();
	// now do the deep copy stuff
	myUnplaced[GameController::WHITE] = b.myUnplaced[GameController::WHITE];
	myUnplaced[GameController::BLACK] = b.myUnplaced[GameController::BLACK];
	myPlaced[GameController::WHITE] = b.myPlaced[GameController::WHITE];
	myPlaced[GameController::BLACK] = b.myPlaced[GameController::BLACK];
	myPlayerTurn = b.myPlayerTurn;
	for (int i = 0; i < 24; i++)
		myPositions[i]->player = b.myPositions[i]->player;
}
bool Board::allPiecesInMills(GameController::Player player) {
	int piecesInMills = 0;
	for (int i = 0; i < 24; i++) {
		if (myPositions[i]->player == player && isMill(myPositions[i]->getLocation(), player))
			piecesInMills++;
	}
	if (piecesInMills == myPlaced[player])
		return true;
	else
		return false;
}
GameController::GameState Board::move(const string& command) {
	GameController::GameState state = GameController::ILLEGAL_MOVE;
	// first we need to figure out if it's a placement, placement and capture, move, or move and capture
	if (command.size() == 2) { // it's a placement
							   // verify legal coord, we're in stage one, and the current player has a piece to place
		if (isLegalCoord(command[1], command[0]) && getStage() == GameController::ONE && myUnplaced[myPlayerTurn] > 0) {
			int index = getArrayIndex(command[1], command[0]);
			if (myPositions[index]->player == GameController::NEUTRAL) {  // make sure there isn't a piece already there
				myPositions[index]->setPlayer(myPlayerTurn);  // move
				myUnplaced[myPlayerTurn]--;
				myPlaced[myPlayerTurn]++;
				myPlayerTurn = myPlayerTurn == GameController::WHITE ? GameController::BLACK : GameController::WHITE;
				state = getStage();
			}
		}
	}
	// next case is either a simple move or a drop and capture
	else if (command.size() == 5) {
		if (command[2] == ',') { // it's a drop and capture
			if (isLegalCoord(command[1], command[0]) && isLegalCoord(command[4], command[3])) {
				int dropPos = getArrayIndex(command[1], command[0]);
				int capturePos = getArrayIndex(command[4], command[3]);
				// verify that the drop forms a mill and the piece they're trying to capture isn't in a mill
				if (isMill(dropPos, myPlayerTurn) &&
					(!isMill(capturePos, myPositions[capturePos]->player) || allPiecesInMills(myPositions[capturePos]->player))) {
					// make the move
					myPositions[dropPos]->setPlayer(myPlayerTurn);
					myPositions[capturePos]->setPlayer(GameController::NEUTRAL);
					myUnplaced[myPlayerTurn]--;
					myPlaced[myPlayerTurn]++;
					myPlayerTurn = myPlayerTurn == GameController::WHITE ? GameController::BLACK : GameController::WHITE;
					myPlaced[myPlayerTurn]--;
					state = getStage();
				}
			}
		}
		else {  // it's a simple move
				// verify both coords are valid
			if (isLegalCoord(command[1], command[0]) && isLegalCoord(command[4], command[3])) {
				int startPos = getArrayIndex(command[1], command[0]);
				int endPos = getArrayIndex(command[4], command[3]);
				// the startPos must be owned by the player and the endPos must be GameController::NEUTRAL
				if (myPositions[startPos]->player == myPlayerTurn && myPositions[endPos]->player == GameController::NEUTRAL) {
					// the move must be to an adjacent location or if not the player must have only 3 pieces
					if (isAdjacent(startPos, endPos) || myPlaced[myPlayerTurn] == 3) {
						// the move is legal, do it and update board state
						myPositions[startPos]->setPlayer(GameController::NEUTRAL);
						myPositions[endPos]->setPlayer(myPlayerTurn);
						myPlayerTurn = myPlayerTurn == GameController::WHITE ? GameController::BLACK : GameController::WHITE;
						state = getStage();
					}
				}
			}
		}
	}
	// last case is a move and capture
	else if (command.size() == 8) {
		// verify all three coords are valid
		if (isLegalCoord(command[1], command[0]) && isLegalCoord(command[4], command[3]) && isLegalCoord(command[7], command[6])) {
			int startPos = getArrayIndex(command[1], command[0]);
			int endPos = getArrayIndex(command[4], command[3]);
			int capPos = getArrayIndex(command[7], command[6]);
			// the startPos must be owned by the player and the endPos must be GameController::NEUTRAL
			// the move must form a mill (endPos)
			// the capPos must also not be in a mill
			if (myPositions[startPos]->player == myPlayerTurn &&
				myPositions[endPos]->player == GameController::NEUTRAL &&
				isMill(endPos, myPlayerTurn) &&
				(!isMill(capPos, myPositions[capPos]->player) || allPiecesInMills(myPositions[capPos]->player))) {
				// the move must be to an adjacent location or if not the player must have only 3 pieces
				if (isAdjacent(startPos, endPos) || myPlaced[myPlayerTurn] == 3) {
					// the move is legal, do it and update board state
					myPositions[startPos]->setPlayer(GameController::NEUTRAL);
					myPositions[endPos]->setPlayer(myPlayerTurn);
					myPositions[capPos]->setPlayer(GameController::NEUTRAL);
					myPlayerTurn = myPlayerTurn == GameController::WHITE ? GameController::BLACK : GameController::WHITE;
					myPlaced[myPlayerTurn]--;
					state = getStage();
				}
			}
		}
	}
	if (hasWon(GameController::BLACK))
		state = GameController::BLACK_WINS;
	else if (hasWon(GameController::WHITE))
		state = GameController::WHITE_WINS;
	return state;
}

std::string Board::getPlayerTurn() {
	if (myPlayerTurn == GameController::BLACK)
		return "Black";
	else
		return "White";
}
// some functions that are used by the AI to change the board
void Board::drop(int pos) {
	myPositions[pos]->player = myPlayerTurn;
	myUnplaced[myPlayerTurn]--;
	myPlaced[myPlayerTurn]++;
}
void Board::capture(int pos) {
	GameController::Player capPlayer = myPositions[pos]->player;
	myPositions[pos]->setPlayer(GameController::NEUTRAL);
	myPlaced[capPlayer]--;
}
void Board::move(int startPos, int endPos) {
	myPositions[startPos]->setPlayer(GameController::NEUTRAL);
	myPositions[endPos]->setPlayer(myPlayerTurn);
}
void Board::changeTurn() {
	myPlayerTurn = myPlayerTurn == GameController::WHITE ? GameController::BLACK : GameController::WHITE;
}
GameController::Player Board::getTurn() {
	return myPlayerTurn;
}
void Board::move(Move &m) {
	if (m.getType() == Move::DROP)
		drop(m.getEndPos());
	else if (m.getType() == Move::DROP_AND_CAPTURE) {
		drop(m.getEndPos());
		capture(m.getCapPos());
	}
	else if (m.getType() == Move::MOVE)
		move(m.getStartPos(), m.getEndPos());
	else {
		move(m.getStartPos(), m.getEndPos());
		capture(m.getCapPos());
	}
	changeTurn();
}
// returns true if the passed in board contains the same state as this one
bool Board::isSameBoardState(Board& b) {
	bool ret = true;
	if (myPlaced[GameController::WHITE] != b.myPlaced[GameController::WHITE])
		ret = false;
	else if (myPlaced[GameController::BLACK] != b.myPlaced[GameController::BLACK])
		ret = false;
	else if (myUnplaced[GameController::WHITE] != b.myUnplaced[GameController::WHITE])
		ret = false;
	else if (myUnplaced[GameController::BLACK] != b.myUnplaced[GameController::BLACK])
		ret = false;
	for (int i = 0; i < 24; i++) {
		if (myPositions[i]->player != b.myPositions[i]->player) {
			ret = false;
			break;
		}
	}
	return ret;
}
Move **Board::getMoves() {
	Move **moves = new Move*[MAX_MOVES];
	for (int i = 0; i < MAX_MOVES; i++)
		moves[i] = NULL;
	int movesGenerated = 0;
	// if we're in stage one enumerate all the possible drops
	if (myUnplaced[myPlayerTurn] > 0) {
		for (int i = 0; i < 24; i++) {
			if (myPositions[i]->player == GameController::NEUTRAL) {
				if (isMill(i, myPlayerTurn)) {
					GameController::Player capPlayer = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;

					// the capMoves part added for the exception rule.  if all the other player's pieces are in mills
					// we can remove one from them
					int capMoves = 0;
					for (int j = 0; j < 24; j++) {
						if (myPositions[j]->player == capPlayer && !isMill(j, myPositions[j]->player) && movesGenerated < MAX_MOVES) {
							capMoves++;
							Move *m = new Move(Move::DROP_AND_CAPTURE, i, j);
							moves[movesGenerated++] = m;
						}
					}
					// exception rule
					if (capMoves == 0) {
						for (int j = 0; j < 24; j++) {
							if (myPositions[j]->player == capPlayer && movesGenerated < MAX_MOVES) {
								Move *m = new Move(Move::DROP_AND_CAPTURE, i, j);
								moves[movesGenerated++] = m;
							}
						}
					}
					// end exception
				}
				else if (movesGenerated < MAX_MOVES) {
					Move *m = new Move(Move::DROP, i);
					moves[movesGenerated++] = m;
				}
			}
		}
	}
	// if we're in stage two enumerate all the possible adjacent moves
	else if (myPlaced[myPlayerTurn] > 3) {
		for (int i = 0; i < 24; i++) {
			// first figure out which pieces we own
			if (myPositions[i]->player == myPlayerTurn) {
				// now look at each adjacent empty spot
				// for each one, if making the move forms a mill, enumerate the possible captures
				if (myPositions[i]->up != NULL && myPositions[i]->up->player == GameController::NEUTRAL) {
					addMoveAndCaptureMoves(moves, movesGenerated, i, myPositions[i]->up->getLocation());
				}
				if (myPositions[i]->down != NULL && myPositions[i]->down->player == GameController::NEUTRAL) {
					addMoveAndCaptureMoves(moves, movesGenerated, i, myPositions[i]->down->getLocation());
				}
				if (myPositions[i]->left != NULL && myPositions[i]->left->player == GameController::NEUTRAL) {
					addMoveAndCaptureMoves(moves, movesGenerated, i, myPositions[i]->left->getLocation());
				}
				if (myPositions[i]->right != NULL && myPositions[i]->right->player == GameController::NEUTRAL) {
					addMoveAndCaptureMoves(moves, movesGenerated, i, myPositions[i]->right->getLocation());
				}
			}
		}
	}
	// if we're in stage three enumerate all possible move/drops
	else {
		for (int i = 0; i < 24; i++) {
			// first we find which pieces we own
			if (myPositions[i]->player == myPlayerTurn) {
				// now look at each empty spot
				// for each one, if making the move forms a mill, enumberate the possible captures
				for (int j = 0; j < 24; j++) {
					if (myPositions[j]->player == GameController::NEUTRAL) {
						addMoveAndCaptureMoves(moves, movesGenerated, i, j);
					}
				}
			}
		}
	}
	qsort(moves, movesGenerated, sizeof(Move*), Move::compareMoves);
	return moves;
}
int Board::countMills(GameController::Player startPlayer, GameController::Player player) {
	int ret = 0;
	bool locInH[24];
	bool locInV[24];
	for (int i = 0; i < 24; i++) {
		if (myPositions[i]->player == startPlayer) {
			if (!locInH[i] && isHorizontalMill(i, player)) {
				locInH[i] = true;
				ret++;
				if (myPositions[i]->left == NULL) {
					locInH[myPositions[i]->right->getLocation()] = true;
					locInH[myPositions[i]->right->right->getLocation()] = true;
				}
				else if (myPositions[i]->right == NULL) {
					locInH[myPositions[i]->left->getLocation()] = true;
					locInH[myPositions[i]->left->left->getLocation()] = true;
				}
				else {
					locInH[myPositions[i]->right->getLocation()] = true;
					locInH[myPositions[i]->left->getLocation()] = true;
				}
			}
			if (!locInV[i] && isVerticalMill(i, player)) {
				locInV[i] = true;
				ret++;
				if (myPositions[i]->up == NULL) {
					locInV[myPositions[i]->down->getLocation()] = true;
					locInV[myPositions[i]->down->down->getLocation()] = true;
				}
				else if (myPositions[i]->down == NULL) {
					locInV[myPositions[i]->up->getLocation()] = true;
					locInV[myPositions[i]->up->up->getLocation()] = true;
				}
				else {
					locInV[myPositions[i]->down->getLocation()] = true;
					locInV[myPositions[i]->up->getLocation()] = true;
				}
			}
		}
	}
	return ret;
}
int Board::placedPieces() {
	return myPlaced[GameController::BLACK] + myPlaced[GameController::WHITE];
}
int Board::getUnplacedPieces(GameController::Player player) {
	return myUnplaced[player];
}
int Board::evaluate(EvalSettings& evals) {
	if (getStage() == GameController::ONE)
		return evalOne(evals);
	else if (getStage() == GameController::TWO)
		return evalTwo(evals);
	else
		return evalThree(evals);
}
int Board::evalTest(EvalSettings& evals) {
	if (getStage() == GameController::ONE)
		return evalOneTest(evals);
	else if (getStage() == GameController::TWO)
		return evalTwoTest(evals);
	else
		return evalThreeTest(evals);
}
int Board::evalOne(EvalSettings& evals) {
	GameController::Player opponent = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	int ret = 0;
	//// a board that gives me an opportunity to form a mill is good
	//ret+= (evals.mill_formable*countMills(GameController::NEUTRAL, myPlayerTurn));
	//// give me points for each mill I have
	//ret+= (evals.mill_formed*countMills(myPlayerTurn, myPlayerTurn));
	// give me points for each mill I blocked
	ret += (evals.mill_blocked*countMills(myPlayerTurn, opponent));

	// give me points for each piece I have on the board.  I get points for range of movement
	// this is specific for stage one
	for (int i = 0; i < 24; i++) {
		if (myPositions[i]->player == myPlayerTurn) {
			if (myPositions[i]->up != NULL)
				ret += evals.adjacent_spot;
			if (myPositions[i]->down != NULL)
				ret += evals.adjacent_spot;
			if (myPositions[i]->left != NULL)
				ret += evals.adjacent_spot;
			if (myPositions[i]->right != NULL)
				ret += evals.adjacent_spot;
		}
	}
	// give me points for each piece I have captured
	for (int i = 9; i > (myPlaced[opponent] + myUnplaced[opponent]); i--)
		ret += evals.captured_piece;
	// take away points for each piece my opponent has captured
	for (int i = 9; i > (myPlaced[myPlayerTurn] + myUnplaced[myPlayerTurn]); i--)
		ret += evals.lost_piece;
	// take away points for each mill my opponent has formed
	ret += (evals.mill_opponent*countMills(opponent, opponent));
	return ret;
}
int Board::evalOneTest(EvalSettings &evals) {
	GameController::Player opponent = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	int ret = 0;
	// give me points for each piece I have on the board.  I get points for range of movement
	// this is specific for stage one
	for (int i = 0; i < 24; i++) {
		if (myPositions[i]->player == myPlayerTurn) {
			if (myPositions[i]->up != NULL)
				ret += evals.adjacent_spot;
			if (myPositions[i]->down != NULL)
				ret += evals.adjacent_spot;
			if (myPositions[i]->left != NULL)
				ret += evals.adjacent_spot;
			if (myPositions[i]->right != NULL)
				ret += evals.adjacent_spot;
		}
	}
	// give me points for each piece I have captured
	for (int i = 9; i > (myPlaced[opponent] + myUnplaced[opponent]); i--)
		ret += evals.captured_piece;
	// take away points for each piece my opponent has captured
	for (int i = 9; i > (myPlaced[myPlayerTurn] + myUnplaced[myPlayerTurn]); i--)
		ret += evals.lost_piece;
	return ret;
}
int Board::evalTwo(EvalSettings& evals) {
	GameController::Player opponent = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	int ret = 0;
	// a board in which I lose is the worst!  we can stop right here.
	if (hasWon(opponent))
		return evals.worst_score;
	// a board in which I win is the best!
	if (hasWon(myPlayerTurn))
		return evals.best_score;
	// give me points for each piece I have captured
	for (int i = 9; i > (myPlaced[opponent] + myUnplaced[opponent]); i--)
		ret += evals.captured_piece;
	// take away points for each piece my opponent has captured
	for (int i = 9; i > (myPlaced[myPlayerTurn] + myUnplaced[myPlayerTurn]); i--)
		ret += evals.lost_piece;
	// a board that gives me an opportunity to form a mill is good
	ret += (evals.mill_formable*countMills(GameController::NEUTRAL, myPlayerTurn));
	// give me points for each mill I have
	ret += (evals.mill_formed*countMills(myPlayerTurn, myPlayerTurn));
	// take away points for each mill my opponent has formed
	ret += (evals.mill_opponent*countMills(opponent, opponent));
	// give me points for each spot of my opponent that is blocked
	for (int i = 0; i < 24; i++) {
		if (myPositions[i]->player == opponent) {
			bool blocked = true;
			if (myPositions[i]->up != NULL && myPositions[i]->up->player == GameController::NEUTRAL)
				blocked = false;
			else if (myPositions[i]->down != NULL && myPositions[i]->down->player == GameController::NEUTRAL)
				blocked = false;
			else if (myPositions[i]->left != NULL && myPositions[i]->left->player == GameController::NEUTRAL)
				blocked = false;
			else if (myPositions[i]->right != NULL && myPositions[i]->right->player == GameController::NEUTRAL)
				blocked = false;
			if (blocked)
				ret += evals.blocked_opponent_spot;
		}
	}
	return ret;
}
int Board::evalTwoTest(EvalSettings& evals) {
	//GameController::Player opponent = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	//int ret = 0;
	//// a board in which I lose is the worst!  we can stop right here.
	//if (hasWon(opponent))
	//	return evals.worst_score;
	//// a board in which I win is great!
	//if (hasWon(myPlayerTurn))
	//	return evals.best_score;
	//// give me points for each piece I have captured
	//for (int i = 9; i > (myPlaced[opponent] + myUnplaced[opponent]); i--)
	//	ret+= evals.captured_piece;
	//// take away points for each piece my opponent has captured
	//for (int i = 9; i > (myPlaced[myPlayerTurn] + myUnplaced[myPlayerTurn]); i--)
	//	ret+= evals.lost_piece;
	//return ret;
	return evalOne(evals);
}
int Board::evalThree(EvalSettings& evals) {
	GameController::Player opponent = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	int ret = 0;
	// a board in which I lose is the worst!  we can stop right here.
	if (hasWon(opponent))
		return evals.worst_score;
	// give me points for each piece I have captured
	for (int i = 9; i > (myPlaced[opponent] + myUnplaced[opponent]); i--)
		ret += evals.captured_piece;
	// a board that gives me an opportunity to form a mill is good
	ret += (evals.mill_formable*countMills(GameController::NEUTRAL, myPlayerTurn));
	// give me points for each mill I blocked
	ret += (evals.mill_blocked*countMills(myPlayerTurn, opponent));
	return ret;
}
int Board::evalThreeTest(EvalSettings& evals) {
	//GameController::Player opponent = (myPlayerTurn == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	//int ret = 0;
	//// a board in which I lose is the worst!  we can stop right here.
	//if (hasWon(opponent))
	//	return evals.worst_score;
	//// a board in which I win is great!
	//if (hasWon(myPlayerTurn))
	//	return evals.best_score;
	//// give me points for each piece I have captured
	//for (int i = 9; i > (myPlaced[opponent] + myUnplaced[opponent]); i--)
	//	ret+= evals.captured_piece;
	//// take away points for each piece my opponent has captured
	//for (int i = 9; i > (myPlaced[myPlayerTurn] + myUnplaced[myPlayerTurn]); i--)
	//	ret+= evals.lost_piece;
	//return ret;
	return evalOne(evals);
}
// returns true if all the pieces on the board for the player are blocked
bool Board::blocked(GameController::Player player) {
	// check every piece on the board
	for (int i = 0; i < 24; i++) {
		// if it's the player's piece check if it can move
		if (myPositions[i]->player == player) {
			// if it can move up, down, left, or right then the player isn't blocked
			if (myPositions[i]->up != NULL && myPositions[i]->up->player == GameController::NEUTRAL)
				return false;
			if (myPositions[i]->down != NULL && myPositions[i]->down->player == GameController::NEUTRAL)
				return false;
			if (myPositions[i]->left != NULL && myPositions[i]->left->player == GameController::NEUTRAL)
				return false;
			if (myPositions[i]->right != NULL && myPositions[i]->right->player == GameController::NEUTRAL)
				return false;
		}
	}
	// we must be blocked
	return true;
}
bool Board::hasWon(GameController::Player player) {
	GameController::Player opponent = (player == GameController::WHITE) ? GameController::BLACK : GameController::WHITE;
	// if the opponent has unplaced pieces, we're still in stage one and we haven't won
	if (myUnplaced[opponent] > 0)
		return false;
	// if the opponent has less than three pieces then we've won!
	if (myPlaced[opponent] + myUnplaced[opponent] < 3)
		return true;
	// if the opponent is blocked then we've won!
	return blocked(opponent);
}
// outputs the board configuration to cout
void Board::print() {
	//	cout << "It is the " << getPlayerTurn() << " player's turn." << endl << endl;
	cout << "    A   B   C   D   E   F   G" << endl << endl;
	cout << "1   " << myPositions[0]->getPlayer() << "-----------" << myPositions[1]->getPlayer() << "-----------" << myPositions[2]->getPlayer() << endl;
	cout << "    " << "|           |           |" << endl;
	cout << "2   " << "|   " << myPositions[3]->getPlayer() << "-------" << myPositions[4]->getPlayer() << "-------" << myPositions[5]->getPlayer() << "   |" << endl;
	cout << "    " << "|   |       |       |   |" << endl;
	cout << "3   " << "|   |   " << myPositions[6]->getPlayer() << "---" << myPositions[7]->getPlayer() << "---" << myPositions[8]->getPlayer() << "   |   |" << endl;
	cout << "    " << "|   |   |       |   |   |" << endl;
	cout << "4   " << myPositions[9]->getPlayer() << "---" << myPositions[10]->getPlayer() << "---" << myPositions[11]->getPlayer() << "       " << myPositions[12]->getPlayer() << "---" << myPositions[13]->getPlayer() << "---" << myPositions[14]->getPlayer() << endl;
	cout << "    " << "|   |   |       |   |   |" << endl;
	cout << "5   " << "|   |   " << myPositions[15]->getPlayer() << "---" << myPositions[16]->getPlayer() << "---" << myPositions[17]->getPlayer() << "   |   |" << endl;
	cout << "    " << "|   |       |       |   |" << endl;
	cout << "6   " << "|   " << myPositions[18]->getPlayer() << "-------" << myPositions[19]->getPlayer() << "-------" << myPositions[20]->getPlayer() << "   |" << endl;
	cout << "    " << "|           |           |" << endl;
	cout << "7   " << myPositions[21]->getPlayer() << "-----------" << myPositions[22]->getPlayer() << "-----------" << myPositions[23]->getPlayer() << endl;
}
