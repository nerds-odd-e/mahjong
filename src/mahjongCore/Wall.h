#ifndef GAME__H
#define GAME__H

#include <vector>

#include "tile.h"
#include "Settings.h"
#define MAX_TILE_COUNT 500

enum class HandGenerationRule {
  LEVEL_1_RULE_1 = 0,
  LEVEL_1_RULE_2,
  LEVEL_1_RULE_3
};

class Wall {
public:
	Wall (int maxPicks);
	virtual ~Wall();
	virtual void shuffleAndRebuild(const unsigned int suitCount = 4);
	virtual bool isEnd();
	virtual Tile popATile();
	virtual Tile peekTile(int index);
	virtual void changeFirstTileTo(Tile tile);
	virtual void setShuffleTimes(int shuffleTimes);
	void GeneratePredefinedHand(const HandGenerationRule);

private:
	void initializePool(const unsigned int suitCount = 4);
	int getAllCount();
	int randomIndex();
	void applySettings(const unsigned int suitCount);
	void swap(int index1, int index2);
	void SwapForTheSameTile(Tile tile, int index);
	void SwapForADifferentTile(Tile tile, int index);
	void GenerateTwoPairs();
	void GenerateATriplet();
	void GenerateAPair();

private:
	Tile tilePool_[MAX_TILE_COUNT];
	std::vector<Tile> tileTypes_;
	int picksCount_;
	int maxPicks_;
	int shuffleTimes_;
	int suitIndex_ = 0;
};

extern Wall * (*createWall)(void);

#endif
