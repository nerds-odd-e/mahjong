#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mahjong_game.h"
#include "MahjongGameServer.h"
#include "GameJsonResponse.h"
#include "GameIDMap.h"

MahjongGameServer::MahjongGameServer(FpShutdownCallback shutdownCallback) :
		settings_{}, shutdownCallback_(shutdownCallback), lastGameID_(0) {
	gamePool_ = new GameIDMap();
}

MahjongGameServer::~MahjongGameServer() {
	delete gamePool_;
}

GameID MahjongGameServer::startNewGame() {
	Game * game = new Game(settings_);
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

unsigned int MahjongGameServer::GetLevel()
{
    return settings_.GetGameLevel().GetLevel();
}

void MahjongGameServer::IncrementLevel()
{
    settings_.GetGameLevel().IncrementLevel();
}

void MahjongGameServer::GetProgress()
{
	settings_.GetGameLevel().GetSubLevel();
}