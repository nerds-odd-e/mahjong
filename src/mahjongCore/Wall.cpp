#include <stdlib.h>

#include "Wall.h"
#include "Settings.h"
#include "GameLevel.h"
#include <algorithm>

constexpr int SHUFFLE_TIMES = 1000;

/*
 * SIMPLIFIED_MAHJONG is for people who cannot read Chinese.
 */
#ifndef SIMPLIFIED_MAHJONG
static const std::vector<Tile> all_tile_types = { C(1), C(2), C(3), C(4), C(5), C(6), C(7),
		C(8), C(9), R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9), MJ_EAST,
		MJ_SOUTH, MJ_WEST, MJ_NORTH, MJ_ZHONG, MJ_FA, MJ_BAI };

static const std::vector<Tile> character_tile_types = { C(1), C(2), C(3), C(4), C(5), C(6), C(7), C(8), C(9)};
static const std::vector<Tile> circle_tile_types = {  R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9)};
static const std::vector<Tile> bamboo_tile_types = { B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9)};

static const std::vector<std::vector<Tile>> tile_suits = {circle_tile_types, bamboo_tile_types};
#else
static const std::vector<Tile> all_types = {R(1), R(2), R(3), R(4), R(5), R(6), R(7), R(8), R(9),
		B(1), B(2), B(3), B(4), B(5), B(6), B(7), B(8), B(9)};
#endif

const int TILE_TYPE_COUNT = all_tile_types.size();

const int TILES_PER_TYPE = 4;

static Wall * create_wall_impl() {
	return new Wall(all_tile_types, 70);
}

Wall * (*createWall)() = create_wall_impl;

Wall::Wall(const std::vector<Tile>& tileTypes, int maxPicks) :
	tileTypes_(tileTypes), maxPicks_(maxPicks), shuffleTimes_(SHUFFLE_TIMES){
	initializePool();
}

void Wall::initializePool(const unsigned int suitCount) {
	int cnt = 0;

	applySettings(suitCount);
	
	for (int j = 0; j < TILES_PER_TYPE; j++)
		for (Tile& tile : tileTypes_)
			this->tilePool_[cnt++] = tile;

	this->picksCount_ = 0;
}

void Wall::applySettings(const unsigned int suitCount)
{
	if(suitCount == 1)
	{
		suitIndex_ %= 2;
		tileTypes_ = tile_suits[suitIndex_++];
	}
}

int Wall::randomIndex() {
	return rand() % getAllCount();
}

int Wall::getAllCount() {
	return tileTypes_.size() * TILES_PER_TYPE;
}

void Wall::swap(int index1, int index2) {
	Tile temp = this->tilePool_[index1];
	this->tilePool_[index1] = this->tilePool_[index2];
	this->tilePool_[index2] = temp;
}

void Wall::shuffleAndRebuild(const unsigned int suitCount) {
	initializePool(suitCount);

	for (int i = 0; i < shuffleTimes_; i++)
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

Tile Wall::peekTile(int index){
	return tilePool_[index];
}

void Wall::setShuffleTimes(int 	shuffleTimes){
	shuffleTimes_=shuffleTimes;
}

void Wall::GeneratePredefinedHand(const HandGenerationRule rule) {
  switch (rule) {
  case HandGenerationRule::LEVEL_1_RULE_1:
    GenerateTwoPairs();
    break;
  case HandGenerationRule::LEVEL_1_RULE_2:
    GenerateATriplet();
    break;
  case HandGenerationRule::LEVEL_1_RULE_3:
    GenerateAPair();
    break;
  }
}

void Wall::SwapForTheSameTile(Tile tile, int index)
{
  auto target_tile{tile};
  auto i{index};
  std::find_if(std::begin(tilePool_) + i, std::end(tilePool_),
               [target_tile, &i](const Tile t) {
                 ++i;
                 return target_tile.getID() == t.getID();
               });
  swap(index, i - 1);
}

void Wall::SwapForADifferentTile(Tile tile, int index)
{
  auto target_tile{tile};
  auto i{index};
  std::find_if(std::begin(tilePool_) + i, std::end(tilePool_),
               [target_tile, &i](const Tile t) {
                 ++i;
                 return target_tile.getID() != t.getID();
               });
  swap(index, i - 1);
}

void Wall::GenerateTwoPairs()
{
  SwapForTheSameTile(tilePool_[0], 1);
  SwapForADifferentTile(tilePool_[1], 2);
  SwapForTheSameTile(tilePool_[2], 3);
}

void Wall::GenerateATriplet()
{
  SwapForTheSameTile(tilePool_[0], 1);
  SwapForTheSameTile(tilePool_[0], 2);
  SwapForADifferentTile(tilePool_[0], 3);
}

void Wall::GenerateAPair()
{
  SwapForTheSameTile(tilePool_[0], 1);
  auto i{2};
  auto target_tile{tilePool_[1]};
  std::find_if(std::begin(tilePool_) + i, std::end(tilePool_),
               [target_tile, &i](const Tile t) {
                 ++i;
                 return target_tile.getID() != t.getID();
               });
  swap(2, i - 1);
  i = 3;
  target_tile = tilePool_[2];
  auto target_tile_{tilePool_[1]};
  std::find_if(std::begin(tilePool_) + i, std::end(tilePool_),
               [target_tile, target_tile_, &i](const Tile t) {
                 ++i;
                 return target_tile.getID() != t.getID() &&
                        target_tile_.getID() != t.getID();
               });
  swap(3, i - 1);
}
