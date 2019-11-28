#include "GameLevel.h"

constexpr unsigned int kNumberOfSubLevelsForLevelTwo {4};
constexpr unsigned int kNumberOfSubLevelsForLevelOne {3};
constexpr unsigned int kNumberOfSubLevelsForLevelFour {4};

void GameLevel::Won()
{
  switch (level_)
  {
  case 0:
      UpgradeFromLevelZero();
    break;
  case 1:
      UpgradeFromLevelOne();
    break;
  case 2:
      UpgradeFromLevelTwo();
    break;
  case 4:
      UpgradeFromLevelFour();
    break;
  default:
    break;
  }
}

void GameLevel::Lost()
{
  if (level_ != 4)
    return;

  subLevel_--;
}

void GameLevel::UpgradeFromLevelZero()
{
  IncrementLevel();
}

void GameLevel::UpgradeFromLevelOne()
{
  IncrementSubLevel();
  if (subLevel_ == kNumberOfSubLevelsForLevelOne)
  {
    IncrementLevel();
  }
}

void GameLevel::UpgradeFromLevelTwo()
{
  IncrementSubLevel();
  if (subLevel_ == kNumberOfSubLevelsForLevelTwo)
  {
    IncrementLevel();
  }
}

void GameLevel::UpgradeFromLevelFour()
{
  IncrementSubLevel();
  if (subLevel_ == kNumberOfSubLevelsForLevelFour)
  {
    IncrementLevel();
  }
}
