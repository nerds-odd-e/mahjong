#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLMahjongGameResponse.h"
#include "UserPerspective.h"
#include "DataCreationHelpers.h"

TEST_GROUP(HTMLMahjongGameResponse) {
    HTMLMahjongGameResponse response;
	UserPerspective userPerspective;
    HandBuilder handBuilder;
	void setup() {
	}
	void teardown() {
	}
};

TEST(HTMLMahjongGameResponse, when_opponent_discards_a_tile_player_can_both_pong_and_win) {
    handBuilder.withAPairOf(MJ_BAMBOO(1)).withTiles(MJ_BAMBOO(2), MJ_BAMBOO(3)).dealToPlease(&userPerspective, 0);
    userPerspective.discard(MJ_BAMBOO(1), 1);
    response.currentGameStatus(&userPerspective);
    const char * result = response.getString();
    STRCMP_CONTAINS("\"allowed_actions\":[\"win\",\"pong\",\"chow\"]", result);
}