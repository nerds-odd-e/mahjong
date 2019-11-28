#include "GameLevel.h"

constexpr unsigned int kNumberOfSubLevelsForLevelTwo {4};
constexpr unsigned int kNumberOfSubLevelsForLevelOne {3};


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
  default:
    break;
  }
}

void GameLevel::Lost()
{

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
