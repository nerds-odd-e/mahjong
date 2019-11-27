#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "UserPerspective.h"
#include "UIEvent.h"
#include "mocks.h"
#include "DataCreationHelpers.h"

TEST_GROUP(UserPerspective) {
	UserPerspective * userPerspective;
	UIEvent *event;
	Settings settings;

	void setup() {
		userPerspective = new UserPerspective(settings);
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
	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 0);
	UIEvent* event = userPerspective->popEvent();
	STRCMP_EQUAL("{\"action\":\"update_all\"}", event->toString().c_str());
	delete event;
}

TEST(UserPerspective, noEventWhenDealToOthers) {
	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 1);
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, numberOfPlayerIs2WhenDealTwice) {
	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 0);
	userPerspective->deal(defaultTilesPongTheWinningTileAndChowWinningTilePlusOne, 4, 1);

	CHECK_EQUAL(2, userPerspective->getNumberOfPlayer());
}

TEST(UserPerspective, gotOnlyPickEventWhenPickAnIrrelevantTile) {
	userPerspective->setHand(0, HandDataMother().createAllIrrelevantHand());
	userPerspective->pick(ANY_TILE, 0);
	UIEvent* event = userPerspective->popEvent();
	STRCMP_EQUAL("{\"action\":\"pick\", \"player\":0,\"tile\":8}", event->toString().c_str());
	delete event;
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotAlsoWinEventWhenPickAWinningTile) {
	userPerspective->setHand(0, HandDataMother().createHandWinWithTheWinningTile());
	userPerspective->pick(WINNING_TILE, 0);
	UIEvent* event = userPerspective->popEvent();
	STRCMP_EQUAL("{\"action\":\"pick\", \"player\":0,\"tile\":10}", event->toString().c_str());
	delete event;
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotDiscardEventWhenDiscard) {
	userPerspective->discard(WINNING_TILE, 0);
	UIEvent* event = userPerspective->popEvent();
	STRCMP_EQUAL("{\"action\":\"discard\", \"player\":0,\"tile\":10}", event->toString().c_str());
	delete event;
	CHECK_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotDealEventWhenPong) {
	userPerspective->setHand(0, HandDataMother().createHandPongTheWinningTile());
	userPerspective->pong(WINNING_TILE, 0);
	UIEvent* event = userPerspective->popEvent();
	STRCMP_EQUAL("{\"action\":\"update_all\"}", event->toString().c_str());
	delete event;
	POINTERS_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, gotChowEventWhenChow) {
	userPerspective->setHand(0, HandDataMother().createHandChowTheWinningTile());
	userPerspective->chow(WINNING_TILE, WINNING_TILE+1, 0);
	UIEvent* event = userPerspective->popEvent();
	STRCMP_EQUAL("{\"action\":\"update_all\"}", event->toString().c_str());
	delete event;

	POINTERS_EQUAL(NULL, userPerspective->popEvent());
}

TEST(UserPerspective, shouldGetEnableEventsWhenOtherPlayerDiscard) {
	userPerspective->setHand(0, HandDataMother().createHandPongAndWinTheWinningTile());
	userPerspective->discard(WINNING_TILE, 1);
	UIEvent* event = userPerspective->popEvent();

	STRCMP_EQUAL("{\"action\":\"discard\", \"player\":1,\"tile\":10}", event->toString().c_str());
	delete event;
}

TEST(UserPerspective, action_get_empty) {
	LONGS_EQUAL(NO_ACTION, userPerspective->takeActionRequest().action_);
}

TEST(UserPerspective, action_set_and_get) {
	PlayerActionRequest request(ACTION_DISCARD, MJ_EAST);
	userPerspective->pushActionRequest(&request);

	LONGS_EQUAL(ACTION_DISCARD, userPerspective->takeActionRequest().action_);
}

