#include "GameLevel.h"

constexpr unsigned int kNumberOfSubLevelsForLevelTwo {4};

void GameLevel::Won()
{
  if (level_ != 2)
  {
    return;
  }
  
  IncrementSubLevel();
  if (subLevel_ != kNumberOfSubLevelsForLevelTwo)
  {
    return;
  }
  
  level_ = 3;
  subLevel_ = 0;  
}

void GameLevel::Lost()
{

}
