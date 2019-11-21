#ifndef TILE_ARRAY_H_
#define TILE_ARRAY_H_

#define MAX_HOLDING_COUNT 13
#define MAX_MELD_COUNT (MAX_HOLDING_COUNT/3)

#include "TileArray.h"

class Hand {
public:
	Hand();
	~Hand();
	int getHoldings(Tile * tiles_buffer, int buffer_size) const;
	int getMelds(Meld * tiles_buffer, int buffer_size) const;
	Tile getCurrentTileAtHand() const;

	void pick(Tile);
	void pong(Tile);
	bool chow(Tile tile, Tile with);
	Tile discard(Tile tile);
	void deal(const Tile tiles[], int tiles_count);

	int isAbleToPong(Tile tile) const;
	int isAbleToChow(Tile tile) const;
	int isAbleToWin(Tile tile) const;

private:
	void rearrangeAfterMeld(Meld meld);
	bool isAbleToChowWithSmallest(Tile tile, Tile smallest) const;
	void _chow(Tile tile, Tile smallest);

private:
	Meld melds_[MAX_MELD_COUNT];
	TileArray * tileArray_;
	Tile current_;
};

Hand *createHand(void);

#endif /* TILE_ARRAY_H_ */
