#ifndef GAME__H
#define GAME__H

#include "tile.h"

#define MAX_TILE_COUNT 500

class Wall {
public:
	Wall(const Tile * tileTypes, int tileTypeCount, int maxPicks);
	virtual ~Wall();
	virtual void shuffleAndRebuild();
	virtual bool isEnd();
	virtual Tile popATile();
	virtual void changeFirstTileTo(Tile tile);

private:
	void initializePool();
	void swap(int index1, int index2);
	int getAllCount();
	int randomIndex();

private:
	Tile tilePool_[MAX_TILE_COUNT];
	const Tile *tileTypes_;
	int tileTypeCount_;
	int picksCount_;
	int maxPicks_;
};

extern Wall * (*createWall)(void);

#endif
