#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "UserPerspective.h"
#include "HTMLUIEvent.h"
#include "mocks.h"
#include "DataCreationHelpers.h"

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

	userPerspective->pick(WINNING_TILE, 0);

	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
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
	mock().ignoreOtherCalls();

	userPerspective->discard(WINNING_TILE, 1);

	CHECK_EQUAL(&dummyEvent2, userPerspective->popEvent());
}

TEST(UserPerspective, action_get_empty) {
	LONGS_EQUAL(NO_ACTION, userPerspective->takeActionRequest().action_);
}

TEST(UserPerspective, action_set_and_get) {
	PlayerActionRequest request(ACTION_DISCARD, MJ_EAST);
	userPerspective->pushActionRequest(&request);

	LONGS_EQUAL(ACTION_DISCARD, userPerspective->takeActionRequest().action_);
}

