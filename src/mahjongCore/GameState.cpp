#include "GameState.h"
#include "mj_table.h"

GameState::GameState(MahjongTable * table) : table_(table) {
}

GameState::~GameState() {
}

void GameStateEndOfGame::restart() {
	getTable()->restartGameWhenAllPlayersAreReady();
}

void GameStatePicked::discard(Tile& action_tile) {
	getTable()->discard(action_tile);
}

void GameStatePicked::doWin() {
	getTable()->doWin();
}

void GameStatePicking::doPick() {
	getTable()->doPick();
}

void GameStatePicking::doWin() {
	getTable()->doWin();
}

void GameStatePicking::doPong() {
	getTable()->doPong();
}
void GameStatePicking::doChow(Tile& action_tile) {
	getTable()->doChow(action_tile);
}
