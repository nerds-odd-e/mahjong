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

	Game();

	virtual ~Game();

	void CreateAIPerspective();

	virtual UserView *getUserView();

	virtual void nextMove(PlayerActionRequest *request);

	void addPlayer(Player * player);

	void tick();

	Wall * getWall();

    unsigned int GetLevel();
    void IncrementLevel();
	void setLevel(unsigned int level);
	int GetSublevel();

private:
	PlayerActionRequest * popActionRequest();
	Player * getPlayerOfDistance(int i);
	Wall * wall_;
	MahjongTable * table_;
	Player * aiPerspective_;
	Player * player_;
	UserPerspective * userPerspective_;
	Settings settings_;
};

#endif /* SYSTEM_H_ */
