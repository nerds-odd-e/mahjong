#ifndef GAMELEVEL_H_
#define GAMELEVEL_H_

class GameLevel {
public:
  GameLevel(unsigned int level = 0) : level_(level), subLevel_(0) {}
  unsigned int GetLevel() const { return level_; }
  unsigned int GetSubLevel() const { return subLevel_; }
  void SetLevel(unsigned int level) { level_ = level;}
  void SetSubLevel(unsigned int sublevel) { subLevel_ = sublevel;}
  void IncrementLevel() { ++level_; subLevel_ = 0; }
  void IncrementSubLevel() { ++subLevel_; }
  void Won();
  void Lost();
 
private:

  void UpgradeFromLevelZero();
  void UpgradeFromLevelOne();
  void UpgradeFromLevelTwo();

  unsigned int level_;
  unsigned int subLevel_;
};

#endif // GAMELEVEL_H_