#include "CppUTest/TestHarness.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TileArray.h"

TEST_GROUP(TileArrayIsAbleToChow) {
    Tile tiles_array[13];
};

TEST(TileArrayIsAbleToChow, not_able_to_chow_when_0_tile_and_C_given)
{
	TileArray tiles(tiles_array, 0);

    CHECK_FALSE(tiles.isAbleToChow(C(1)));
}

TEST(TileArrayIsAbleToChow, not_able_to_chow_when_0_tile_and_R_given)
{
    TileArray tiles(tiles_array, 0);

    CHECK_FALSE(tiles.isAbleToChow(R(1)));
}

TEST(TileArrayIsAbleToChow, not_able_to_chow_when_1_tile_and_C_given)
{
    tiles_array[0] = C(1);
	TileArray tiles(tiles_array, 1);

    CHECK_FALSE(tiles.isAbleToChow(C(1)));
}

TEST(TileArrayIsAbleToChow, not_able_to_chow_because_missing_previous_tile)
{
    tiles_array[0] = C(1);
    tiles_array[1] = C(2);
	TileArray tiles(tiles_array, 2);

    CHECK_FALSE(tiles.isAbleToChow(C(4)));
}

TEST(TileArrayIsAbleToChow, able_to_chow_when_given_two_previous)
{
    tiles_array[0] = C(1);
    tiles_array[1] = C(2);
	TileArray tiles(tiles_array, 2);

    CHECK_TRUE(tiles.isAbleToChow(C(3)));
}

TEST(TileArrayIsAbleToChow, not_able_to_chow_when_missing_previous_previous)
{
    tiles_array[0] = C(6);
    tiles_array[1] = C(3);
	TileArray tiles(tiles_array, 2);

    CHECK_FALSE(tiles.isAbleToChow(C(4)));
}

TEST(TileArrayIsAbleToChow, not_able_to_chow_when_missing_next)
{
    tiles_array[0] = C(3);
    tiles_array[1] = C(5);
	TileArray tiles(tiles_array, 2);

    CHECK_FALSE(tiles.isAbleToChow(C(1)));
}