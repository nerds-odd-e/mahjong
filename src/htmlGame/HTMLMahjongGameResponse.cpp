#include "HTMLMahjongGameResponse.h"
#include "game.h"
#include "UserPerspective.h"
#include "Hand.h"
#include "string.h"
#include "stdio.h"

void HTMLMahjongGameResponse::newGame(GameID gameID) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	snprintf(buffer, buffer_size, "{\"game_id\":%d}", gameID);
	content_ = buffer;
}

void HTMLMahjongGameResponse::bye() {
}

const char * HTMLMahjongGameResponse::getString() {
	return content_.c_str();
}

void HTMLMahjongGameResponse::shutdown() {
	content_ = "<HTML><BODY>shutdown!</BODY></HTML>";
}

void HTMLMahjongGameResponse::gameDoesNotExist() {
	content_ = "alert('Game does not exist. Restart, please.');";
}

class TileArrayScriptGenerator {
public:
	const char * getTilesArrayString(UserView * view, char buffer[], int buffer_size);
private:
	void catTilesToString(char buffer[], const Tile * tiles, int n);
	void catmeldToString(char buffer[], const Meld * meld, int n);
	void catPlayerTilesToString(Hand * player, char buffer[], int buffer_size);
};

void HTMLMahjongGameResponse::currentGameStatus(UserView * view) {
	const int buffer_size = 1024;
	char tmp[buffer_size];
	TileArrayScriptGenerator().getTilesArrayString(view, tmp, buffer_size);
	content_ = tmp;
}

void HTMLMahjongGameResponse::popAction(UserView * view) {
	UIEvent *event = view->popEvent();
	if (event == NULL) {
		content_ = "App.noop();";
		return;
	}
	content_ = event->toString();
	delete event;
}

void HTMLMahjongGameResponse::clear() {
	content_ = "";
}

void TileArrayScriptGenerator::catTilesToString(char buffer[], const Tile * tiles, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", tiles[i].getID());
		strcat(buffer, tmp_tile);
	}
}

void TileArrayScriptGenerator::catmeldToString(char buffer[], const Meld * meld, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", meld[i]);
		strcat(buffer, tmp_tile);
	}
}

void TileArrayScriptGenerator::catPlayerTilesToString(Hand * player, char buffer[],
		int buffer_size) {
	strcat(buffer, ",\"hand\":[");
	Tile tiles[MAX_HOLDING_COUNT];
	Meld meld[MAX_MELD_COUNT];
	int n = player->getHoldings(tiles, MAX_HOLDING_COUNT);
	catTilesToString(buffer, tiles, n);
	int len = strlen(buffer);
	if (buffer[len - 1] == ',') {
		buffer[len - 1] = '\0';
	}
	strcat(buffer, "]");

	strcat(buffer, ",\"new_pick\":");
	tiles[0] = player->getCurrentTileAtHand();
	catTilesToString(buffer, tiles, 1);

	strcat(buffer, "\"melds\":[");
	n = player->getMelds(meld, MAX_MELD_COUNT);
	catmeldToString(buffer, meld, n);

	len = strlen(buffer);
	if (buffer[len - 1] == ',') {
		buffer[len - 1] = '\0';
	}
	strcat(buffer, "]");
}

const char * TileArrayScriptGenerator::getTilesArrayString(UserView * view,
		char buffer[], int buffer_size) {
    char tmp[100];
	sprintf(buffer, "[");
	int count = view->getNumberOfPlayer();
	for (int i = 0; i < count; i++) {
		Hand *data = view->getHand(i);
		if (i)
			strcat(buffer, ",");
		strcat(buffer, "{\"player_index\":");
		sprintf(tmp, "%d", i);
		strcat(buffer, tmp);
		catPlayerTilesToString(data, buffer, buffer_size);
		strcat(buffer, "}");
	}
	strcat(buffer, "]");
	return buffer;
}
