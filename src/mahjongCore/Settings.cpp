#include <GameLevel.h>
#include <Settings.h>
#include <vector>

const std::vector<unsigned int> HandSizeByLevel{1, 4, 4, 7, 13, 13, 13};
const std::vector<unsigned int> NumberOfSuitesByLevel{1, 1, 4, 4, 4, 4, 4};

unsigned int Settings::GetHandSize() const {
  return HandSizeByLevel[level_.GetLevel()];
}

unsigned int Settings::GetNumberOfSuites() const {
  return NumberOfSuitesByLevel[level_.GetLevel()];
}

GameLevel& Settings::GetGameLevel()
{
  return level_;
}