#ifndef SYSTEM_H_
#define SYSTEM_H_


#include "Perspective.h"
#include "Settings.h"

class UserPerspective;
class Wall;
class MahjongTable;
class UserView;

class Game {
public:

	Game(const Settings& settings);

	virtual ~Game();

	virtual UserView *getUserView();

	virtual void nextMove(PlayerActionRequest *request);

	void addPlayer(Player * player);

	void tick();

	Wall * getWall();

private:
	PlayerActionRequest * popActionRequest();
	Player * getPlayerOfDistance(int i);
	Wall * wall_;
	MahjongTable * table_;
	Player * aiPerspective_;
	Player * player_;
	UserPerspective * userPerspective_;
	const Settings & settings_;
};

#endif /* SYSTEM_H_ */
