#include <vector>
#include <algorithm>
#include <cassert>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Wall.h"


TEST_GROUP(wall) {
	Wall * wall;
	int maxPops;
	void setup() {
		wall = NULL;
		maxPops = 2;
	}

	void teardown() {
		delete wall;
	}

    static bool IsCharacter(Tile& tile)
	{
		return tile.getID() >= C(1).getID() && tile.getID() <= C(9).getID();
	}

	static bool IsCircle(Tile& tile)
	{
		return tile.getID() >= R(1).getID() && tile.getID() <= R(9).getID();
	}

	static bool IsBamboo(Tile& tile)
	{
		return tile.getID() >= B(1).getID() && tile.getID() <= B(9).getID();
	}

	bool IsTheSameSuit()
	{
        std::vector<Tile> pool{};

		while(!wall->isEnd())
		{
			pool.push_back(wall->popATile());
		}

		bool is_character = std::all_of(pool.begin(), pool.end(), IsCharacter);
		bool is_circle = std::all_of(pool.begin(), pool.end(), IsCircle);
		bool is_bamboo = std::all_of(pool.begin(), pool.end(), IsBamboo);

		return is_character || is_circle || is_bamboo;
	}
};

TEST(wall, wallIsNotEndWhenCreated) {
	Tile tileTypes[] = {C(1)};
	wall = new Wall(tileTypes, 1, maxPops);
	CHECK(!wall->isEnd());
}

TEST(wall, popFromwallThatIsNotEnd) {
	Tile tileTypes[] = {C(1)};
	wall = new Wall(tileTypes, 1, maxPops);
	CHECK_EQUAL(C(1), wall->popATile());
}

TEST(wall, wallBecomesEmptyWhenPopTheMaxTimes) {
	Tile tileTypes[] = {C(1)};
	int maxPops = 2;
	wall = new Wall(tileTypes, 1, maxPops);
	wall->popATile();
	wall->popATile();
	CHECK(wall->isEnd());
}

TEST(wall, popRightTilesAfterShuffle) {
	Tile tileTypes[] = {C(1), C(2)};
	int maxPops = 8;
	wall = new Wall(tileTypes, 2, maxPops);

	wall->shuffleAndRebuild();

	while (!wall->isEnd()) {
		Tile tile = wall->popATile();
		CHECK(tile == C(1) || tile == C(2));
	}
}

TEST(wall, randomnessAfterShuffle) {
	// use the same seed to
	// get the same set of random number every time.
	srand(100);

	Tile tileTypes[] = {C(1), C(2)};
	int maxPops = 8;
	wall = new Wall(tileTypes, 2, maxPops);

	wall->shuffleAndRebuild();

	bool hasC1 = false, hasC2 = false;
	for(int i = 0; i < 4; i++) {
		Tile tile = wall->popATile();
		hasC1 |= (tile == C(1));
		hasC2 |=(tile == C(2));
	}

	CHECK(hasC1);
	CHECK(hasC2);
}

TEST(wall, poolWithOneSuite)
{
	wall = createWall();
	
	wall->shuffleAndRebuild(1);
    
    CHECK(IsTheSameSuit());
}

TEST(wall, poolWithFourSuite)
{
	wall = createWall();

	wall->shuffleAndRebuild();

	CHECK(!IsTheSameSuit());
}

