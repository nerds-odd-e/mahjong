#include "CppUTest/TestHarness.h"
#include "GameLevel.h"
#include "Settings.h"

TEST_GROUP(Settings){};

TEST(Settings, defaultHandSizeIsThirteen) {
  GameLevel level;
  Settings settings{level};
  CHECK_EQUAL(13, settings.GetHandSize());
}

TEST(Settings, levelOneHandSizeIsFour) {
  GameLevel level{1};
  Settings settings{level};
  CHECK_EQUAL(4, settings.GetHandSize());
}

TEST(Settings, defaultNumberOfSuitesIsFour) {
  GameLevel level;
  Settings settings{level};
  CHECK_EQUAL(4, settings.GetNumberOfSuites());
}

TEST(Settings, levelOneNumberOfSuitesIsOne) {
  GameLevel level{1};
  Settings settings{level};
  CHECK_EQUAL(1, settings.GetNumberOfSuites());
}