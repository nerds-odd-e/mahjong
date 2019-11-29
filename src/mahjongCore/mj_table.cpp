#include "Perspective.h"
#include "Hand.h"
#include "Wall.h"
#include "mj_table.h"
#include "Settings.h"

MahjongTable::MahjongTable(Wall *wall, Settings& settings) :
		wall_(wall), player_count_(0), current_player(0), host(0), restartCount_(
				0), currentState_(&endOfGameState_), endOfGameState_(this), pickedState_(
				this), pickingState_(this), settings_(settings) {

}

MahjongTable::~MahjongTable() {
}

Player * MahjongTable::getPlayerOfDistance(int i) {
	return this->players[(this->current_player + i) % this->player_count_];
}

void MahjongTable::addPlayer(Player * player) {
	this->players[this->player_count_++] = player;
}

int MahjongTable::getPlayerCount() {
	return this->player_count_;
}

void MahjongTable::pick(Tile tile) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Player * perspective = getPlayerOfDistance(i);
		perspective->pick(tile, i);
	}
}

void MahjongTable::changeHost() {
	this->host = (this->host + 1) % this->player_count_;
	this->current_player = this->host;
}

void MahjongTable::changeCurrentPlayer(int distance) {
	this->current_player = (this->current_player + distance)
			% this->player_count_;
}

void MahjongTable::win(int score) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Player * perspective = getPlayerOfDistance(i);
		perspective->win(score, i);
	}
	changeHost();
}

void MahjongTable::deal(Tile tiles[], int n) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Player * perspective = getPlayerOfDistance(i);
		perspective->deal(tiles, n, i);
	}
	changeCurrentPlayer(1);
}

void MahjongTable::throw_tile(Tile tile) {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Player * perspective = getPlayerOfDistance(i);
		perspective->discard(tile, i);
	}
	this->last_tile = tile;
	changeCurrentPlayer(1);
}

void MahjongTable::pong() {
	int i = 0;
	for (i = 0; i < this->player_count_; i++) {
		Player * perspective = getPlayerOfDistance(i);
		perspective->pong(this->last_tile, i);
	}
}

int MahjongTable::chow(Tile with) {
	Player * perspective = getPlayerOfDistance(0);
	if (!perspective->chow(last_tile, with, 0))
		return 0;
	for (int i = 1; i < player_count_; i++) {
		perspective = getPlayerOfDistance(i);
		perspective->chow(last_tile, with, i);
	}
	return 1;
}

void MahjongTable::restartGame() {
	wall_->shuffleAndRebuild(settings_.GetNumberOfSuites());
	Tile tiles[settings_.GetHandSize()];
	int cnt = getPlayerCount();
	for (; cnt > 0; cnt--) {

		for (int i = 0; i < settings_.GetHandSize(); i++) {
			tiles[i] = wall_->popATile();
		}
		if (settings_.GetGameLevel().GetLevel() == 1) {
			auto target_tile{tiles[0]};
			Tile found_tile{};
			auto i{1};
			while(found_tile != target_tile)
			{
				if (wall_->peekTile(i) == target_tile)
				{
					found_tile = wall_->peekTile(i);
				}
				++i;
			}
      		wall_->swap(1, i);
        }
		deal(tiles, settings_.GetHandSize());
	}
//	pick(wall_->popATile());
    currentState_ = &pickingState_;
}

void MahjongTable::restartGameWhenAllPlayersAreReady() {
	changeCurrentPlayer(1);
	if (++restartCount_ == player_count_) {
		restartCount_ = 0;
		restartGame();
	}
}

void MahjongTable::discard(Tile& action_tile) {
	throw_tile(action_tile);
	if (wall_->isEnd()) {
		win(0);
		currentState_ = &endOfGameState_;
	} else {
		currentState_ = &pickingState_;
	}
}

void MahjongTable::doWin() {
	win(1);
	currentState_ = &endOfGameState_;
}

void MahjongTable::doPick() {
	pick(wall_->popATile());
	currentState_ = &pickedState_;
}

void MahjongTable::doPong() {
	pong();
	currentState_ = &pickedState_;
}

void MahjongTable::doChow(Tile action_tile) {
	if (chow(action_tile)) {
		currentState_ = &pickedState_;
	}
}

PlayerActionRequest MahjongTable::popActionRequest() {
	Player* perspective = getPlayerOfDistance(0);
	return perspective->takeActionRequest();
}

void MahjongTable::nextMove() {
	while (true) {
		PlayerActionRequest actionRequest = popActionRequest();
		if (!actionRequest.hasAction())
			break;
		actionRequest.doPlayerAction(currentState_);
	}
}

int MahjongTable::getWinForCurrentPlayer() const
{ 
	return 1;
}
