#ifndef TILES__H
#define TILES__H

#include "tile.h"

class TileArray {
public:
	TileArray(const Tile * tiles, int count);
	virtual ~TileArray();

	bool has(Tile tile) const;
	bool isAbleToChow(Tile tile) const;
	int getTileCount() const;
	bool isAbleToPong(Tile tile) const;
	bool winWith(Tile discard) const;
	const Tile& operator[] (int n) const;

	void remove(Tile tile, int count);
	void replaceOneOf(Tile tile, Tile with);

private:
    bool isNotAbleToChowOnTheRight(const Tile& tile) const;
    Tile previousTile(const Tile& tile) const; 

	Tile * tiles_;
	int tileCount_;
};

#endif
