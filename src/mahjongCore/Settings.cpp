#include <GameLevel.h>
#include <Settings.h>

unsigned int Settings::GetHandSize() const {
  auto hand_size{13U};
  if (level_.GetLevel() == 1) {
    hand_size = 4;
  }
  return hand_size;
}

unsigned int Settings::GetNumberOfSuites() const {
  auto number_of_suites{4U};
  if (level_.GetLevel() == 1) {
    number_of_suites = 1;
  }
  return number_of_suites;
}