#include "CppUTest/TestHarness.h"

#include "DummyPlayerPerspective.h"


TEST_GROUP(dummy_player_perspective)
{
	DummyPlayerPerspective * perspective;
	Settings settings_;
	void setup() {
		perspective = new DummyPlayerPerspective(settings_);
		Tile holdings[] = { C(1) };
		perspective->deal(holdings, 1, 0);
	}
	void teardown() {
		delete perspective;
	}

};

TEST(dummy_player_perspective, perspective_creation)
{
	LONGS_EQUAL(ACTION_PICK, perspective->takeActionRequest().action_);
}

TEST(dummy_player_perspective, player_discards_picked_tile)
{
	Tile picked_tile{ C(2) };
	perspective->pick(picked_tile, 0);
	PlayerActionRequest* action_request = perspective->takeActionRequest1();
	CHECK_EQUAL(picked_tile, action_request->tile_);
	LONGS_EQUAL(ACTION_DISCARD, action_request->action_);
}
