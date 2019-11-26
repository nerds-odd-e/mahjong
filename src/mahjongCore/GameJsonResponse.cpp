#include "GameJsonResponse.h"
#include "game.h"
#include "UserPerspective.h"
#include "Hand.h"
#include "string.h"
#include "stdio.h"
#include "configuration.h"

void GameJsonResponse::newGame(GameID gameID) {
	const int buffer_size = 1000;
	char buffer[buffer_size];
	snprintf(buffer, buffer_size, "{\"game_id\":%d}", gameID);
	content_ = buffer;
}

void GameJsonResponse::bye() {
}
	
const char * GameJsonResponse::getString() {
	if (content_.empty())
		return "{}";
	return content_.c_str();
}

void GameJsonResponse::shutdown() {
	UIEvent * event = UIEventFactory().createMessageEvent("shutting down...");
	content_ = event->toString();
	delete event;
}

void GameJsonResponse::gameDoesNotExist() {
	UIEvent * event = UIEventFactory().createMessageEvent("Game does not exist. Restart, please.");
	content_ = event->toString();
	delete event;
}

void GameJsonResponse::setContent(std::string content)
{
	this->content_ = content;
}

class GameStatusJSONGenerator {
public:
	const char * getCurrentStatus(UserView * view, char buffer[], int buffer_size);
private:
	void catTilesToString(char buffer[], const Tile * tiles, int n);
	void catmeldToString(char buffer[], const Meld * meld, int n);
	void catPlayerTilesToString(Hand * player, char buffer[], int buffer_size);
	void catPlayerAllowedActionsToString(UserView * userView, char buffer[], int buffer_size);

};

void GameJsonResponse::currentGameStatus(UserView * view) {
	const int buffer_size = 1024;
	char tmp[buffer_size];
	GameStatusJSONGenerator().getCurrentStatus(view, tmp, buffer_size);
	content_ = tmp;
}

void GameJsonResponse::popAction(UserView * view) {
	UIEvent *event = view->popEvent();
	if (event == NULL) {
		content_ = "{\"action\":\"your_turn\"}";
		return;
	}
	content_ = event->toString();
	delete event;
}

void GameJsonResponse::clear() {
	content_ = "";
}

void GameStatusJSONGenerator::catTilesToString(char buffer[], const Tile * tiles, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", tiles[i].getID());
		strcat(buffer, tmp_tile);
	}
}

void GameStatusJSONGenerator::catmeldToString(char buffer[], const Meld * meld, int n) {
	char tmp_tile[100];
	int i = 0;
	for (i = 0; i < n; i++) {
		sprintf(tmp_tile, "%d,", meld[i]);
		strcat(buffer, tmp_tile);
	}
}

void GameStatusJSONGenerator::catPlayerTilesToString(Hand * player, char buffer[],
		int buffer_size) {
	strcat(buffer, ",\"hand\":[");
	Tile tiles[MAX_HOLDING_COUNT];
	Meld meld[MAX_MELD_COUNT];
	int n = player->getHoldings(tiles, Configuration::getInstance().GetMaxHoldingCount());
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
	n = player->getMelds(meld, Configuration::getInstance().GetMaxMeldCount());
	catmeldToString(buffer, meld, n);

	len = strlen(buffer);
	if (buffer[len - 1] == ',') {
		buffer[len - 1] = '\0';
	}
	strcat(buffer, "]");
}

void GameStatusJSONGenerator::catPlayerAllowedActionsToString(UserView * view, char buffer[],
		int buffer_size) {
	strcat(buffer, "\"allowed_actions\":[");
	bool first = true;
    if (view->getHand(0)->isAbleToWin(view->getCurrentDiscardTile())) {
		if (first)
			first = false;
		else
			strcat(buffer, ",");
		strcat(buffer, "\"win\"");
	}
    if (view->getHand(0)->isAbleToPong(view->getCurrentDiscardTile())) {
		if (first)
			first = false;
		else
			strcat(buffer, ",");
		strcat(buffer, "\"pong\"");
	}
    if (view->getHand(0)->isAbleToChow(view->getCurrentDiscardTile())) {
		if (first)
			first = false;
		else
			strcat(buffer, ",");
		strcat(buffer, "\"chow\"");
	}

	strcat(buffer, "]");
}

const char * GameStatusJSONGenerator::getCurrentStatus(UserView * view,
		char buffer[], int buffer_size) {
    char tmp[100];
	sprintf(buffer, "{\"players\":[");
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
	strcat(buffer, "],");
	catPlayerAllowedActionsToString(view, buffer, buffer_size);
	strcat(buffer, "}");
	return buffer;
}
