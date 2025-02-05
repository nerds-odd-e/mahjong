#ifndef MOCKS_H_
#define MOCKS_H_

class Player;
class EvaluatorAdaptor;
EvaluatorAdaptor * createMockEvaluator(void);

#include "tile.h"
#include "PlayerActionRequest.h"
class MockPlayerActionRequest : public PlayerActionRequest {
public:
	MockPlayerActionRequest() :PlayerActionRequest(NO_ACTION, 0){}
	virtual ~MockPlayerActionRequest(){}

	virtual bool hasAction() {
		return mock().actualCall("hasAction").onObject(this).returnValue().getIntValue();
	}

	virtual void doPlayerAction(GameState *state) {
		mock().actualCall("doPlayerAction").onObject(this).withParameter("state", state);
	}

};

#include "Perspective.h"
#include "TileArray.h"
class MockPlayer: public Player {
public:
	MockPlayer(Settings & settings) : Player(settings) {}

	virtual void destroy(Player *self) {
		free(self);
	}

	virtual void deal(const Tile tiles[], int buffer_size, int distance) {
		UNUSED(buffer_size);
		mock().actualCall("deal").onObject(this).withParameter("distance",
				distance).withParameter("tiles", tiles);
	}

	virtual void pick(Tile tile, int distance) {
		mock().actualCall("pick").onObject(this).withParameter("tile",
				(const char *) tile).withParameter("distance", distance);
	}

	virtual void win(int score, int distance) {
		mock().actualCall("win").onObject(this).withParameter("score", score).withParameter(
				"distance", distance);
	}

	virtual void discard(Tile tile, int distance) {
		mock().actualCall("discard_tile").onObject(this).withParameter("tile",
				(const char *) tile).withParameter("distance", distance);
	}
	virtual void pong(Tile tile, int distance) {
		UNUSED(tile), UNUSED(distance);
	}

	virtual int chow(Tile tile, Tile with, int distance) {
		UNUSED(tile), UNUSED(with), UNUSED(distance);
		return 0;
	}

	virtual void pushActionRequest(PlayerActionRequest *actionRequest) {
		UNUSED(actionRequest);
	}

	virtual PlayerActionRequest * takeActionRequest1(){
		mock().actualCall("takeActionRequest").onObject(this);
		return (PlayerActionRequest *)mock().returnValue().getObjectPointer();
	}
};

#include "GameJsonResponse.h"
class MockHTMLMahjongGameResponse: public GameJsonResponse {
public:
	virtual ~MockHTMLMahjongGameResponse(){}
	void newGame(int gameID) {
		mock().actualCall("newGame").onObject(this).withParameter("gameID",
				gameID);
	}

	void bye() {
		mock().actualCall("bye").onObject(this);
	}

	void shutdown() {
		mock().actualCall("shutdown").onObject(this);
	}

	void popAction(UserView *view) {
		mock().actualCall("popAction").onObject(this).withParameter("view",
				view);
	}

	void gameDoesNotExist() {
		mock().actualCall("gameDoesNotExist").onObject(this);
	}

};

#include "MahjongGameServer.h"

class MockHTMLMahjongGameServer: public MahjongGameServer {
public:
	GameID startNewGame() {
		return mock().actualCall("startNewGame").onObject(this).returnValue().getIntValue();
	}

	void killGame(GameID gameID) {
		mock().actualCall("killGame").onObject(this).withParameter("gameID",
				gameID);
	}

	void shutdown() {
		mock().actualCall("shutdown").onObject(this);
	}

	Game * getGameByID(GameID gameID) {
		return (Game*) mock().actualCall("getGameByID").onObject(this).withParameter(
				"gameID", gameID).returnValue().getObjectPointer();
	}

};

#include "game.h"

class MockGame: public Game {
public:
    MockGame(): Game() {};

	virtual void nextMove(PlayerActionRequest *request) {
		UNUSED(request);
		mock().actualCall("nextMove").onObject(this).withParameter("request",
				request);
	}

	virtual void setAction(PlayerActionRequest * actionRequest) {
		UNUSED(actionRequest);
		mock().actualCall("set_action").onObject(this);
	}

	virtual UserView *getUserView() {
		return (UserView *) mock().actualCall("getUserView").onObject(this).returnValue().getPointerValue();
	}
};

#include "UserPerspective.h"
class MockUserView: public UserView {
public:
	UIEvent * popEvent() {
		return (UIEvent *) mock().actualCall("popEvent").onObject(this).returnValue().getObjectPointer();
	}

	const char * get_tiles_array_string(char buffer[], int buffer_size) {
		UNUSED(buffer), UNUSED(buffer_size);
		return "<tile list>";
	}

	int getNumberOfPlayer() {
		return mock().actualCall("getNumberOfPlayer").onObject(this).returnValue().getIntValue();
	}

	Hand *getHand(int distance) {
		UNUSED(distance);
		return (Hand *) mock().actualCall("getHand").onObject(this).returnValue().getObjectPointer();
	}

	Tile getCurrentDiscardTile() {
		return (Tile) mock().actualCall("getCurrentDiscardTile").onObject(this).returnValue().getIntValue();
	}

    void setHand(int distance, Hand* hand)
    {

    }

};

#endif /* MOCKS_H_ */
