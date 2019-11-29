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

	bool ContainsOnlyCircles()
	{
		std::vector<Tile> pool{};

		while(!wall->isEnd())
		{
			pool.push_back(wall->popATile());
		}
		return std::all_of(pool.begin(), pool.end(), IsCircle);
	}
	
	bool ContainsOnlyBamboo()
	{
		std::vector<Tile> pool{};

		while(!wall->isEnd())
		{
			pool.push_back(wall->popATile());
		}
		return std::all_of(pool.begin(), pool.end(), IsBamboo);
	}
};

TEST(wall, wallIsNotEndWhenCreated) {
	wall = new Wall(maxPops);
	CHECK(!wall->isEnd());
}

TEST(wall, popFromwallThatIsNotEmpty) {
	wall = new Wall(maxPops);
	wall->shuffleAndRebuild(1);
	Tile tile = wall->popATile();
	CHECK(IsCircle(tile));
}

TEST(wall, wallBecomesEmptyWhenPopTheMaxTimes) {
	int maxPops = 2;
	wall = new Wall(maxPops);
	
	wall->popATile();
	wall->popATile();
	CHECK(wall->isEnd());
}

TEST(wall, popCorrectTilesAfterShuffle) {
	
	wall = createWall();
	
	wall->shuffleAndRebuild(1);

	while (!wall->isEnd()) {
		Tile tile = wall->popATile();
		CHECK(IsCircle(tile));
	}
}

TEST(wall, randomnessAfterShuffle) {
    // use the same seed to
	// get the same set of random number every time.
	srand(100);

	wall = createWall();
	wall->shuffleAndRebuild(1);	
	Tile tileToCheck = wall->popATile();
	bool randomAtListOnceTime = false;
	for(int i = 0; i < 10; i++) {
		Tile new_popped_tile = wall->popATile();
		if(new_popped_tile != tileToCheck)
		{
			randomAtListOnceTime = true; 
			break;	
		}
		wall->shuffleAndRebuild(1);
	}
	CHECK(randomAtListOnceTime);
}

TEST(wall, poolWithOneSuite)
{
	wall = createWall();
	
	wall->shuffleAndRebuild(1);
    
    CHECK(IsTheSameSuit());
}

TEST(wall, poolContainsMoreThanOneSuit)
{
	wall = createWall();

	wall->shuffleAndRebuild();

	CHECK(!IsTheSameSuit());
}

TEST(wall, poolWithOneSuitContainsOnlyCircles)
{
	wall = createWall();

	wall->shuffleAndRebuild(1);

	CHECK(ContainsOnlyCircles());
}

TEST(wall, poolWithOneSuitContainsOnlyBamboo)
{
	wall = createWall();

	wall->shuffleAndRebuild(1);
	wall->shuffleAndRebuild(1);

	CHECK(ContainsOnlyBamboo());
}
