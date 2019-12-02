#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "aiGame.h"
#include "../mocks.h"

TEST_GROUP(game) {
	Settings settings;
	Game * game;
};

TEST(game, gameShouldTakeActionRequestFromPlayerWhenTick) {
	game = new Game();
	Player * player = new MockPlayer(settings);
	MockPlayerActionRequest action;
	game->addPlayer(player);

	mock().expectOneCall("takeActionRequest").onObject(player).andReturnValue(&action);
	mock().expectOneCall("hasAction").onObject(&action).andReturnValue(0);

	game->tick();

	delete game;
}

TEST(game, gameShouldTakeActionRequestAndDoItWhenTick) {
	game = new Game();
	Player * player = new MockPlayer(settings);
	MockPlayerActionRequest action;
	game->addPlayer(player);

	mock().expectOneCall("takeActionRequest").onObject(player).andReturnValue(&action);
	mock().expectOneCall("hasAction").onObject(&action).andReturnValue(1);
	mock().expectOneCall("doPlayerAction").onObject(&action).ignoreOtherParameters();
	mock().expectOneCall("takeActionRequest").onObject(player).andReturnValue(&action);
	mock().expectOneCall("hasAction").onObject(&action).andReturnValue(0);

	game->tick();

	delete game;
}


TEST_GROUP(AIGame) {
	Game * game;
};

TEST(AIGame, creatingAGameWithOnlyAIPlayer) {
	game = createMJGameWithOneAIPlayerOnly();

	delete game;
}

