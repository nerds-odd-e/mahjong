#include <queue>
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"

#include "TileArray.h"
#include "AIPerspective.h"

#include "CppUTest/TestHarness.h"

TEST_GROUP(ai_perspective)
{
	AIPerspective * perspective;
	EvaluatorAdaptor * evaluator;
	Settings settings_;
	void setup() {
		evaluator = createMockEvaluator();
		perspective = new AIPerspective(settings_);
		perspective->setEvaluator(evaluator);
		Tile holdings[] = { C(1) };
		perspective->deal(holdings, 1, 0);
	}
	void teardown() {
		delete perspective;
	}

};

TEST(ai_perspective, player_creation)
{
	LONGS_EQUAL(ACTION_PICK, perspective->takeActionRequest().action_);
}

TEST(ai_perspective, player_pick_when_winning)
{
	perspective->pick(C(1), 0);
	LONGS_EQUAL(ACTION_WIN, perspective->takeActionRequest().action_);
}

TEST(ai_perspective, player_react_when_winning)
{
	perspective->discard(C(1), 1);
	LONGS_EQUAL(ACTION_WIN, perspective->takeActionRequest().action_);
}

TEST(ai_perspective, player_pick)
{
	// ai player will call the evaluator to evaluate the array
	// twice, because there are two tiles after pick.
	mock()	.expectNCalls(2, "evaluate_array")
			.onObject(evaluator)
			.ignoreOtherParameters()
			.andReturnValue(1);
	perspective->pick(C(3), 0);
	LONGS_EQUAL(ACTION_DISCARD, perspective->takeActionRequest().action_);
}

TEST(ai_perspective, player_win)
{
	perspective->win(0, 0);
	LONGS_EQUAL(ACTION_RESTART, perspective->takeActionRequest().action_);
}
