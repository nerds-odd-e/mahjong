#ifndef GAMELEVEL_H_
#define GAMELEVEL_H_

class GameLevel {
public:
  GameLevel(unsigned int level = 0) : level_(level), subLevel_(0) {}
  unsigned int GetLevel() const { return level_; }
  int GetSubLevel() const { return subLevel_; }
  void SetLevel(unsigned int level) { level_ = level;}
  void IncrementLevel() { ++level_; subLevel_ = 0; }
  void IncrementSubLevel() { ++subLevel_; }
  void Won();
  void Lost();
  
 
private:
  unsigned int level_;
  int subLevel_;
};

#endif // GAMELEVEL_H_