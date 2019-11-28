#include "GameLevel.h"
#include <map>

const std::map<unsigned int, int> levelToWinsMap{
  {0, 1},
  {1, 3},
  {2, 5},
  {3, 5},
  {4, 4},
  {5, 5},
};

void GameLevel::Won()
{
  IncrementSubLevel();
  if (levelToWinsMap.at(level_) <= subLevel_)
  {
     IncrementLevel();
  }
}

void GameLevel::Lost()
{
  if (level_ != 4)
    return;
  subLevel_--;
}
