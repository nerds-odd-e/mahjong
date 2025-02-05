#ifndef MAHJONGCOMMAND_H_
#define MAHJONGCOMMAND_H_

#include "GameID.h"
#include "tile.h"
#include "PlayerActionRequest.h"
#include <vector>
#include <string>

class MahjongGameServer;
class Game;
class GameJsonResponse;

class MahjongCommand {
public:
	virtual ~MahjongCommand() {
	}
	virtual void execute(GameJsonResponse *respond) =0;
};

class MJCommandGetCurrentGameStatus: public MahjongCommand {
public:
	MJCommandGetCurrentGameStatus(Game *game) :
			game_(game) {
	}
	void execute(GameJsonResponse *respond);
private:
	Game* game_;
};

class MJCommandPopAction: public MahjongCommand {
public:
	MJCommandPopAction(Game *game) :
			game_(game) {
	}
	void execute(GameJsonResponse *respond);
private:
	Game* game_;
};

class MJCommandNewPlayerJoin: public MahjongCommand {
public:
	MJCommandNewPlayerJoin(MahjongGameServer* server) :
			server_(server) {
	}
	void execute(GameJsonResponse *respond);
private:
	MahjongGameServer* server_;
};

class MJCommandQuitGame: public MahjongCommand {
public:
	MJCommandQuitGame(MahjongGameServer* server, GameID gameID) :
			server_(server), gameID_(gameID) {
	}
	void execute(GameJsonResponse *respond);
private:
	MahjongGameServer* server_;
	GameID gameID_;
};

class MJCommandShutdownServer: public MahjongCommand {
public:
	MJCommandShutdownServer(MahjongGameServer* server):
		server_(server) {}
	void execute(GameJsonResponse *respond);
private:
	MahjongGameServer* server_;
};

class MJCommandDoesNotExist: public MahjongCommand {
public:
	void execute(GameJsonResponse *respond);
};

class MJCommandAction: public MahjongCommand {
public:
	MJCommandAction(Game *game, action_t action, Tile tile) :
			game_(game), action_(action), tile_(tile) {
	}
	virtual void execute(GameJsonResponse *respond);
protected:
	Game *game_;
	action_t action_;
	Tile tile_;
};

class MJCommandStartNewGame: public MJCommandAction {
public:
	MJCommandStartNewGame(Game *game) :
			MJCommandAction(game, ACTION_RESTART, NO_TILE) {
	}
};

class MJCommandPick: public MJCommandAction {
public:
	MJCommandPick(Game *game) :
			MJCommandAction(game, ACTION_PICK, NO_TILE) {
	}
};

class MJCommandDiscard: public MJCommandAction {
public:
	MJCommandDiscard(Game *game, Tile tile) :
			MJCommandAction(game, ACTION_DISCARD, tile) {
	}
};

class MJCommandChow: public MJCommandAction {
public:
	MJCommandChow(Game *game, Tile tile) :
			MJCommandAction(game, ACTION_CHOW, tile) {
	}
};

class MJCommandPong: public MJCommandAction {
public:
	MJCommandPong(Game *game) :
			MJCommandAction(game, ACTION_PONG, NO_TILE) {
	}
};

class MJCommandKong: public MJCommandAction {
public:
	MJCommandKong(Game *game, Tile tile) :
			MJCommandAction(game, ACTION_KONG, tile) {
	}
};

class MJCommandWin: public MJCommandAction {
public:
	MJCommandWin(Game *game) :
			MJCommandAction(game, ACTION_WIN, NO_TILE) {
	}
};

class MJTestSetNextPick: public MahjongCommand {
public:
	MJTestSetNextPick(Game *game, Tile tile) :
			game_(game), tile_(tile) {
	}
	void execute(GameJsonResponse *respond);
private:
	Game* game_;
	Tile tile_;
};

class MJCommandSetLevel: public MahjongCommand {
public:
	MJCommandSetLevel(MahjongGameServer* server, Game *game, int level) :
		server_(server), game_(game), level_(level) {
	}
	void execute(GameJsonResponse *respond);
private:
	MahjongGameServer* server_;
	Game* game_;
	int level_;
};

class MJCommandGetLevel: public MahjongCommand {
public:
	MJCommandGetLevel(Game* game) :
		game_{game} {
		}
	void execute(GameJsonResponse *respond);

private:
    Game* game_;
};

class MJCommandStartImmediateWinGame:public MJCommandStartNewGame
{
	public:
	MJCommandStartImmediateWinGame(Game *game) : MJCommandStartNewGame(game)
	{

	}

	void execute(GameJsonResponse *respond)
	{
		MJCommandStartNewGame::execute(respond);
	}
};

class MJCommandSetHand: public MahjongCommand {
public:
	MJCommandSetHand(Game *game, const std::vector<int>& tiles) : game_{game}, tiles_{tiles}{
	}
	void execute(GameJsonResponse *respond);
private:
	Game* game_;
    std::vector<int> tiles_;
};

#endif /* MAHJONGCOMMAND_H_ */
