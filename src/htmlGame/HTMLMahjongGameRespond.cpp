#include "HTMLMahjongGameRespond.h"
#include "game.h"
#include "UserPerspective.h"
#include "Hand.h"
#include "string.h"
#include "stdio.h"

const char * html_frame =
		"<html>\n"
				"<head>\n"
				"<title>Mahjong Game - For Writing Effective Unit Test Training</title> "
				"<script>game_id=%d;</script>\n"
				"<LINK REL=StyleSheet HREF=\"mj.css\" TYPE=\"text/css\">\n"
				"<script src=\"mj.js\" type=\"text/javascript\"></script>\n"
				"</head>\n"
				"<body>\n"
				"</body>\n"
				"</html>\n";

void HTMLMahjongGameRespond::newGame(GameID gameID) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	snprintf(buffer, buffer_size, html_frame, gameID);
	content_ = buffer;
}

void HTMLMahjongGameRespond::bye() {
}

const char * HTMLMahjongGameRespond::getString() {
	return content_.c_str();
}

void HTMLMahjongGameRespond::shutdown() {
	content_ = "<HTML><BODY>shutdown!</BODY></HTML>";
}

void HTMLMahjongGameRespond::gameDoesNotExist() {
	content_ = "alert('Game does not exist. Restart, please.');";
}

class TileArrayScriptGenerator {
public:
	const char * getTilesArrayString(UserView * view, char buffer[], int buffer_size);
private:
	void catTilesToString(char buffer[], const tile_t * tiles, int n);
	void catEatenToString(char buffer[], const eaten_t * eaten, int n);
	void catPlayerTilesToString(Hand * player, char buffer[], int buffer_size);
};

void HTMLMahjongGameRespond::updateAllHoldings(UserView * view) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	char tmp[buffer_size] = "";
	TileArrayScriptGenerator script;
	script.getTilesArrayString(view, tmp, buffer_size);
	snprintf(buffer, buffer_size, "App.UpdateHolding(%s);", tmp);
	content_ += buffer;
}

void HTMLMahjongGameRespond::updateUIEvent(UserView * view) {
	UIEvent *event;
	while ((event = view->popEvent()) != NULL) {
		content_ += event->toString();
		delete event;
	}
}

void HTMLMahjongGameRespond::clear() {
	content_ = "";
}

void TileArrayScriptGenerator::catTilesToString(char buffer[], const tile_t * tiles, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", tiles[i]);
		strcat(buffer, tmp_tile);
	}
}

void TileArrayScriptGenerator::catEatenToString(char buffer[], const eaten_t * eaten, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", eaten[i]);
		strcat(buffer, tmp_tile);
	}
}

void TileArrayScriptGenerator::catPlayerTilesToString(Hand * player, char buffer[],
		int buffer_size) {
	strcat(buffer, "[");
	tile_t tiles[MAX_HOLDING_COUNT];
	eaten_t eaten[MAX_EATEN_COUNT];
	int n = player->get_holdings(tiles, MAX_HOLDING_COUNT);
	catTilesToString(buffer, tiles, n);
	tiles[0] = player->get_current();
	catTilesToString(buffer, tiles, 1);
	n = player->get_eaten(eaten, MAX_EATEN_COUNT);
	catEatenToString(buffer, eaten, n);
	int len = strlen(buffer);
	if (buffer[len - 1] == ',') {
		buffer[len - 1] = '\0';
	}
	strcat(buffer, "]");
}

const char * TileArrayScriptGenerator::getTilesArrayString(UserView * view,
		char buffer[], int buffer_size) {
	sprintf(buffer, "[");
	int count = view->getNumberOfPlayer();
	for (int i = 0; i < count; i++) {
		Hand *data = view->getHand(i);
		if (i)
			strcat(buffer, ",");
		catPlayerTilesToString(data, buffer, buffer_size);
	}
	strcat(buffer, "]");
	return buffer;
}
