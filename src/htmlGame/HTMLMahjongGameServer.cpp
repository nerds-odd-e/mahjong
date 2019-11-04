#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

#include "mahjong_game.h"
#include "HTMLMahjongGameServer.h"
#include "MahjongCommand.h"
#include "HTMLCommandParser.h"
#include "HTMLMahjongGameResponse.h"
#include "MahjongGameFactory.h"
#include "GameIDMap.h"

MahjongGameServer::MahjongGameServer(MahjongGameFactory * factory,
		FpShutdownCallback shutdownCallback, HTMLCommandParser *parser) :
		factory_(factory), shutdownCallback_(shutdownCallback), lastGameID_(0) {
	gamePool_ = new GameIDMap();
	commandParser_ = parser;
	if (commandParser_ == NULL)
		commandParser_ = new HTMLCommandParser(this);
}

MahjongGameServer::~MahjongGameServer() {
	delete gamePool_;
	delete commandParser_;
}

GameID MahjongGameServer::startNewGame() {
	Game * game = new Game;
	lastGameID_ = gamePool_->addGameAndGetID(game);
	return lastGameID_;
}

void MahjongGameServer::killGame(GameID gameID) {
	gamePool_->removeAndDeleteGame(gameID);
}

MahjongGameResponse * MahjongGameServer::executeGameCommand(const char * command,
		const char *parameters) {
	MahjongGameResponse *respond = factory_->createMahjongGameRespond();
	std::auto_ptr<MahjongCommand> mjCommand (commandParser_->parse(command, parameters));
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
