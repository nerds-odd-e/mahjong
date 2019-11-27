#include "CppUTest/TestHarness.h"
#include "GameLevel.h"
#include "Settings.h"

TEST_GROUP(Settings){};

TEST(Settings, WhenLevelZeroThenHandSizeOne) {
  Settings settings{};
  CHECK_EQUAL(1, settings.GetHandSize());
}

TEST(Settings, WhenLevelOneThenHandSizeIsFour) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(1);
  CHECK_EQUAL(4, settings.GetHandSize());
}

TEST(Settings, WhenLevelTwoThenHandSizeIsThirtheen) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(2);
  CHECK_EQUAL(13, settings.GetHandSize());
}

TEST(Settings, WhenLevelThreeThenHandSizeIsSeven) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(3);
  CHECK_EQUAL(7, settings.GetHandSize());
}

TEST(Settings, WhenLevelFourThenHandSizeIsThirtheen) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(4);
  CHECK_EQUAL(13, settings.GetHandSize());
}

TEST(Settings, WhenLevelZeroThenSuiteSizeAll) {
  Settings settings{};
  CHECK_EQUAL(4, settings.GetNumberOfSuites());
}

TEST(Settings, WhenLevelOneThenSuiteSizeIs1) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(1);
  CHECK_EQUAL(1, settings.GetNumberOfSuites());
}

TEST(Settings, WhenLevelTwoThenSuiteSizeAll) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(2);
  CHECK_EQUAL(4, settings.GetNumberOfSuites());
}

TEST(Settings, WhenLevelThreeThenSuiteSizeAll) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(3);
  CHECK_EQUAL(4, settings.GetNumberOfSuites());
}

TEST(Settings, WhenLevelFourThenHandSuiteSizeAll) {
  Settings settings{};
  settings.GetGameLevel().SetLevel(4);
  CHECK_EQUAL(4, settings.GetNumberOfSuites());
}