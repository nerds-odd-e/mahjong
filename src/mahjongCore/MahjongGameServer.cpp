#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mahjong_game.h"
#include "MahjongGameServer.h"
#include "GameJsonResponse.h"
#include "GameIDMap.h"

MahjongGameServer::MahjongGameServer(FpShutdownCallback shutdownCallback) :
		gameLevel_{}, settings_{gameLevel_}, shutdownCallback_(shutdownCallback), lastGameID_(0) {
	gamePool_ = new GameIDMap();
}

MahjongGameServer::~MahjongGameServer() {
	delete gamePool_;
}

GameID MahjongGameServer::startNewGame() {
	Game * game = new Game;
	lastGameID_ = gamePool_->addGameAndGetID(game);
	return lastGameID_;
}

void MahjongGameServer::killGame(GameID gameID) {
	gamePool_->removeAndDeleteGame(gameID);
}

GameJsonResponse * MahjongGameServer::executeGameCommand(MahjongCommand* mjCommand)
{
	GameJsonResponse *respond = new GameJsonResponse();
	mjCommand->execute(respond);
	return respond;
}

void MahjongGameServer::shutdown() {
	if (shutdownCallback_ != NULL)
		shutdownCallback_();
}

GameID MahjongGameServer::getLastGameID() {
	return lastGameID_;
}

Game * MahjongGameServer::getGameByID(GameID gameID) {
	return gamePool_->getGameByID(gameID);
}

inline unsigned int MahjongGameServer::getLevel() const
{
    return gameLevel_.GetLevel();
}

inline void MahjongGameServer::setLevel(unsigned int level)
{
    return gameLevel_.SetLevel(level);
}
