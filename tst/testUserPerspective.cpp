#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "UserPerspective.h"
#include "HTMLUIEvent.h"
#include "Hand.h"
#include "mocks.h"

class DummyUIEvent: public UIEvent {
public:
	virtual ~DummyUIEvent() {
	}
	virtual std::string toString() {
		return "";
	}
};

const Tile WINNING_TILE = 10;
const Tile ANY_TILE = 8;
Tile defaultTilesPongTheWinningTileAndChowWinningTilePlusOne[] = { WINNING_TILE, WINNING_TILE, WINNING_TILE+2, WINNING_TILE+2 };

class HandBuilder {
public:
	HandBuilder(): numberOfTiles_(0){}
	Hand * build() {
		return createHand(tiles_, numberOfTiles_);
	}

	HandBuilder& withAPairOf(Tile tile) {
		tiles_[numberOfTiles_++] = tile;
		tiles_[numberOfTiles_++] = tile;
		return *this;
	}

	HandBuilder& withPongOf(Tile tile) {
		tiles_[numberOfTiles_++] = tile;
		tiles_[numberOfTiles_++] = tile;
		tiles_[numberOfTiles_++] = tile;
		return *this;
	}

private:
	Hand * createHand(Tile * tiles, int count) {
		Hand * hand = new Hand();
		hand->deal(tiles, count);
		return hand;
	}

private:
	Tile tiles_[MAX_HOLDING_COUNT];
	int numberOfTiles_;
};

class HandDataMother {
public:
	Hand *createAllIrrelevantHand() {
		Tile tiles[] = { 1, 4, 7, 11 };
		return createHand(tiles, 4);
	}

	Hand * createHandWinWithTheWinningTile() {
		Tile tiles[] = {WINNING_TILE};
		return createHand(tiles, 1);
	}

	Hand *createHandPongTheWinningTile() {
		Tile tiles[] = {WINNING_TILE, WINNING_TILE, WINNING_TILE + 3, WINNING_TILE + 6};
		return createHand(tiles, 4);
	}

	Hand * createHandChowTheWinningTile() {
		Tile tiles[] = {WINNING_TILE+1, WINNING_TILE+2, WINNING_TILE + 3, WINNING_TILE + 6};
		return createHand(tiles, 4);
	}

	Hand * createHandPongAndWinTheWinningTile() {
		Tile tiles[] = {WINNING_TILE, WINNING_TILE, WINNING_TILE + 2, WINNING_TILE + 2};
		return createHand(tiles, 4);
	}

private:
	Hand * createHand(Tile * tiles, int count) {
		Hand * hand = new Hand();
		hand->deal(tiles, count);
		return hand;
	}
};

TEST_GROUP(UserPerspective) {
	UserPerspective * userPerspective;
	UIEvent *event;
	DummyUIEvent dummyEvent1;
	DummyUIEvent dummyEvent2;
	DummyUIEvent dummyEvent3;

	void setup() {
		MockUIEventFactory *eventFactory = new MockUIEventFactory();
		userPerspective = new UserPerspective(eventFactory);
	}

	void teardown() {
		delete userPerspective;
	}
};

TEST(UserPerspective, noEventWhenUserPerspectiveIsJustCreated) {
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, noPlayerBeforeDealing) {
	CHECK_EQUAL(0, userPerspective->getNumberOfPlayer());
}

TEST(UserPerspective, gotDealEventWhenDealToSelf) {
	mock().expectOneCall("createDealEvent").withParameter("view",
			(UserView *) userPerspective).andReturnValue(&dummyEvent1);

	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 0);

	POINTERS_EQUAL(&dummyEvent1, userPerspective->popEvent());
}

TEST(UserPerspective, noEventWhenDealToOthers) {
	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 1);
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, numberOfPlayerIs2WhenDealTwice) {
	mock().expectOneCall("createDealEvent").withParameter("view",
			(UserView *) userPerspective).andReturnValue(NULL);

	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 0);
	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 1);

	CHECK_EQUAL(2, userPerspective->getNumberOfPlayer());
}

TEST(UserPerspective, gotOnlyPickEventWhenPickAnIrrelevantTile) {
	userPerspective->setHand(0, HandDataMother().createAllIrrelevantHand());

	mock().expectOneCall("createPickEvent").withParameter("tile",
			(const char *)ANY_TILE).withParameter("distance", 0).andReturnValue(&dummyEvent2);

	userPerspective->pick(ANY_TILE, 0);

	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotAlsoWinEventWhenPickAWinningTile) {
	userPerspective->setHand(0, HandDataMother().createHandWinWithTheWinningTile());

	mock().expectOneCall("createPickEvent").withParameter("tile",
			(const char *)WINNING_TILE).withParameter("distance", 0).andReturnValue(&dummyEvent2);
	mock().expectOneCall("createEnableWinEvent").andReturnValue(&dummyEvent3);

	userPerspective->pick(WINNING_TILE, 0);

	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(&dummyEvent3, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotDiscardEventWhenDiscard) {
	mock().expectOneCall("createDiscardEvent").withParameter("tile",
			(const char *)WINNING_TILE).withParameter("distance", 0).andReturnValue(&dummyEvent2);

	userPerspective->discard(WINNING_TILE, 0);

	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotDealEventWhenPong) {
	userPerspective->setHand(0, HandDataMother().createHandPongTheWinningTile());

	mock().expectOneCall("createDealEvent").ignoreOtherParameters().andReturnValue(&dummyEvent2);

	userPerspective->pong(WINNING_TILE, 0);

	POINTERS_EQUAL(&dummyEvent2, userPerspective->popEvent());
	POINTERS_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotChowEventWhenChow) {
	userPerspective->setHand(0, HandDataMother().createHandChowTheWinningTile());

	mock().expectOneCall("createDealEvent").ignoreOtherParameters().andReturnValue(&dummyEvent2);

	userPerspective->chow(WINNING_TILE, WINNING_TILE+1, 0);

	POINTERS_EQUAL(&dummyEvent2, userPerspective->popEvent());
	POINTERS_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, shouldGetEnableEventsWhenOtherPlayerDiscard) {
	userPerspective->setHand(0, HandDataMother().createHandPongAndWinTheWinningTile());

	mock().expectOneCall("createDiscardEvent").withParameter("tile",
			(const char *)WINNING_TILE).withParameter("distance", 1).andReturnValue(&dummyEvent2);
	mock().expectOneCall("createEnableWinEvent").andReturnValue(&dummyEvent3);
	mock().expectOneCall("createEnablePongEvent").andReturnValue(&dummyEvent3);
	mock().ignoreOtherCalls();

	userPerspective->discard(WINNING_TILE, 1);

	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
	CHECK_EQUAL(&dummyEvent3, userPerspective->popEvent());
	CHECK_EQUAL(&dummyEvent3, userPerspective->popEvent());
}

TEST(UserPerspective, action_get_empty) {
	LONGS_EQUAL(NO_ACTION, userPerspective->takeActionRequest().action_);
}

TEST(UserPerspective, action_set_and_get) {
	PlayerActionRequest request(ACTION_DISCARD, MJ_EAST);
	userPerspective->pushActionRequest(&request);

	LONGS_EQUAL(ACTION_DISCARD, userPerspective->takeActionRequest().action_);
}

