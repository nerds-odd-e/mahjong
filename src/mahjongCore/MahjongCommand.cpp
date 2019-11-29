#include "MahjongCommand.h"
#include "mahjong_game.h"
#include "MahjongGameServer.h"
#include "GameJsonResponse.h"
#include "Wall.h"
#include "Hand.h"

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

void MJCommandSetLevel::execute(GameJsonResponse *respond) {
    server_->setLevel(level_);
	server_->getGameByID(server_->getLastGameID())->CreateAIPerspective();
}

void MJCommandGetLevel::execute(GameJsonResponse *respond)
{
    std::string response_json =
        "{\"current_level\":" + std::to_string(server_->GetLevel()) + "\n}";

    respond->setContent(response_json);
}

void MJCommandNumberOfWins::execute(GameJsonResponse *respond) {
	std::string response_json =
		"{\"number_of_wins\":" + std::to_string(server_->GetSublevel()) + "\n}";

	respond->setContent(response_json);
}

void MJCommandSetHand::execute(GameJsonResponse *respond) {
    Tile tiles[tiles_.size()];

    int index = 0;
    for(const auto tile : tiles_)
    {
        tiles[index++] = tile;
    }

    Hand* custom_hand = new Hand();
    custom_hand->deal(tiles, tiles_.size());

	game_->getUserView()->setHand(0, custom_hand);
}