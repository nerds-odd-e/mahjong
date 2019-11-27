#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "GameLevel.h"

class Settings {
public:
  Settings() :level_(0){} ;
  unsigned int GetHandSize() const;
  unsigned int GetNumberOfSuites() const;
  GameLevel& GetGameLevel();

private:
  GameLevel level_;
};

#endif // SETTINGS_H_