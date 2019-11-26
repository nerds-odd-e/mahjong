class GameLevel {
public:
  GameLevel(unsigned int level = 0) : level_(level), subLevel_(0) {}
  unsigned int GetLevel() const { return level_; }
  unsigned int GetSubLevel() const { return subLevel_; }
  void IncrementLevel() { ++level_; subLevel_ = 0; }
  void IncrementSubLevel() { ++subLevel_; }
private:
  unsigned int level_;
  unsigned int subLevel_;
};