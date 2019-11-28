#ifndef GAME__H
#define GAME__H

#include "tile.h"
#include "Settings.h"
#define MAX_TILE_COUNT 500

class Wall {
public:
	Wall(const Tile * tileTypes, int tileTypeCount, int maxPicks);
	virtual ~Wall();
	virtual void shuffleAndRebuild(const unsigned int suitCount = 4);
	virtual bool isEnd();
	virtual Tile popATile();
	virtual void changeFirstTileTo(Tile tile);

private:
	void initializePool(const unsigned int suitCount = 4);
	void swap(int index1, int index2);
	int getAllCount();
	int randomIndex();
	void applySettings(const unsigned int suitCount);

private:
	Tile tilePool_[MAX_TILE_COUNT];
	const Tile *tileTypes_;
	int tileTypeCount_;
	int picksCount_;
	int maxPicks_;
};

extern Wall * (*createWall)(void);

#endif
