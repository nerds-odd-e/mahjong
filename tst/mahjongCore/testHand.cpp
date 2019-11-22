#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TileArray.h"
#include "Hand.h"
#include "mj_table.h"
#include "../mocks.h"

TEST_GROUP(Hand) {
	Hand * hand;
	Tile tiles[100];
	void setup() {
		hand=createHand();

	}
	void teardown() {
		delete hand;
	}
};

TEST(Hand,get_tiles_when_not_dealt) {
	Tile tiles[14];
	LONGS_EQUAL(0, hand->getHoldings(tiles, 14));
	CHECK_EQUAL(NO_TILE, hand->getCurrentTileAtHand());
}

TEST(Hand,get_tiles_when_dealt) {
	Tile tiles_of_deal[4] = {C(3), C(4), C(1), C(2)};
	Tile tiles[14];
	hand->deal(tiles_of_deal, 4);
	LONGS_EQUAL(4, hand->getHoldings(tiles, 14));
	CHECK_EQUAL(C(1), tiles[0]);
	CHECK_EQUAL(C(4), tiles[3]);
	CHECK_EQUAL(NO_TILE, hand->getCurrentTileAtHand());
}
TEST(Hand,meld_info_has_been_reset_after_deal) {
	Meld meld;
	Tile tiles_of_deal1[] = {C(1),C(1)};
	hand->deal(tiles_of_deal1, 1);
	hand->pong(C(1));
	Tile tiles_of_deal2[] = {C(3)};
	hand->deal(tiles_of_deal2, 1);
	LONGS_EQUAL(0, hand->getMelds(&meld, 1));
}

TEST(Hand,isAbleToPong) {
	Tile tiles1[] = {MJ_EAST, MJ_EAST};
	hand->deal(tiles1, 2);
	LONGS_EQUAL(1, hand->isAbleToPong(MJ_EAST));
	Tile tiles2[] = {MJ_EAST, MJ_NORTH, MJ_NORTH, MJ_NORTH};
	hand->deal(tiles2, 4);
	LONGS_EQUAL(0, hand->isAbleToPong(MJ_EAST));
}

TEST(Hand,pong) {
	Tile tiles1[] = {MJ_EAST, MJ_EAST, MJ_NORTH};
	Meld meld[3];
	hand->deal(tiles1, 3);
	hand->pong(MJ_EAST);
	LONGS_EQUAL(0,hand->getHoldings(tiles, 3));
	LONGS_EQUAL(1,hand->getMelds(meld, 3));
	LONGS_EQUAL(PONG(MJ_EAST), meld[0]);
}
TEST(Hand,chow_fail) {
	Tile tiles1[] = {1, 2, 3};
	Meld meld[3];
	hand->deal(tiles1, 3);
	LONGS_EQUAL(0, hand->chow(4, 3));
	LONGS_EQUAL(3,hand->getHoldings(tiles, 3));
	LONGS_EQUAL(0,hand->getMelds(meld, 3));
}

TEST(Hand,chow_middle) {
	Tile tiles1[] = {C(1), C(3), C(4)};
	Meld meld[3];
	hand->deal(tiles1, 3);
	CHECK(hand->chow(C(2), C(1)));
	LONGS_EQUAL(0,hand->getHoldings(tiles, 3));
	CHECK_EQUAL(C(4),hand->getCurrentTileAtHand());
	LONGS_EQUAL(1,hand->getMelds(meld, 3));
	LONGS_EQUAL(CHOW(C(1)), meld[0]);
}

TEST(Hand,chow_last) {
	Tile tiles1[] = {C(2), C(3), C(4), C(9)};
	Meld meld[3];
	hand->deal(tiles1, 4);
	CHECK(hand->chow(C(5), C(3)));
	LONGS_EQUAL(1,hand->getHoldings(tiles, 4));
	CHECK_EQUAL(C(9),hand->getCurrentTileAtHand());
	LONGS_EQUAL(1,hand->getMelds(meld, 3));
	LONGS_EQUAL(CHOW(C(3)), meld[0]);
}


const Tile CURRENT_TILE = C(1);
const Tile HOLDING_TILE = C(2);
TEST_GROUP(HandDiscard) {
	Hand * hand;
	Tile tileBuffer[1];
	void setup() {
		hand=createHand();
		Tile tiles1[] = {HOLDING_TILE};
		hand->deal(tiles1, 1);
		hand->pick(CURRENT_TILE);
	}
	void teardown() {
		delete hand;
	}
};

TEST(HandDiscard,holdingShouldNotChangeWhenDiscardTheCurrentTile) {
	hand->discard(CURRENT_TILE);
	hand->getHoldings(tileBuffer, 1);
	CHECK_EQUAL(HOLDING_TILE, tileBuffer[0]);
}

TEST(HandDiscard,holdingShouldChangeToCurrentWhenDiscardTheHoldingTile) {
	hand->discard(HOLDING_TILE);
	hand->getHoldings(tileBuffer, 1);
	CHECK_EQUAL(CURRENT_TILE, tileBuffer[0]);
}
