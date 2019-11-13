#ifndef TILE_H_
#define TILE_H_

#ifndef NULL
#define NULL 0
#endif

#define UNUSED(x) (void)(x)

#define MAX_NUMBER_OF_PLAYER 4

#define	NO_TILE  Tile(0)
#define MJ_CHARACTOR_BASE  '0'
#define MJ_CIRCLE_BASE  '@'
#define MJ_BAMBOO_BASE  '`'
#define MJ_EAST  Tile(MJ_BAMBOO_BASE+12)
#define MJ_SOUTH  Tile(MJ_BAMBOO_BASE+15)
#define MJ_WEST  Tile(MJ_BAMBOO_BASE+18)
#define MJ_NORTH  Tile(MJ_BAMBOO_BASE+21)
#define MJ_ZHONG  Tile(MJ_BAMBOO_BASE+24)
#define MJ_FA  Tile(MJ_BAMBOO_BASE+27)
#define MJ_BAI  Tile(MJ_BAMBOO_BASE+30)

class Tile{
public:
	Tile() {}
	Tile(char tileNumber) : tileNumber_(tileNumber){}
	Tile(const Tile& tile) : tileNumber_(tile.tileNumber_){}

	Tile nextTile() {
		return Tile(tileNumber_+ 1);
	}

    Tile previousTile() {
        return Tile(tileNumber_ - 1);
    }

    Tile& operator = (const Tile& tile) {
		tileNumber_ = tile.tileNumber_;
		return *this;
	}

	Tile operator + (int number) const{
		Tile tile;
		tile.tileNumber_ = tileNumber_+ (char)number;
		return tile;
	}

	int operator - (const Tile& tile) const {
		return tileNumber_ - tile.tileNumber_;
	}

	bool operator== (const Tile& tile) const {
		return tileNumber_ == tile.tileNumber_;
	}

	bool operator!= (const Tile& tile) const {
		return tileNumber_ != tile.tileNumber_;
	}

	bool operator < (const Tile& tile) const {
		return tileNumber_ < tile.tileNumber_;
	}

	bool operator > (const Tile& tile) const {
		return tileNumber_ > tile.tileNumber_;
	}

	operator const char *() const;

	int getID() const{
		return tileNumber_;
	}

private:
	char tileNumber_;
};

#define MJ_CHARACTOR(n)    ((Tile)(MJ_CHARACTOR_BASE + (n)))
#define C MJ_CHARACTOR
#define MJ_CIRCLE(n)    ((Tile)(MJ_CIRCLE_BASE + (n)))
#define R MJ_CIRCLE
#define MJ_BAMBOO(n)    ((Tile)(MJ_BAMBOO_BASE + (n)))
#define B MJ_BAMBOO

typedef int Meld;
#define PONG(tile)  (0x80 | (tile.getID()))
#define CHOW(lowestTile)  (0x100 | (lowestTile.getID()))

#endif /* TILE_H_ */
