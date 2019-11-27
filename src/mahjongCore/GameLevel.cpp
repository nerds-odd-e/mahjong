#include "GameLevel.h"

void GameLevel::Won()
{
  if (level_ == 2)
    IncrementSubLevel();
}

void GameLevel::Lost()
{
  if (level_ == 2)
    return;
}
