#ifndef UI_PERSPECTIVE_H_
#define UI_PERSPECTIVE_H_

#include "TileArray.h"
#include "Perspective.h"
#include "UIEvent.h"

class MahjongTable;

class Hand;
class Game;

class UserView {
public:
	virtual ~UserView(){};
	virtual UIEvent * popEvent() = 0;
	virtual int getNumberOfPlayer() = 0;
	virtual Hand *getHand(int distance) = 0;
	virtual Tile getCurrentDiscardTile() = 0;
};

class UserPerspective: public Player, public UserView {
public:
	UserPerspective();
	virtual ~UserPerspective();

	virtual void deal(const Tile tiles[], int n, int distance);
	virtual void pick(Tile tile, int distance);
	virtual void pong(Tile tile, int distance);
	virtual int chow(Tile tile, Tile with, int distance);
	virtual void win(int score, int distance);
	virtual void discard(Tile tile, int distance);

	virtual void pushActionRequest(PlayerActionRequest *request);

	virtual UIEvent * popEvent();
	virtual int getNumberOfPlayer();
	virtual Hand *getHand(int distance);
	virtual Tile getCurrentDiscardTile();

	void setHand(int distance, Hand * hand);

private:
	void add_event(UIEvent * event);

	UIEventQueue eventQueue_;
	Tile last_tile;
	Hand * Hands[MAX_NUMBER_OF_PLAYER];
	UIEventFactory *eventFactory_;
	void _remove_players();
};

#endif /* UI_PERSPECTIVE_H_ */
