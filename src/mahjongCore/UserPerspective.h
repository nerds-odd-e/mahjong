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
    virtual void setHand(int distance, Hand * hand) = 0;
};

class UserPerspective: public Player, public UserView {
public:
	UserPerspective(Settings & settings);
	virtual ~UserPerspective();

	virtual void deal(const Tile tiles[], int n, int distance) override;
	virtual void pick(Tile tile, int distance) override;
	virtual void pong(Tile tile, int distance) override;
	virtual int chow(Tile tile, Tile with, int distance) override;
	virtual void win(int score, int distance) override;
	virtual void discard(Tile tile, int distance) override;

	virtual void pushActionRequest(PlayerActionRequest *request) override;

	virtual UIEvent * popEvent() override;
	virtual int getNumberOfPlayer() override;
	virtual Hand *getHand(int distance) override;
	virtual Tile getCurrentDiscardTile() override;

	void setHand(int distance, Hand * hand) override;



private:
	void add_event(UIEvent * event);

	UIEventQueue eventQueue_;
	Tile last_tile;
	Hand * Hands[MAX_NUMBER_OF_PLAYER];
	UIEventFactory *eventFactory_;
	void _remove_players();
};

#endif /* UI_PERSPECTIVE_H_ */
