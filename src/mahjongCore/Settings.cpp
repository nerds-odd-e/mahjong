#include <GameLevel.h>
#include <Settings.h>
#include <vector>

const std::vector<int> HandSizeByLevel{1, 4, 13, 7, 13};
const std::vector<int> NumberOfSuitesByLevel{4, 1, 4, 4, 4};

unsigned int Settings::GetHandSize() const {
  return HandSizeByLevel[level_.GetLevel()];
}

unsigned int Settings::GetNumberOfSuites() const {
  return NumberOfSuitesByLevel[level_.GetLevel()];
}

unsigned int Settings::GetLevel() const
{
    return level_.GetLevel();
}
void Settings::IncrementLevel()
{
    level_.IncrementLevel();
}