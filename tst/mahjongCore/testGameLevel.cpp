#include "CppUTest/TestHarness.h"
#include "GameLevel.h"

TEST_GROUP(GameLevel)
{
};

TEST(GameLevel, defaultLevelIsZero) {
    GameLevel level;
    CHECK_EQUAL(0, level.GetLevel());
}

TEST(GameLevel, incrementLevelIncrements) {
    GameLevel level;
    level.Increment();
    CHECK_EQUAL(1, level.GetLevel());
}

TEST(GameLevel, setLevelSets) {
    GameLevel level;
    level.SetLevel(3);
    CHECK_EQUAL(3, level.GetLevel());
}