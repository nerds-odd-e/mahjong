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

void SubLevelUp(GameLevel & level, const int iterations)
{
    for (int i = 0; i < iterations; ++i)
    {
        level.Won();
    }
}

TEST(GameLevel, LevelTwoFourWins_ThenGoToLevelThree) {
    GameLevel level{2};
    CHECK_EQUAL(2, level.GetLevel());
    SubLevelUp(level,4);
    CHECK_EQUAL(3, level.GetLevel());
}

TEST(GameLevel, LevelZeroOneWin_ThenGoToLevelOne) {
    GameLevel level{0};
    level.Won();
    CHECK_EQUAL(1, level.GetLevel());
}

TEST(GameLevel, LevelTwoThreeWinsOneLose_ThenStayInLevelTwo) {
    GameLevel level{2};
    CHECK_EQUAL(2, level.GetLevel());
    SubLevelUp(level,3);
    CHECK_EQUAL(2, level.GetLevel());
    level.Lost();
    CHECK_EQUAL(2, level.GetLevel());
}

TEST(GameLevel, LevelTwoFourWinsOneLose_ThenGoToLevelThree) {
    GameLevel level{2};
    CHECK_EQUAL(2, level.GetLevel());
    SubLevelUp(level,2);
    CHECK_EQUAL(2, level.GetLevel());
    level.Lost();
    CHECK_EQUAL(2, level.GetLevel());
    SubLevelUp(level,2);
    CHECK_EQUAL(3, level.GetLevel());
}

TEST(GameLevel, LevelFourFourWinsNoLose_ThenGoToLevelFive) {
    GameLevel level{4};
    CHECK_EQUAL(4, level.GetLevel());
    SubLevelUp(level,4);
    CHECK_EQUAL(5, level.GetLevel());
}

TEST(GameLevel, LevelFourThreeWinsNoLose_ThenStayLevelFour) {
    GameLevel level{4};
    CHECK_EQUAL(4, level.GetLevel());
    SubLevelUp(level, 3);
    CHECK_EQUAL(4, level.GetLevel());
}

TEST(GameLevel, LevelFourFourWinsOneLose_ThenStayLevelFour) {
    GameLevel level{4};
    CHECK_EQUAL(4, level.GetLevel());
    CHECK_EQUAL(0, level.GetSubLevel());
    level.Lost();
    CHECK_TRUE(0 > level.GetSubLevel());
    SubLevelUp(level, 4);
    CHECK_EQUAL(3, level.GetSubLevel());
    CHECK_EQUAL(4, level.GetLevel());
}