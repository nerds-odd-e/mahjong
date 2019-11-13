#include "CppUTest/TestHarness.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TileArray.h"

#define MAX_HOLDING_COUNT 13

TEST_GROUP(TileArrayIsAbleToChow) {

};

TEST(TileArrayIsAbleToChow, not_able_to_chow) {
    Tile tiles[] = {MJ_EAST, MJ_WEST, MJ_SOUTH, MJ_NORTH};

    TileArray tileArray(tiles, sizeof(tiles));

    CHECK_FALSE(tileArray.isAbleToChow(MJ_CHARACTOR(1)));
}

TEST(TileArrayIsAbleToChow, chow_on_the_left) {
    Tile tiles[] = {MJ_CHARACTOR(2), MJ_CHARACTOR(3), MJ_EAST, MJ_WEST};

    TileArray tileArray(tiles, sizeof(tiles));

    CHECK_TRUE(tileArray.isAbleToChow(MJ_CHARACTOR(1)));
}

TEST(TileArrayIsAbleToChow, chow_on_the_right) {
    Tile tiles[] = {MJ_CHARACTOR(1), MJ_CHARACTOR(2), MJ_EAST, MJ_WEST};

    TileArray tileArray(tiles, sizeof(tiles));

    CHECK_TRUE(tileArray.isAbleToChow(MJ_CHARACTOR(3)));
}

TEST(TileArrayIsAbleToChow, chow_in_the_middle) {
    Tile tiles[] = {MJ_CHARACTOR(5), MJ_CHARACTOR(7), MJ_EAST, MJ_WEST};

    TileArray tileArray(tiles, sizeof(tiles));

    CHECK_TRUE(tileArray.isAbleToChow(MJ_CHARACTOR(6)));
}

TEST(TileArrayIsAbleToChow, chow_when_tile_already_there) {
    Tile tiles[] = {MJ_CHARACTOR(5), MJ_CHARACTOR(6), MJ_CHARACTOR(7), MJ_WEST};

    TileArray tileArray(tiles, sizeof(tiles));

    CHECK_TRUE(tileArray.isAbleToChow(MJ_CHARACTOR(6)));
}

TEST(TileArrayIsAbleToChow, not_able_to_chow_with_non_number_tile) {
    Tile tiles[] = {MJ_EAST, MJ_WEST, MJ_SOUTH, MJ_NORTH};

    TileArray tileArray(tiles, sizeof(tiles));

    CHECK_FALSE(tileArray.isAbleToChow(MJ_SOUTH));
}

