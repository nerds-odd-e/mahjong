#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BaseAIPerspective.h"
#include "Hand.h"
#include "EvaluatorAdaptor.h"
#include "assert.h"

constexpr unsigned int ai_max_holding_count = 13;

BaseAIPerspective::BaseAIPerspective(Settings & settings) : Player(settings) {
	currentActionRequest_.action_ = ACTION_RESTART;
	player = NULL;
	evaluator = createEvaluatorAdaptor();
}
BaseAIPerspective::~BaseAIPerspective() {
	if (player)
		delete player;
	delete evaluator;
}

void BaseAIPerspective::deal(const Tile tiles[], int n, int distance) {
	if (distance == 0) {
		Hand * player_data = createHand();
		player_data->deal(tiles, n);
		player = player_data;
		currentActionRequest_.action_ = ACTION_PICK;
	}
}

void BaseAIPerspective::pick(Tile tile, int distance) {
	if (distance == 0) {
		player->pick(tile);
		if (isAbleToWin(NO_TILE))
			currentActionRequest_.action_ = ACTION_WIN;
		else {
			currentActionRequest_.action_ = ACTION_DISCARD;
			currentActionRequest_.tile_ = whichToDiscard();
		}
	}
}

void BaseAIPerspective::pong(Tile tile, int distance) {
}

int BaseAIPerspective::chow(Tile tile, Tile with, int distance) {
	return 0;
}

void BaseAIPerspective::win(int score, int distance) {
	currentActionRequest_.action_ = ACTION_RESTART;
	delete player;
	player = NULL;
}

void BaseAIPerspective::pushActionRequest(PlayerActionRequest *actionRequest) {

}

void BaseAIPerspective::discard(Tile tile, int distance) {
	if (distance == 0)
		player->discard(tile);
	else {
		if (isAbleToWin(tile))
			currentActionRequest_.action_ = ACTION_WIN;
		else
			currentActionRequest_.action_ = ACTION_PICK;
	}
}

void BaseAIPerspective::setEvaluator(EvaluatorAdaptor * evaluator){
	if (this->evaluator != NULL)
		delete this->evaluator;
	this->evaluator = evaluator;
}


bool BaseAIPerspective::isAbleToWin(Tile tile) const
{
	return player->isAbleToWin(tile);
}

