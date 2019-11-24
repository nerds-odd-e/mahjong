#include "MahjongCommand.h"
#include "mahjong_game.h"
#include "MahjongGameServer.h"
#include "GameJsonResponse.h"
#include "Wall.h"

void MJCommandGetCurrentGameStatus::execute(GameJsonResponse *respond) {
	respond->currentGameStatus(game_->getUserView());
}

void MJCommandPopAction::execute(GameJsonResponse *respond) {
	respond->popAction(game_->getUserView());
}

void MJCommandNewPlayerJoin::execute(GameJsonResponse *respond) {
	int gameID = server_->startNewGame();
	respond->newGame(gameID);
}

void MJCommandQuitGame::execute(GameJsonResponse *respond) {
	server_->killGame(gameID_);
	respond->bye();
}

void MJCommandShutdownServer::execute(GameJsonResponse *respond) {
	server_->shutdown();
	respond->shutdown();
}

void MJCommandDoesNotExist::execute(GameJsonResponse *respond) {
	respond->gameDoesNotExist();
}

void MJCommandAction::execute(GameJsonResponse *respond) {
	PlayerActionRequest request(action_, tile_);
	game_->nextMove(&request);
	respond->popAction(game_->getUserView());
}

void MJTestSetNextPick::execute(GameJsonResponse *respond) {
	game_->getWall()->changeFirstTileTo(tile_);
}
