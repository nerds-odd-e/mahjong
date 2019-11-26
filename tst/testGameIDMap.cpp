#include "GameIDMap.h"
#include "game.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


TEST_GROUP(GameIDMap) {
	GameIDMap map;
	Game *game1;
	Game *game2;
	int id1;
	int id2;
	void setup() {
        Settings settings;
		game1 = new Game(settings);
		game2 = new Game(settings);
		id1 = map.addGameAndGetID(game1);
		id2 = map.addGameAndGetID(game2);
	}
};

TEST(GameIDMap, should_get_null_when_asking_for_unexistent_id){
	const int ANY_ID = 300;
	CHECK_EQUAL(NULL, map.getGameByID(ANY_ID));
}

TEST(GameIDMap, ids_should_not_be_equal_when_insert_two_items){
	CHECK(id1 != id2);
}
TEST(GameIDMap, should_get_the_right_item_when_there_are_more_than_one){
	CHECK_EQUAL(game1, map.getGameByID(id1));
	CHECK_EQUAL(game2, map.getGameByID(id2));
}
TEST(GameIDMap, should_get_null_when_the_item_is_removed){
	map.removeAndDeleteGame(id1);
	CHECK_EQUAL(NULL, map.getGameByID(id1));
}
