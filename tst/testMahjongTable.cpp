#include <queue>
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Wall.h"
#include "mj_table.h"
#include "mocks.h"
#include "CppUTest/TestHarness.h"
#include "AIPerspective.h"
#include "UserPerspective.h"
#include "Hand.h"


TEST_GROUP(MahjongTable) {
    Wall * wall_ = createWall();
    Settings settings;
	MahjongTable * table_ = new MahjongTable(wall_, settings);
    UserPerspective * userPerspective = new UserPerspective(settings);
	// UserPerspective * userPerspective = new UserPerspective();

    void teardown() {
        delete table_;
        delete userPerspective;
        delete wall_;
    }
};


TEST(MahjongTable, it_must_have_1_tiles_when_the_level_is_0) {
    Tile tiles[100];
    table_->addPlayer(userPerspective);
    table_->restartGame();
    Hand *hand = userPerspective->getHand(0);
    int count = hand->getHoldings(tiles, 100);
    CHECK_EQUAL(1, count);
}
