#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "GameLevel.h"

class Settings {
public:
  Settings() = default;
  unsigned int GetHandSize() const;
  unsigned int GetNumberOfSuites() const;
  unsigned int GetLevel() const;
  void IncrementLevel();

private:
  GameLevel level_;
};

#endif // SETTINGS_H_