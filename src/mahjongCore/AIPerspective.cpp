#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AIPerspective.h"
#include "Hand.h"
#include "EvaluatorAdaptor.h"
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
	int tile_count = player->getHoldings(holdings, ai_max_holding_count);
	holdings[tile_count] = player->getCurrentTileAtHand();
	for (i = 0; i < tile_count + 1; i++) {
		player->getHoldings(tiles, ai_max_holding_count);
		tiles[i] = player->getCurrentTileAtHand();
		int score = evaluator->evaluate_array(TileArray(tiles, tile_count));
		if (score > max) {
			max = score;
			index_to_throw = i;
		}
	}

	return holdings[index_to_throw];
}
