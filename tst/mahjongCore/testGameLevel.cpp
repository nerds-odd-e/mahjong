#include "CppUTest/TestHarness.h"
#include "GameLevel.h"

TEST_GROUP(GameLevel)
{
};

TEST(GameLevel, defaultLevelIsZero) {
    GameLevel level;
    CHECK_EQUAL(0, level.GetLevel());
}

TEST(GameLevel, initialSubLevelIsZero) {
    GameLevel level;
    CHECK_EQUAL(0, level.GetSubLevel());
}

TEST(GameLevel, incrementLevelIncrements) {
    GameLevel level;
    level.IncrementLevel();
    CHECK_EQUAL(1, level.GetLevel());
}

TEST(GameLevel, incrementLevelResetsSubLevel) {
    GameLevel level;
    level.IncrementLevel();
    CHECK_EQUAL(0, level.GetSubLevel());
}

TEST(GameLevel, incrementSubLevelIncrements) {
    GameLevel level;
    level.IncrementSubLevel();
    CHECK_EQUAL(1, level.GetSubLevel());
}