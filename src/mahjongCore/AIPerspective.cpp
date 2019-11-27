#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AIPerspective.h"
#include "assert.h"

constexpr unsigned int ai_max_holding_count = 13;

AIPerspective::AIPerspective(Settings & settings) : BaseAIPerspective(settings) {
}

AIPerspective::~AIPerspective() {
}

Tile AIPerspective::whichToDiscard() {
	int i;
	int max = 0;
	int index_to_throw = 0;
	Tile holdings[ai_max_holding_count + 1];
	Tile tiles[ai_max_holding_count + 1];
	int tile_count = player->getHoldings(holdings, settings_.GetHandSize());
	holdings[tile_count] = player->getCurrentTileAtHand();
	for (i = 0; i < tile_count + 1; i++) {
		player->getHoldings(tiles, settings_.GetHandSize());
		tiles[i] = player->getCurrentTileAtHand();
		int score = evaluator->evaluate_array(TileArray(tiles, tile_count));
		if (score > max) {
			max = score;
			index_to_throw = i;
		}
	}

	return holdings[index_to_throw];
}

bool AIPerspective::isAbleToWin(Tile tile) const
{
	return player->isAbleToWin(tile);
}

void AIPerspective::pick(Tile tile, int distance) {
	if (distance == 0) {
		player->pick(tile);
		if (isAbleToWin(NO_TILE))
			currentActionRequest_.action_ = ACTION_WIN;
			UserLost();
		}
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
		if (isAbleToWin(tile))
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

