#undef new
#include <map>
#include "CppUTest/MemoryLeakDetectorNewMacros.h"
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "HTMLMahjongGame.h"
#include "HTMLMahjongGameServer.h"
#include "Wall.h"
#include "TileArray.h"
#include "EvaluatorAdaptor.h"
#include "HTMLMahjongGameFactory.h"

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

static Wall * createEverIncreasingWall() {
	lastCreatedEverIncreasingWall = new EverIncreasingWall;
	return lastCreatedEverIncreasingWall;
}

#define HAS_STRING(expect, actual) HAS_STRING_LOCATION(expect, actual, __FILE__, __LINE__)
TEST_GROUP(html_game) {

	int gameID;
	HTMLMahjongGame *game;
	HTMLMahjongGameFactory factory;
	MahjongGameServer *server;
	EverIncreasingWall *wall;
	char bigBuffer_[BIGGER_BUFFER_SIZE];

	void setup() {
		server = new MahjongGameServer(&factory);
		game = new HTMLMahjongGame(server);
		UT_PTR_SET(createEvaluatorAdaptor, createSimpleEvaluator);
		UT_PTR_SET(createWall, createEverIncreasingWall);
		execute_cmd("/join");
		gameID = server->getLastGameID();
		wall = lastCreatedEverIncreasingWall;
		execute_game_cmd("/start", 0);
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

	const char * LastResponse() {
		return bigBuffer_;
	}

	void HAS_STRING_LOCATION(const char * expect, const char * actual,
			const char * filename, int line) {
		if (strstr(actual, expect) == NULL) {
			const int buffer_size = 500;
			char text[buffer_size];
			snprintf(text, buffer_size - 1, "The actual string <%s>\n"
					"does not include the expected string <%s>", actual,
					expect);
			FAIL_LOCATION(text, filename, line);
		}
	}
};

TEST(html_game, start) {
	STRCMP_EQUAL(
			"App.deal();App.Pick(0, 27);",
			LastResponse());
}

TEST(html_game, get_current_status) {
	execute_game_cmd("/current", 0);
	STRCMP_EQUAL(
			"[{\"player_index\":0,\"hand\":[1,2,3,4,5,6,7,8,9,10,11,12,13],\"new_pick\":27,\"melds\":[]},"
			"{\"player_index\":1,\"hand\":[14,15,16,17,18,19,20,21,22,23,24,25,26],\"new_pick\":0,\"melds\":[]}]",
			LastResponse());
}

TEST(html_game, a_game) {
	execute_game_cmd("/throw", 1);
	HAS_STRING("App.Throw(1, 0);|App.Pick(1, 28);|App.Throw(14, 1);",
			LastResponse());
	setCheapestTileForSimpleEvaluator(28);
	wall->setCurrentTile(27);
	execute_game_cmd("/pick", 0);
	STRCMP_EQUAL( "App.Pick(0, 27);App.LightButton('win');",
			LastResponse());
	execute_game_cmd("/win", 0);
	STRCMP_EQUAL("App.WinAck(0, 1);", LastResponse());
	wall->setCurrentTile(1);
	setCheapestTileForSimpleEvaluator(27);
	execute_game_cmd("/start", 0);
	HAS_STRING(
			"App.deal();App.Pick(1, 27);|App.Throw(27, 1);",
			LastResponse());
}

TEST(html_game, no_tile_any_more) {
	wall->empty();
	execute_game_cmd("/throw", 1);
	STRCMP_EQUAL( "App.Throw(1, 0);|App.WinAck(1, 0);", LastResponse());
	setCheapestTileForSimpleEvaluator(54);
	execute_game_cmd("/start", 0);
	HAS_STRING(
			"App.deal();App.Pick(1, 54);|App.Throw(54, 1);",
			LastResponse());
	HAS_STRING("App.WinAck(0, 0);", LastResponse());
	execute_game_cmd("/start", 0);
	STRCMP_EQUAL(
			"App.deal();App.Pick(0, 81);",
			LastResponse());
}

TEST(html_game, _WIN) {
	execute_game_cmd("/win", 1);
	STRCMP_EQUAL("alert(\"Are you kidding?\");", LastResponse());
	execute_game_cmd("/throw", 1);
	HAS_STRING( "App.Throw(1, 0);|App.Pick(1, 28);|App.Throw(14, 1);",
			LastResponse());
	setCheapestTileForSimpleEvaluator(28);
	execute_game_cmd("/win", 0);
	STRCMP_EQUAL("alert(\"Are you kidding?\");", LastResponse());
	execute_game_cmd("/pick", 0);
	setCheapestTileForSimpleEvaluator(27);
	wall->setCurrentTile(27);
	execute_game_cmd("/throw", 29);
	execute_game_cmd("/win", 0);
	STRCMP_EQUAL("App.WinAck(0, 1);", LastResponse());
}

TEST(html_game, ai_WIN) {
	wall->setCurrentTile(14);
	execute_game_cmd("/throw", 1);
	STRCMP_EQUAL( "App.Throw(1, 0);|App.Pick(1, 14);|App.WinAck(1, 1);",
			LastResponse());
	execute_game_cmd("/start", 0);
	wall->setCurrentTile(41);
	execute_game_cmd("/pick", 0);
	execute_game_cmd("/throw", 41);
	STRCMP_EQUAL( "App.Throw(41, 0);|App.WinAck(1, 1);", LastResponse());
}

TEST(html_game, pong) {
	execute_game_cmd("/throw", 1);
	execute_game_cmd("/pong", 0);
	STRCMP_EQUAL( "alert(\"Are you kidding?\");", LastResponse());
	wall->setCurrentTile(2);
	execute_game_cmd("/pick", 0);
	wall->setCurrentTile(2);
	setCheapestTileForSimpleEvaluator(2);
	execute_game_cmd("/throw", 3);
	HAS_STRING(
			"App.Throw(3, 0);|App.Pick(1, 2);|App.Throw(2, 1);App.LightButton('pong');",
			LastResponse());
	execute_game_cmd("/pong", 0);
	STRCMP_EQUAL( "App.deal();", LastResponse());
	execute_game_cmd("/current", 0);
	STRCMP_EQUAL( "[{"
			"\"player_index\":0,\"hand\":[4,5,6,7,8,9,10,11,12,13],\"new_pick\":27,\"melds\":[130]"
		"},{"
			"\"player_index\":1,\"hand\":[15,16,17,18,19,20,21,22,23,24,25,26,28],\"new_pick\":0,\"melds\":[]"
	"}]", LastResponse());
	execute_game_cmd("/throw", 4);
	HAS_STRING( "App.Throw(4, 0);|App.Pick(1, 3);|App.Throw(15, 1);",
			LastResponse());
}

IGNORE_TEST(html_game, chow_when_not_able_to_chow) {
	execute_game_cmd("/throw", 1);
	execute_game_cmd("/chow", 0);
	STRCMP_EQUAL( "alert(\"Cannot meld chow.\");", LastResponse());
}

IGNORE_TEST(html_game, chow) {
	setCheapestTileForSimpleEvaluator(14);
	execute_game_cmd("/throw", 1);
	execute_game_cmd("/chow", 12);
	STRCMP_EQUAL(
			"App.UpdateHolding([[2,3,4,5,6,7,8,9,10,11,27,268],[15,16,17,18,19,20,21,22,23,24,25,26,28,0]]);",
			LastResponse());
}
