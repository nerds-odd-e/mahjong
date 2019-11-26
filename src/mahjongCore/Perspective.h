#ifndef PLAYER_H_
#define PLAYER_H_

#include "tile.h"
#include "PlayerActionRequest.h"
struct PlayerGameData
{
	int number_of_wins {0};
};

class Player {
public:
	Player() : currentActionRequest_(NO_ACTION, NO_TILE){}
	virtual ~Player(){}

	virtual void deal(const Tile tiles[], int n, int distance)=0;
	virtual void pick(Tile tile, int distance)=0;
	virtual void pong(Tile tile, int distance)=0;
	virtual int chow(Tile tile, Tile with, int distance)=0;
	virtual void win(int score, int distance)=0;
	virtual void discard(Tile tile, int distance)=0;

	virtual PlayerActionRequest takeActionRequest(){
		PlayerActionRequest saved = currentActionRequest_;
		currentActionRequest_.action_ = NO_ACTION;
		return saved;
	}
	virtual PlayerActionRequest* takeActionRequest1(){
		return &currentActionRequest_;
	}
	virtual void pushActionRequest(PlayerActionRequest *actionRequest)=0;

	int getWins() const
	{
		return game_data_.number_of_wins;
	}

protected:
	PlayerActionRequest currentActionRequest_;

private:
	PlayerGameData game_data_;
};

#endif /* PLAYER_H_ */
