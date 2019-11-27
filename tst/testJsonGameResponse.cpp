#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "GameJsonResponse.h"
#include "UserPerspective.h"
#include "DataCreationHelpers.h"
#include <memory>

TEST_GROUP(GameJsonResponse) {
    GameJsonResponse response;
    Settings settings;
	std::unique_ptr<UserPerspective>  userPerspective;
    HandBuilder handBuilder;
	void setup() {
        userPerspective = std::make_unique<UserPerspective>(settings);
	}
	void teardown() {
	}
};

TEST(GameJsonResponse, empty_response) {
    const char * result = response.getString();
    STRCMP_CONTAINS("{}", result);
}
TEST(GameJsonResponse, when_opponent_discards_a_tile_player_can_both_pong_and_win) {
    handBuilder.withAPairOf(B(1)).withTiles(B(2), B(3)).dealToPlease(userPerspective.get(), 0);
    userPerspective->discard(MJ_BAMBOO(1), 1);
    response.currentGameStatus(userPerspective.get());
    const char * result = response.getString();
    STRCMP_CONTAINS("\"allowed_actions\":[\"win\",\"pong\",\"chow\"]", result);
}