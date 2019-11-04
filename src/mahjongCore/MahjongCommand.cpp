#include "MahjongCommand.h"
#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLMahjongGameRespond.h"

void MJCommandNewPlayerJoin::execute(MahjongGameRespond *respond) {
	int gameID = server_->startNewGame();
	respond->newGame(gameID);
}

void MJCommandQuitGame::execute(MahjongGameRespond *respond) {
	server_->killGame(gameID_);
	respond->bye();
}

void MJCommandShutdownServer::execute(MahjongGameRespond *respond) {
	server_->shutdown();
	respond->shutdown();
}

void MJCommandDoesNotExist::execute(MahjongGameRespond *respond) {
	respond->gameDoesNotExist();
}

void MJCommandAction::execute(MahjongGameRespond *respond) {
	PlayerActionRequest request(action_, tile_);
	game_->nextMove(&request);
	respond->updateUIEvent(game_->getUserView());
}
