#include <iostream>
#include <list>
#include <map>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Hand.h"
#include "UserPerspective.h"
#include "Wall.h"
#include "mj_table.h"
#include "mocks.h"

constexpr int MAX_HAND_SIZE = 13;

TEST_GROUP(MahjongTable) {
  Settings settings;
  Wall *wall_;
  UserPerspective *userPerspective;
  MahjongTable *table_;
  Tile tiles[MAX_HAND_SIZE];
  int handSize;

  void setup() {
    wall_ = createWall();
    userPerspective = new UserPerspective(settings);
    table_ = new MahjongTable(wall_, settings);
    handSize = 0;
    table_->addPlayer(userPerspective);
  }

  void teardown() {
    delete table_;
    delete userPerspective;
    delete wall_;
  }

  void StartGame() {
    table_->restartGame();
    Hand *hand = userPerspective->getHand(0);
    handSize = hand->getHoldings(tiles, MAX_HAND_SIZE);
  }
};

TEST(MahjongTable, it_must_have_1_tiles_when_the_level_is_0) {

  StartGame();
  CHECK_EQUAL(1, handSize);
}

TEST(MahjongTable, it_must_have_4_tiles_when_the_level_is_1) {
  settings.GetGameLevel().IncrementLevel();
  StartGame();
  CHECK_EQUAL(4, handSize);
}

TEST(MahjongTable, level_1_sublevel_3_player_draws_a_pair_and_two_randoms) {
  settings.GetGameLevel().IncrementLevel();
  settings.GetGameLevel().IncrementSubLevel();
  settings.GetGameLevel().IncrementSubLevel();
  wall_->setShuffleTimes(0);
  StartGame();

  std::list<Tile> tilesList(std::begin(tiles), std::begin(tiles) + handSize);
  tilesList.unique();

  CHECK(tilesList.size() < handSize);
}

TEST(MahjongTable, test_wall_consistency_on_level_1) {
  constexpr auto COUNT_OF_TILES_IN_SUITE{36};
  constexpr auto COUNT_OF_TILES_PER_TYPE{4};
  wall_->setShuffleTimes(0);
  settings.GetGameLevel().IncrementLevel();
  settings.GetGameLevel().IncrementSubLevel();
  settings.GetGameLevel().IncrementSubLevel();

  StartGame();

  std::map<Tile, int> count_tiles;
  for (auto i = 0; i < handSize; ++i) {
    Tile t = tiles[i];
    auto te = count_tiles.find(t);
    if (te != count_tiles.end()) {
      te->second++;
    } else {
      count_tiles[t] = 1;
    }
  }
  for (int i = handSize; i < COUNT_OF_TILES_IN_SUITE; ++i) {
    Tile t = wall_->peekTile(i);
    auto te = count_tiles.find(t);
    if (te != count_tiles.end()) {
      te->second++;
    } else {
      count_tiles[t] = 1;
    }
  }
  for (auto e : count_tiles) {
    CHECK_EQUAL(COUNT_OF_TILES_PER_TYPE, e.second);
  }
}