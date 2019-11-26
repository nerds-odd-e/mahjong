class GameLevel {
public:
  GameLevel(unsigned int level = 0) : level_(level) {}
  unsigned int GetLevel() const { return level_; }
  void SetLevel(const unsigned int level) { level_ = level; }
  void Increment() { ++level_; }

private:
  unsigned int level_;
};