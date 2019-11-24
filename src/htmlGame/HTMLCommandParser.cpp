#include <string.h>
#include <cstdio>
#include <stdlib.h>
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include "mahjong_game.h"


HTMLCommandParser::HTMLCommandParser(MahjongGameServer * server) :
		server_(server) {
}

HTMLCommandParser::~HTMLCommandParser() {
}

MahjongCommand * HTMLCommandParser::parse(const char * command,
		const char *parameters) {
	const char * cmd = strchr(command, '/');

	return parseWithExtractedParameters(cmd, parameters);
}

MahjongCommand * HTMLCommandParser::parseWithExtractedParameters(
		const char * cmd, const char *parameters) {

	if (strcmp(cmd, "/join") == 0)
		return new MJCommandNewPlayerJoin(server_);

	if (strcmp(cmd, "/shutdown") == 0)
		return new MJCommandShutdownServer(server_);

	GameID gameID = 0;
	char gameCmd[100];
	std::sscanf(cmd, "/%d/%s", &gameID, gameCmd);
	Tile tile = atoi(parameters);

	return parseWithExtractedParametersForGame(gameID, gameCmd, tile);
}

MahjongCommand * HTMLCommandParser::parseWithExtractedParametersForGame(
		GameID gameID, const char * cmd, Tile tile) {
	if (strcmp(cmd, "bye") == 0)
		return new MJCommandQuitGame(server_, gameID);

	Game * game = server_->getGameByID(gameID);

	if (game != NULL) {
		if (strcmp(cmd, "start") == 0)
			return new MJCommandStartNewGame(game);

		if (strcmp(cmd, "current") == 0)
			return new MJCommandGetCurrentGameStatus(game);

		if (strcmp(cmd, "next_event") == 0)
			return new MJCommandPopAction(game);

		if (strcmp(cmd, "pick") == 0)
			return new MJCommandPick(game);

		if (strcmp(cmd, "throw") == 0)
			return new MJCommandDiscard(game, tile);

		if (strcmp(cmd, "chow") == 0)
			return new MJCommandChow(game, tile);

		if (strcmp(cmd, "pong") == 0)
			return new MJCommandPong(game);

		if (strcmp(cmd, "kong") == 0)
			return new MJCommandKong(game, tile);

		if (strcmp(cmd, "win") == 0)
			return new MJCommandWin(game);
	}
	return new MJCommandDoesNotExist;
}
