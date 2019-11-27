#ifndef DATA_CREATION_HELPERS
#define DATA_CREATION_HELPERS

#include "Hand.h"
#include "Perspective.h"

class DummyUIEvent: public UIEvent {
public:
	virtual ~DummyUIEvent() {
	}
	virtual std::string toString() {
		return "";
	}
};

const Tile WINNING_TILE = 10;
const Tile ANY_TILE = 8;
const Tile defaultTilesPongTheWinningTileAndChowWinningTilePlusOne[] = { WINNING_TILE, WINNING_TILE, WINNING_TILE+2, WINNING_TILE+2 };

constexpr unsigned int max_holding_count = 13;

class HandBuilder {
public:
	HandBuilder(): numberOfTiles_(0){}

	Hand * please() {
		return createHand(tiles_, numberOfTiles_);
	}

	Player * dealToPlease(Player *player, int distance) {
		player->deal(tiles_, numberOfTiles_, distance);
        return player;
	}

	HandBuilder& withTiles(Tile tile) {
		tiles_[numberOfTiles_++] = tile;
		return *this;
	}

    template<typename T, typename... Args>	
	HandBuilder& withTiles(T tile, Args... args) {
        withTiles(tile);
        return withTiles(args...);
	}

	HandBuilder& withAPairOf(Tile tile) {
        return withTiles(tile, tile);
	}

	HandBuilder& withPongOf(Tile tile) {
        return withTiles(tile, tile, tile);
	}

	HandBuilder& withChowFrom(Tile tile) {
        return withTiles(tile, tile+1, tile+2);
	}

private:
	Hand * createHand(Tile * tiles, int count) {
		Hand * hand = new Hand();
		hand->deal(tiles, count);
		return hand;
	}

private:
	Tile tiles_[max_holding_count];
	int numberOfTiles_;
};

class HandDataMother {
public:
	Hand *createAllIrrelevantHand() {
		Tile tiles[] = { 1, 4, 7, 11 };
		return createHand(tiles, 4);
	}

	Hand * createHandWinWithTheWinningTile() {
		Tile tiles[] = {WINNING_TILE};
		return createHand(tiles, 1);
	}

	Hand *createHandPongTheWinningTile() {
		Tile tiles[] = {WINNING_TILE, WINNING_TILE, WINNING_TILE + 3, WINNING_TILE + 6};
		return createHand(tiles, 4);
	}

	Hand * createHandChowTheWinningTile() {
		Tile tiles[] = {WINNING_TILE+1, WINNING_TILE+2, WINNING_TILE + 3, WINNING_TILE + 6};
		return createHand(tiles, 4);
	}

	Hand * createHandPongAndWinTheWinningTile() {
		Tile tiles[] = {WINNING_TILE, WINNING_TILE, WINNING_TILE + 2, WINNING_TILE + 2};
		return createHand(tiles, 4);
	}

private:
	Hand * createHand(Tile * tiles, int count) {
		Hand * hand = new Hand();
		hand->deal(tiles, count);
		return hand;
	}
};
#endif