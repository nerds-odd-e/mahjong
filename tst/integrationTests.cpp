#undef new
#include <map>
#include "CppUTest/MemoryLeakDetectorNewMacros.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "HTMLMahjongGame.h"
#include "MahjongGameServer.h"
#include "Wall.h"
#include "TileArray.h"
#include "EvaluatorAdaptor.h"

namespace {

const int BIGGER_BUFFER_SIZE = 1000;

}

EvaluatorAdaptor * createSimpleEvaluator();
void setCheapestTileForSimpleEvaluator(Tile tile);

#include "mocks.h"

class EverIncreasingWall: public Wall {
public:
	EverIncreasingWall() :
			Wall(NULL, 0, 0), currentTile_(1), wallEnd_(false) {
	}

	Tile popATile() {
		Tile tileToReturn = currentTile_;
		currentTile_ = currentTile_.nextTile();
		return tileToReturn;
	}

	bool isEnd() {
		return wallEnd_;
	}

	void empty() {
		wallEnd_ = true;
	}

	void shuffleAndRebuild() {
	}

	void setCurrentTile(int t) {
		currentTile_ = t;
	}
private:
	Tile currentTile_;
	bool wallEnd_;
}*lastCreatedEverIncreasingWall = NULL;

static Wall * createEverIncreasingWall(const Settings& settings) {
	lastCreatedEverIncreasingWall = new EverIncreasingWall;
	return lastCreatedEverIncreasingWall;
}

TEST_GROUP(html_game) {

	int gameID;
	HTMLMahjongGame *game;
	MahjongGameServer *server;
	EverIncreasingWall *wall;
	char bigBuffer_[BIGGER_BUFFER_SIZE];

	void setup() {
		server = new MahjongGameServer();
		server->IncrementLevel();
		game = new HTMLMahjongGame(server);
		UT_PTR_SET(createEvaluatorAdaptor, createSimpleEvaluator);
		UT_PTR_SET(createWallSetting, createEverIncreasingWall);
		execute_cmd("/join");
		gameID = server->getLastGameID();
		wall = lastCreatedEverIncreasingWall;
		execute_game_cmd("/start", 0);
        execute_game_cmd("/pick", 0);
	}

	void teardown() {
		delete game;
		delete server;
	}

	void execute_cmd(const char * cmd) {
		game->callback(cmd, 0, bigBuffer_,
				BIGGER_BUFFER_SIZE);
	}

	void execute_game_cmd(const char * cmd, int tile) {
		static char temp[100];
		static char tile_str[10];
		sprintf(tile_str, "%d", tile);
		sprintf(temp, "/%d%s", gameID, cmd);
		game->callback(temp, tile_str, bigBuffer_,
				BIGGER_BUFFER_SIZE);
	}

	void get_next_event_until_it_is_my_turn() {
		int count = 0;
		do {
			execute_game_cmd("/next_event", 0);
			count++;
		} while(count < 10 && strcmp(LastResponse(), "{\"action\":\"your_turn\"}") != 0);
		CHECK_TRUE_TEXT(count < 10, "getting next action 10 time and still not your turn");
	}

	const char * LastResponse() {
		return bigBuffer_;
	}
};

TEST(html_game, start) {
    STRCMP_EQUAL( "{\"action\":\"pick\", \"player\":0,\"tile\":27}", LastResponse());
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"your_turn\"}", LastResponse());
}

TEST(html_game, get_current_status) {
	execute_game_cmd("/current", 0);
	STRCMP_EQUAL(
			"{"
				"\"players\":["
					"{\"player_index\":0,\"hand\":[1,2,3,4,5,6,7,8,9,10,11,12,13],\"new_pick\":27,\"melds\":[]},"
					"{\"player_index\":1,\"hand\":[14,15,16,17,18,19,20,21,22,23,24,25,26],\"new_pick\":0,\"melds\":[]}"
				"],"
				"\"allowed_actions\":[\"chow\"]"
			"}",
			LastResponse());
}

TEST(html_game, a_game) {
	get_next_event_until_it_is_my_turn();
	execute_game_cmd("/throw", 1);
	STRCMP_CONTAINS("{\"action\":\"discard\", \"player\":0,\"tile\":1}", LastResponse());
	execute_game_cmd("/next_event", 0);
	STRCMP_CONTAINS("{\"action\":\"pick\", \"player\":1,\"tile\":28}", LastResponse());
	execute_game_cmd("/next_event", 0);
	STRCMP_CONTAINS("{\"action\":\"discard\", \"player\":1,\"tile\":14}", LastResponse());
	setCheapestTileForSimpleEvaluator(28);
	wall->setCurrentTile(27);
	execute_game_cmd("/pick", 0);
	STRCMP_EQUAL( "{\"action\":\"pick\", \"player\":0,\"tile\":27}", LastResponse());
	execute_game_cmd("/current", 0);
	STRCMP_CONTAINS("\"allowed_actions\":[\"win\"", LastResponse());
	execute_game_cmd("/win", 0);
	STRCMP_EQUAL("{\"action\":\"win\", \"player\":0,\"score\":1}", LastResponse());
	wall->setCurrentTile(1);
	setCheapestTileForSimpleEvaluator(27);
	execute_game_cmd("/start", 0);
	STRCMP_EQUAL( "{\"action\":\"update_all\"}", LastResponse());
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"pick\", \"player\":1,\"tile\":27}", LastResponse());
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"discard\", \"player\":1,\"tile\":27}", LastResponse());
}

TEST(html_game, no_tile_any_more) {
	execute_game_cmd("/next_event", 0);
	wall->empty();
	execute_game_cmd("/throw", 1);
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"win\", \"player\":1,\"score\":0}", LastResponse());
	setCheapestTileForSimpleEvaluator(54);
	execute_game_cmd("/start", 0);
    STRCMP_EQUAL( "{\"action\":\"update_all\"}", LastResponse());
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"pick\", \"player\":1,\"tile\":54}", LastResponse());
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL("{\"action\":\"win\", \"player\":0,\"score\":0}", LastResponse());
	execute_game_cmd("/start", 0);
	STRCMP_EQUAL( "{\"action\":\"update_all\"}", LastResponse());
}

TEST(html_game, _WIN) {
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/win", 1);
	STRCMP_EQUAL("{\"action\":\"message\", \"content\":\"Are you kidding?\"}", LastResponse());
	execute_game_cmd("/throw", 1);
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"pick\", \"player\":1,\"tile\":28}", LastResponse());
	execute_game_cmd("/next_event", 0);
	setCheapestTileForSimpleEvaluator(28);
	execute_game_cmd("/win", 0);
	STRCMP_EQUAL("{\"action\":\"message\", \"content\":\"Are you kidding?\"}", LastResponse());
	execute_game_cmd("/pick", 0);
	setCheapestTileForSimpleEvaluator(27);
	wall->setCurrentTile(27);
	execute_game_cmd("/throw", 29);
	get_next_event_until_it_is_my_turn();
	execute_game_cmd("/win", 0);
	STRCMP_EQUAL("{\"action\":\"win\", \"player\":0,\"score\":1}", LastResponse());
}

TEST(html_game, ai_WIN) {
	execute_game_cmd("/next_event", 0);
	wall->setCurrentTile(14);
	execute_game_cmd("/throw", 1);
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"win\", \"player\":1,\"score\":1}", LastResponse());
	execute_game_cmd("/start", 0);
	wall->setCurrentTile(41);
	execute_game_cmd("/pick", 0);
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/throw", 41);
	execute_game_cmd("/next_event", 0);
	STRCMP_EQUAL( "{\"action\":\"win\", \"player\":1,\"score\":1}", LastResponse());
}

TEST(html_game, pong) {
	execute_game_cmd("/throw", 1);
	get_next_event_until_it_is_my_turn();
	execute_game_cmd("/pong", 0);
	STRCMP_EQUAL( "{\"action\":\"message\", \"content\":\"Are you kidding?\"}", LastResponse());
	wall->setCurrentTile(2);
	execute_game_cmd("/pick", 0);
	wall->setCurrentTile(2);
	setCheapestTileForSimpleEvaluator(2);
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/throw", 3);
	get_next_event_until_it_is_my_turn();
	execute_game_cmd("/current", 0);
	STRCMP_CONTAINS("\"allowed_actions\":[\"pong\"", LastResponse());
	execute_game_cmd("/pong", 0);
	STRCMP_EQUAL( "{\"action\":\"update_all\"}", LastResponse());
	execute_game_cmd("/current", 0);
	STRCMP_CONTAINS( "{\"players\":[{"
			"\"player_index\":0,\"hand\":[4,5,6,7,8,9,10,11,12,13],\"new_pick\":27,\"melds\":[130]"
		"},{"
			"\"player_index\":1,\"hand\":[15,16,17,18,19,20,21,22,23,24,25,26,28],\"new_pick\":0,\"melds\":[]"
	"}]", LastResponse());
	execute_game_cmd("/next_event", 0);
	execute_game_cmd("/throw", 4);
}

TEST(html_game, chow_when_not_able_to_chow) {
	execute_game_cmd("/throw", 1);
	get_next_event_until_it_is_my_turn();
	execute_game_cmd("/chow", 0);
	STRCMP_EQUAL( "{\"action\":\"message\", \"content\":\"Cannot meld chow.\"}", LastResponse());
}

TEST(html_game, chow) {
	setCheapestTileForSimpleEvaluator(14);
	execute_game_cmd("/throw", 1);
	get_next_event_until_it_is_my_turn();
	execute_game_cmd("/chow", 12);
	STRCMP_EQUAL( "{\"action\":\"update_all\"}", LastResponse());
	execute_game_cmd("/current", 0);
	STRCMP_CONTAINS( "{\"players\":[{\"player_index\":0,\"hand\":[2,3,4,5,6,7,8,9,10,11],\"new_pick\":27,\"melds\":[268]}", LastResponse());
}
