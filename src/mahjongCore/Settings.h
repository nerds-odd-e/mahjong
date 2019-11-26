#ifndef SETTINGS_H_
#define SETTINGS_H_

class GameLevel;

class Settings {
public:
  Settings(const GameLevel &level) : level_{level} {}
  unsigned int GetHandSize() const;
  unsigned int GetNumberOfSuites() const;

private:
  const GameLevel &level_;
};

#endif // SETTINGS_H_