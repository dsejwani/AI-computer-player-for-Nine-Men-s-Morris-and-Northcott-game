//#include "stdafx.h"
#include "pch.h"
#include <time.h>
#include "GameController.h"
#include "Board.h"
#include "Move.h"
#include "GameNode.h"
#include "EvalSettings.h"

using std::cout;
using std::endl;
using std::string;

// constructor for human vs. computer game
GameController::GameController(int timeLimit, char firstToAct, char compColor) {
	// set up the board.  and who goes first
	if (firstToAct == 'C' || firstToAct == 'c') {
		if (compColor == 'W' || compColor == 'w') {
			myBoard = new Board(WHITE);
			myComputerColor = WHITE;
			myHumanColor = BLACK;
		}
		else {
			myBoard = new Board(BLACK);
			myComputerColor = BLACK;
			myHumanColor = WHITE;
		}
	}
	else if (compColor == 'W' || compColor == 'w') {
		myBoard = new Board(BLACK);
		myComputerColor = WHITE;
		myHumanColor = BLACK;
	}
	else {
		myBoard = new Board(WHITE);
		myComputerColor = BLACK;
		myHumanColor = WHITE;
	}
	myState = ONE;
	myTimeLimit = timeLimit;
	myGameOver = false;
	myEvalSettings = new EvalSettings();
	myLastBoard = NULL;
	myEval = &Board::evaluate;
	// if the computer is first to act, make a move!
	if (firstToAct == 'C' || firstToAct == 'c') {
		computerMove(*myEvalSettings, myEval);
	}
}
// constructor for evaluate vs. evalTest game.  evalGoes determines if evaluate goes first
GameController::GameController(int timeLimit, int gamel, bool evalGoes) {
	myBoard = new Board(WHITE);
	myState = ONE;
	myTimeLimit = timeLimit;
	myGameOver = false;
	myLastBoard = NULL;
	myEvalSettings = new EvalSettings();
	while (!isOver()) {
		if (evalGoes) {
			Player me = myBoard->getTurn();
			computerMove(*myEvalSettings, &Board::evaluate);
			if (myBoard->hasWon(me)) {
				myGameOver = true;
				cout << "The evaluate function has won!" << endl;
			}
			if (myLastBoard != NULL)
				delete myLastBoard;
			myLastBoard = new Board(*myBoard);
			evalGoes = false;
		}
		else {
			Player me = myBoard->getTurn();
			computerMove(*myEvalSettings, &Board::evalTest);
			if (myBoard->hasWon(me)) {
				myGameOver = true;
				cout << "The evalTest function has won!" << endl;
			}
			evalGoes = true;
		}
		myBoard->print();
	}
}
// destructor
GameController::~GameController() {
	delete myBoard;
	delete myEvalSettings;
	if (myLastBoard != NULL)
		delete myLastBoard;
}
// function to perform a computer move on the board
std::string GameController::computerMove(EvalSettings& es, evalFunc ev) {
	bool ret = true;
	string y1;
	myEval = ev;
	cout << "Determining computer's move..." << endl;
	Move::ourMovesGenerated = 0;
	clock_t start, end;
	start = clock();
	GameNode *m = bestMove(start, es);
	end = clock();
	if (m == NULL) {
		if (myBoard->hasWon(BLACK))
		{
			cout << "Black has won!" << endl;
			ret = false;
		}
			
		else if (myBoard->hasWon(WHITE))
		{
			cout << "White has won!" << endl;
			ret = false;
		}
		// this next bit is because we didn't find a move.  I'm guessing it's because we're only a move or two away
		// from losing.  So get the list of moves and just toss out the first one.
		else {
			cout << "No best move found. You may be about to win!" << endl;
			Move **moveList = myBoard->getMoves();
			if (moveList[0] != NULL) {
				cout << "Computer move: " << moveList[0]->getMove() << endl;
				y1 = moveList[0]->getMove();
				myBoard->move(*moveList[0]);
				for (int i = 0; moveList[i] != NULL && i < Board::MAX_MOVES; i++)
					delete moveList[i];
			}
			else {
				cout << "Couldn't find any move!" << endl;
				ret = false;
			}
			delete[] moveList;
		}
	}
	else {
		cout << "      Best Move: ";
		y1 = m->move->getMove();
		//cout << m->move->getMove() << endl;
		cout << "          Score: " << m->score << endl;
		cout << "Moves Generated: " << Move::ourMovesGenerated << " in " << ((double)(end - start)) / (double)CLOCKS_PER_SEC << " seconds." << endl;
		cout << "   " << myBoard->getPlayerTurn() << "'s (computer) move: " << m->move->getMove() << endl;
		myBoard->move(*(m->move));
		delete m;
	}
	if (ret)
		return y1;
	return "-1";
}
// takes a string (the move command from the user).  Performs the move and has the computer move in response
std::string GameController::move(std::string& strMove) {
	bool ret = false;
	string y;
	myState = myBoard->move(strMove);
	if (myState != ILLEGAL_MOVE)
		ret = true;
	if (myBoard->hasWon(myHumanColor)) {
		cout << "You have won!" << endl;
		myGameOver = true;
	}
	// now have the computer move
	else if (ret) {
		myBoard->print();
		y = computerMove(*myEvalSettings, myEval);
		if (y=="-1")
			myGameOver = true;
		else if (myBoard->hasWon(myComputerColor)) {
			cout << "The computer has won!" << endl;
			myGameOver = true;
		}
		// keep track of what our last move was so we can avoid getting stuck in a loop with another player
		if (myLastBoard != NULL)
			delete myLastBoard;
		myLastBoard = new Board(*myBoard);
	}
	
	return y;
}
bool GameController::isOver() {
	return myGameOver;
}
// prints the status of the game.
void GameController::print() {
	myBoard->print();
	if (myBoard->hasWon(myHumanColor))
		cout << "You have won!" << endl;
	else if (myBoard->hasWon(myComputerColor))
		cout << "I won!" << endl;

	if (myBoard->getTurn() == myComputerColor)
		cout << "It is the computer's move." << endl;
	else {
		if (myBoard->getStage() == ONE) {
			cout << "You have " << myBoard->getUnplacedPieces(myHumanColor) << " unplaced pieces." << endl;
			cout << "Enter drop or drop and capture (ex: D1 or D1,B6): ";
		}
		else if (myBoard->getStage() == TWO) {
			cout << "Enter adjacent move or move and capture (ex: A1-A4 or A1-A4,G1): ";
		}
		else {
			cout << "Enter fly move or fly move and capture (ex: G1-A7 or G1-A7,D3): ";
		}
	}
}
// this is the wrapper function for the recursive alpha-beta bestmove function.
// this is an iterative deepening going 2 ply deeper if there's still time to search
GameNode *GameController::bestMove(clock_t start, EvalSettings& es) {
	clock_t now = clock();
	myStartTime = start;
	GameNode *best = NULL;
	myEvalSettings = &es;
	myHitTimeCutoff = false;
	for (int depth = 2; ((double)(now - myStartTime)) / (double)CLOCKS_PER_SEC < myTimeLimit; depth += 2) {
		GameNode *temp = NULL;
		cout << "Searching to depth: " << depth << endl;
		temp = bestMove(myBoard, depth, es.worst_score, es.best_score, true);
		now = clock();
		if (myHitTimeCutoff) {
			cout << "Time limit reached before finding best move at this depth." << endl << endl;
		}
		else if (temp != NULL && temp->move != NULL) {
			if (best != NULL)
				delete best;
			best = temp;
			cout << "Move " << best->move->getMove() << " found in " << ((double)(now - myStartTime)) / (double)CLOCKS_PER_SEC << " seconds." << endl;
		}
		else if (temp == NULL)
			break;
	}
	return best;
}
// the recursive bestmove function using alpha-beta!
// NOTE: we need to keep track of if this is the first call to make sure that we don't evaluate moves
//       that would stick us into an infinite move loop
GameNode *GameController::bestMove(Board *b, int depth, int mybest, int hisbest, bool firstCall) {
	if (depth == 0)
		return new GameNode((b->*myEval)(*myEvalSettings), NULL);
	clock_t now = clock();
	if (((double)(now - myStartTime)) / (double)CLOCKS_PER_SEC > myTimeLimit) {
		myHitTimeCutoff = true;
		return NULL;
	}

	Move **moveList = b->getMoves();
	int movesEvaluated = 0;
	int bestScore = mybest;
	Move *bestMove = NULL;
	while (moveList[movesEvaluated] != NULL && movesEvaluated < Board::MAX_MOVES) {
		Board *evalBoard = new Board(*b);
		evalBoard->move(*moveList[movesEvaluated]);
		if (firstCall && (myLastBoard != NULL) && evalBoard->isSameBoardState(*myLastBoard)) {  // don't eval this move
		}
		else {
			GameNode *attempt = GameController::bestMove(evalBoard, depth - 1, 0 - hisbest, 0 - bestScore, false);
			if (attempt != NULL && (0 - attempt->score) > bestScore) {
				bestScore = (0 - attempt->score);
				delete attempt;
				if (bestMove != NULL)
					delete bestMove;
				bestMove = new Move(*moveList[movesEvaluated]);
			}
			else if (attempt != NULL) {
				delete attempt;
			}
			if (bestScore > hisbest) {
				delete evalBoard;
				break;
			}
		}
		delete evalBoard;
		movesEvaluated++;
	}

	// free memory!
	movesEvaluated = 0;
	while ((moveList[movesEvaluated] != NULL) && (movesEvaluated < Board::MAX_MOVES)) {
		delete moveList[movesEvaluated];
		movesEvaluated++;
	}
	delete[] moveList;

	return new GameNode(bestScore, bestMove);
}