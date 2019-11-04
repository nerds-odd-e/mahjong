#ifndef HTML_GAME_H_
#define HTML_GAME_H_

#include "Perspective.h"
#include "GameID.h"
class Wall;
class Game;
class GameIDMap;
class HTMLCommandParser;
class MahjongGameResponse;
class MahjongGameFactory;

typedef void (*FpShutdownCallback)(void);

class MahjongGameServer {
public:
	MahjongGameServer(MahjongGameFactory* factory = NULL, FpShutdownCallback shutdownCallback = NULL,
			HTMLCommandParser *parser = NULL);

	virtual ~MahjongGameServer();

	MahjongGameResponse * executeGameCommand(const char * command, const char *parameters);

	virtual GameID startNewGame();

	virtual void killGame(GameID gameID);

	virtual void shutdown();

	virtual Game * getGameByID(GameID);

	GameID getLastGameID();

private:
	GameIDMap *gamePool_;
	HTMLCommandParser *commandParser_;
	FpShutdownCallback shutdownCallback_;
	GameID lastGameID_;
	MahjongGameFactory * factory_;
};

#endif /* HTML_GAME_H_ */
