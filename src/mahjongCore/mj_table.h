#ifndef GAME_FLOW_H_
#define GAME_FLOW_H_

#include "tile.h"
#include "GameState.h"
#include "GameLevel.h"

class Wall;
class Hand;
class Player;
class PlayerActionRequest;
class Settings;

class MahjongTable{
public:
	MahjongTable(Wall * wall, Settings& settings);
	~MahjongTable();

	void nextMove();

	void addPlayer(Player * player);
	int getWinForCurrentPlayer() const;
	void restartGame();
private:
	Player * getPlayerOfDistance( int i);
	int getPlayerCount();
	void pick( Tile tile);
	void changeHost();
	void changeCurrentPlayer( int distance);
	void win( int score);
	void deal( Tile tiles[], int n);
	void discard_tile( Tile tile);
	void pong();
	int chow( Tile with);
	void restartGameWhenAllPlayersAreReady();
	PlayerActionRequest popActionRequest();
	void discard(Tile& action_tile);
	void doWin();
	void doPick();
	void doPong();
	void doChow(Tile action_tile);
	Wall *wall_;
	Player * players[MAX_NUMBER_OF_PLAYER];
	int player_count_;
	int current_player;
	int host;
	Tile last_tile;
	int restartCount_;
    int handSize_;
	GameState * currentState_;
	GameStateEndOfGame endOfGameState_;
	GameStatePicked pickedState_;
	GameStatePicking pickingState_;
	Settings& settings_;

	friend class GameStateEndOfGame;
	friend class GameStatePicked;
	friend class GameStatePicking;
};

#endif /* GAME_FLOW_H_ */
