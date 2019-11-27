#include "Hand.h"
#include "memory.h"
#include <stdlib.h>
#include "Perspective.h"

Hand::~Hand() {
	delete tileArray_;
}

Hand::Hand() : tileArray_(NULL){
	int i;
	current_ = NO_TILE;
	for (i = 0; i < max_meld_count; i++) {
		melds_[i] = 0;
	}
}

void Hand::pick(Tile tile) {
	this->current_ = tile;
}

int Hand::isAbleToWin(Tile discard) const {
	if (discard == NO_TILE)
		discard = this->current_;
	return tileArray_->winWith(discard);
}

int Hand::getHoldings(Tile * tiles_buffer, int buffer_size) const {
	if (tileArray_ == NULL)
		return 0;

	int tileCount = tileArray_->getTileCount();
	for (int i = 0; i < tileCount && i < buffer_size; i++)
		tiles_buffer[i] = (*tileArray_)[i];
	return tileCount;
}

int Hand::getMelds(Meld * tiles_buffer, int buffer_size) const {
	int tile_count = 0;
	for (; tile_count < max_meld_count; tile_count++) {
		if (this->melds_[tile_count])
			tiles_buffer[tile_count] = this->melds_[tile_count];
		else
			break;
	}
	return tile_count;
}

Tile Hand::getCurrentTileAtHand() const {
	return this->current_;
}

void Hand::deal(const Tile tiles[], int buffer_size) {
	delete tileArray_;
	tileArray_ = new TileArray(tiles, buffer_size);

	for (int i = 0; i < max_meld_count; i++)
		this->melds_[i] = 0;
}

Tile Hand::discard(Tile tile) {
	if (tile != this->current_)
		tileArray_->replaceOneOf(tile, this->current_);
	this->current_ = NO_TILE;

	return tile;
}
int Hand::isAbleToPong(Tile tile) const {
	return tileArray_->isAbleToPong(tile);
}

int Hand::isAbleToChow(Tile tile) const {
	return tileArray_->isAbleToChow(tile);
}

void Hand::rearrangeAfterMeld(Meld meld) {
	int i;

	int cnt = tileArray_->getTileCount();
	this->current_ = (*tileArray_)[cnt - 1];
	tileArray_->remove(current_, 1);

	for (i = 0; i < max_meld_count; i++) {
		if (this->melds_[i] == 0)
			break;
	}
	this->melds_[i] = meld;
}

void Hand::pong(Tile tile) {
	tileArray_->remove(tile, 2);
	rearrangeAfterMeld(PONG(tile));
}

bool Hand::isAbleToChowWithSmallest(Tile tile, Tile smallest) const
{
	for (int i = 0; i < 3; i++)
		if (tile != smallest + i)
			if (!tileArray_->has(smallest + i))
				return false;
	return true;
}
void Hand::_chow(Tile tile, Tile smallest)
{
	for (int i = 0; i < 3; i++)
		if (tile != smallest + i) {
			tileArray_->remove(smallest + i, 1);
		}

	rearrangeAfterMeld(CHOW(smallest));
}

bool Hand::chow(Tile tile, Tile with) {
	Tile smallest = tile < with ? tile : with;
	if (!isAbleToChowWithSmallest(tile, smallest))
		return false;
	_chow(tile, smallest);
	return true;
}

Hand * createHand() {
	return new Hand;
}
