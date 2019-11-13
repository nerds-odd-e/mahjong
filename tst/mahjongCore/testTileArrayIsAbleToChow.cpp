#include "CppUTest/TestHarness.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TileArray.h"

#define MAX_HOLDING_COUNT 13

TEST_GROUP(TileArrayIsAbleToChow) {

};

TEST(TileArrayIsAbleToChow, start_here)
{
    Tile tiles[] = {NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE, NO_TILE};

    TileArray tileArray(tiles, MAX_HOLDING_COUNT);

    CHECK_FALSE(tileArray.isAbleToChow(MJ_CHARACTOR(1)));
}

