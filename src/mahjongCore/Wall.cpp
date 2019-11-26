#include <stdlib.h>
#include "Wall.h"

#define SHUFFLE_TIMES 1000

/*
 * SIMPLIFIED_MAHJONG is for people who cannot read Chinese.
 */
#ifndef SIMPLIFIED_MAHJONG
static const Tile all_tile_types[] = { C(1), C(2), C(3), C(4), C(5), C(6), C(7),
		C(8), C(9), R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9), MJ_EAST,
		MJ_SOUTH, MJ_WEST, MJ_NORTH, MJ_ZHONG, MJ_FA, MJ_BAI };

static const Tile circle_tile_types[] = { C(1), C(2), C(3), C(4), C(5), C(6), C(7), C(8), C(9)};
static const Tile character_tile_types[] = {  R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9)};
static const Tile bamboo_tile_types[] = { B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9)};

#else
static const Tile all_types[] = {R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9)};
#endif

const int TILE_TYPE_COUNT = sizeof(all_tile_types)/sizeof(all_tile_types[0]);

const int TILES_PER_TYPE = 4;

static Wall * create_wall_impl() {
	return new Wall(all_tile_types, TILE_TYPE_COUNT, 70);
}

Wall * (*createWall)() = create_wall_impl;

Wall::Wall(const Tile * tileTypes, int tileTypeCount, int maxPicks) :
	tileTypes_(tileTypes), tileTypeCount_(tileTypeCount), maxPicks_(maxPicks){
	initializePool();
}

void Wall::initializePool() {
	int cnt = 0;

	for (int j = 0; j < TILES_PER_TYPE; j++)
		for (int i = 0; i < tileTypeCount_; i++)
			this->tilePool_[cnt++] = tileTypes_[i];

	this->picksCount_ = 0;
}

int Wall::randomIndex() {
	return rand() % getAllCount();
}

int Wall::getAllCount() {
	return tileTypeCount_ * TILES_PER_TYPE;
}

void Wall::swap(int index1, int index2) {
	Tile temp = this->tilePool_[index1];
	this->tilePool_[index1] = this->tilePool_[index2];
	this->tilePool_[index2] = temp;
}

void Wall::shuffleAndRebuild() {
	initializePool();

	for (int i = 0; i < SHUFFLE_TIMES; i++)
		swap(randomIndex(), randomIndex());
}

Tile Wall::popATile() {
	return tilePool_[picksCount_++];
}

Wall::~Wall() {
}

bool Wall::isEnd() {
	return this->picksCount_ >= maxPicks_ || this->picksCount_ == getAllCount();
}


void Wall::changeFirstTileTo(Tile tile){
	tilePool_[picksCount_] = tile;
}

