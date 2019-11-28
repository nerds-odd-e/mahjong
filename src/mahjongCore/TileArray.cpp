#include <stdlib.h>
#include <memory.h>
#include "TileArray.h"

#define MAX_HOLDING_COUNT 13

static int tiles_is_winning(Tile tile_array[], int size_of_array,
		int had_pair);

static int tiles_is_winning_remove_a_pair(Tile tile_array[],
		int size_of_array) {
	if (tile_array[0] == tile_array[1]) {
		if (tiles_is_winning(tile_array + 2, size_of_array - 2, 1))
			return 1;
	}
	return 0;
}

static int tiles_is_winning_remove_a_pong(Tile tile_array[],
		int size_of_array, int had_pair) {
	if (size_of_array > 2) {
		if ((tile_array[0] == tile_array[1])
				&& (tile_array[1] == tile_array[2]))
			if (tiles_is_winning(tile_array + 3, size_of_array - 3, had_pair))
				return 1;
	}
	return 0;
}

static int tiles_is_winning_remove_a_chow(Tile tile_array[],
		int size_of_array, int had_pair) {
	if (size_of_array > 2) {
		Tile new_tile_array[100];
		int i, cnt = 0;
		Tile first_tile = tile_array[0];
		for (i = 0; i < size_of_array; i++) {
			if (cnt < 3 && tile_array[i] == first_tile + cnt) {
				cnt++;
			} else {
				new_tile_array[i - cnt] = tile_array[i];
			}
		}

		if (cnt == 3)
			if (tiles_is_winning(new_tile_array, size_of_array - 3, had_pair))
				return 1;
	}
	return 0;
}

static int tiles_is_winning_more_than_one_tile(Tile tile_array[],
		int size_of_array, int had_pair) {
	return ((!had_pair && tiles_is_winning_remove_a_pair(tile_array,
			size_of_array)) || tiles_is_winning_remove_a_pong(tile_array,
			size_of_array, had_pair) || tiles_is_winning_remove_a_chow(
			tile_array, size_of_array, had_pair));
}

static int tiles_is_winning(Tile tile_array[], int size_of_array,
		int had_pair) {
	if (size_of_array == 0)
		return 1;

	if (size_of_array == 0)
		return 0;

	return tiles_is_winning_more_than_one_tile(tile_array, size_of_array,
			had_pair);
}

static int tile_compare(const void * t1, const void * t2) {
	return (*((Tile *) t1)) - (*((Tile *) t2));
}

static void tiles_sort(Tile tiles[], int n) {
	int i, cnt = 0;
	for (i = 0; i < n; i++) {
		if (tiles[i] != NO_TILE)
			tiles[cnt++] = tiles[i];
	}
	for (i = cnt; i < n; i++) {
		tiles[i] = NO_TILE;
	}
	qsort(tiles, cnt, sizeof(Tile), tile_compare);

}

bool tiles_plus_one_is_winning(Tile holding[], int n, Tile discard) {
	TileArray ta(holding, n);
	return ta.winWith(discard);
}

TileArray::TileArray(const Tile * tiles, int count) {

	tileCount_ = 0;
	for (int i = 0; i < count; i++)
		if (tiles[i] != NO_TILE)
			tileCount_++;

	tiles_ = new Tile[tileCount_];

	for (int i = 0; i < tileCount_; i++)
		tiles_[i] = tiles[i];

	tiles_sort(tiles_, tileCount_);
}

TileArray::~TileArray() {
	delete[] tiles_;
}


int TileArray::getTileCount() const {
	return tileCount_;
}

bool TileArray::isAbleToPong(Tile tile) const {
	int cnt = 0;
	for (int i = 0; i < tileCount_; i++)
		if (tiles_[i] == tile)
			cnt++;

	return cnt >= 2;

}

bool TileArray::winWith(Tile discard) const {
	Tile * tiles = new Tile[tileCount_ + 1];

	for (int i = 0; i < tileCount_; i++)
		tiles[i] = tiles_[i];
	tiles[tileCount_] = discard;
	tiles_sort(tiles, tileCount_ + 1);

	bool ret = tiles_is_winning(tiles,
			tileCount_ + 1, 0);

	delete[] tiles;

	return ret;
}

bool TileArray::has(Tile tile) const {
	for (int i = 0; i < tileCount_; i++)
		if (tiles_[i] == tile)
			return true;
	return false;
}

void TileArray::remove(Tile tile, int count) {
	int cnt = 0;
	for (int i = 0; i < tileCount_; i++) {
		if (tiles_[i] == tile && cnt < count) {
			tiles_[i] = NO_TILE;
			cnt++;
		}
	}
	tiles_sort(tiles_, tileCount_);
	tileCount_ -= count;
}

void TileArray::replaceOneOf(Tile tile, Tile with) {
	for (int i = 0; i < tileCount_; i++)
		if (tiles_[i] == tile) {
			tiles_[i] = with;
			break;
		}
	tiles_sort(tiles_, tileCount_);
}

const Tile& TileArray::operator[] (int n) const {
	return tiles_[n];
}

bool TileArray::isAbleToChow(Tile tile) const 
{
    if(tileCount_ < 2)
    {
        return false;
    }
    
    if(tile == C(4) && isNotAbleToChowOnTheRight(tile))
    {
        return false;
    }

    if(tile == C(1) && !has(tile.nextTile()))
    {
        return false;
    }

	return true;
}

bool TileArray::isNotAbleToChowOnTheRight(const Tile& tile) const
{
    return !has(previousTile(tile)) || !has(Tile(tile.getID() - 2));
}

Tile TileArray::previousTile(const Tile& tile) const
{
    return Tile(tile.getID() - 1);
}
