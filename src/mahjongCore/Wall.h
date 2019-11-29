#ifndef GAME__H
#define GAME__H

#include <vector>

#include "tile.h"
#include "Settings.h"
#define MAX_TILE_COUNT 500

class Wall {
public:
	Wall (const std::vector<Tile>& tileTypes, int maxPicks);
	virtual ~Wall();
	virtual void shuffleAndRebuild(const unsigned int suitCount = 4);
	virtual bool isEnd();
	virtual Tile popATile();
	virtual Tile peekTile(int index);
	virtual void changeFirstTileTo(Tile tile);
	virtual void setShuffleTimes(int shuffleTimes);
	void swap(int index1, int index2);

private:
	void initializePool(const unsigned int suitCount = 4);
	int getAllCount();
	int randomIndex();
	void applySettings(const unsigned int suitCount);

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
