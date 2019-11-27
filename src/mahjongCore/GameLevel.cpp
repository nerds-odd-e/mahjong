#include "GameLevel.h"

constexpr unsigned int kNumberOfSubLevelsForLevelTwo {4};

void GameLevel::Won()
{
  if (level_ == 2)
  {
    IncrementSubLevel();
    if (subLevel_ == kNumberOfSubLevelsForLevelTwo)
    {
      level_ = 3;
      subLevel_ = 0;
    }
  }
}

void GameLevel::Lost()
{
  if (level_ == 2)
    return;
}
