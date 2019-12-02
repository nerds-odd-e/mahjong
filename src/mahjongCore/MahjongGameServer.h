#ifndef HTML_GAME_H_
#define HTML_GAME_H_

#include <memory>
#include "Perspective.h"
#include "GameID.h"
#include "GameLevel.h"
#include "MahjongCommand.h"
#include "Settings.h"

class Wall;
class Game;
class GameIDMap;
class GameJsonResponse;

typedef void (*FpShutdownCallback)(void);

class MahjongGameServer {
public:
	MahjongGameServer(FpShutdownCallback shutdownCallback = NULL);

	virtual ~MahjongGameServer();

	GameJsonResponse * executeGameCommand(MahjongCommand* mjCommand);
	virtual GameID startNewGame();

	virtual void killGame(GameID gameID);

	virtual void shutdown();

	virtual Game * getGameByID(GameID);

	GameID getLastGameID();

private:
    Settings settings_;
	GameIDMap *gamePool_;
	FpShutdownCallback shutdownCallback_;
	GameID lastGameID_;
};

#endif /* HTML_GAME_H_ */
