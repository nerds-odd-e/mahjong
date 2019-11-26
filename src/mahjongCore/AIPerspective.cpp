#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AIPerspective.h"
#include "Hand.h"
#include "EvaluatorAdaptor.h"
#include "assert.h"
#include "configuration.h"

AIPerspective::AIPerspective() {
	currentActionRequest_.action_ = ACTION_RESTART;
	player = NULL;
	evaluator = createEvaluatorAdaptor();
}
AIPerspective::~AIPerspective() {
	if (player)
		delete player;
	delete evaluator;
}

void AIPerspective::deal(const Tile tiles[], int n, int distance) {
	if (distance == 0) {
		Hand * player_data = createHand();
		player_data->deal(tiles, n);
		player = player_data;
		currentActionRequest_.action_ = ACTION_PICK;
	}
}

Tile AIPerspective::whichToDiscard() {
	int i;
	int max = 0;
	int index_to_throw = 0;
	Tile holdings[MAX_HOLDING_COUNT + 1];
	Tile tiles[MAX_HOLDING_COUNT + 1];
	int tile_count = player->getHoldings(holdings, Configuration::getInstance().GetMaxHoldingCount());
	holdings[tile_count] = player->getCurrentTileAtHand();
	for (i = 0; i < tile_count + 1; i++) {
		player->getHoldings(tiles, Configuration::getInstance().GetMaxHoldingCount());
		tiles[i] = player->getCurrentTileAtHand();
		int score = evaluator->evaluate_array(TileArray(tiles, tile_count));
		if (score > max) {
			max = score;
			index_to_throw = i;
		}
	}

	return holdings[index_to_throw];
}
void AIPerspective::pick(Tile tile, int distance) {
	if (distance == 0) {
		player->pick(tile);
		if (player->isAbleToWin(NO_TILE))
			currentActionRequest_.action_ = ACTION_WIN;
		else {
			currentActionRequest_.action_ = ACTION_DISCARD;
			currentActionRequest_.tile_ = whichToDiscard();
		}
	}
}

void AIPerspective::pong(Tile tile, int distance) {
}

int AIPerspective::chow(Tile tile, Tile with, int distance) {
	return 0;
}

void AIPerspective::win(int score, int distance) {
	currentActionRequest_.action_ = ACTION_RESTART;
	delete player;
	player = NULL;
}

void AIPerspective::pushActionRequest(PlayerActionRequest *actionRequest) {

}

void AIPerspective::discard(Tile tile, int distance) {
	if (distance == 0)
		player->discard(tile);
	else {
		if (player->isAbleToWin(tile))
			currentActionRequest_.action_ = ACTION_WIN;
		else
			currentActionRequest_.action_ = ACTION_PICK;
	}
}

void AIPerspective::setEvaluator(EvaluatorAdaptor * evaluator){
	if (this->evaluator != NULL)
		delete this->evaluator;
	this->evaluator = evaluator;
}

