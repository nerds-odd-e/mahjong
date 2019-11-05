#include "MahjongCommand.h"
#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLMahjongGameResponse.h"

void MJCommandGetCurrentGameStatus::execute(MahjongGameResponse *respond) {
	respond->currentGameStatus(game_->getUserView());
}

void MJCommandPopAction::execute(MahjongGameResponse *respond) {
	respond->popAction(game_->getUserView());
}

void MJCommandNewPlayerJoin::execute(MahjongGameResponse *respond) {
	int gameID = server_->startNewGame();
	respond->newGame(gameID);
}

void MJCommandQuitGame::execute(MahjongGameResponse *respond) {
	server_->killGame(gameID_);
	respond->bye();
}

void MJCommandShutdownServer::execute(MahjongGameResponse *respond) {
	server_->shutdown();
	respond->shutdown();
}

void MJCommandDoesNotExist::execute(MahjongGameResponse *respond) {
	respond->gameDoesNotExist();
}

void MJCommandAction::execute(MahjongGameResponse *respond) {
	PlayerActionRequest request(action_, tile_);
	game_->nextMove(&request);
	respond->popAction(game_->getUserView());
}
