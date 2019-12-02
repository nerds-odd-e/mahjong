#include <queue>
#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include <typeinfo>
#include "mocks.h"

TEST_GROUP(HTMLCommandParser) {
	MockHTMLMahjongGameServer server;
	HTMLCommandParser *parser;
	MahjongCommand *cmd;
	void setup() {
		cmd = NULL;
		parser = new HTMLCommandParser(&server);
	}
	void teardown() {
		delete cmd;
		delete parser;
	}
};

TEST(HTMLCommandParser, parse_start_new) {
	cmd = parser->parse("/join", "");
	STRCMP_EQUAL(typeid(MJCommandNewPlayerJoin).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, parse_bye) {
	cmd = parser->parse("/3/bye", "");
	STRCMP_EQUAL(typeid(MJCommandQuitGame).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, parse_shutdown) {
	cmd = parser->parse("/shutdown", "");
	STRCMP_EQUAL(typeid(MJCommandShutdownServer).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, restart) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/start", "");
	STRCMP_EQUAL(typeid(MJCommandStartNewGame).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, game_does_not_exist) {
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 4).andReturnValue((void *)NULL);
	cmd = parser->parse("/4/start", "");
	STRCMP_EQUAL(typeid(MJCommandDoesNotExist).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandDiscard) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/discard", "5");
	STRCMP_EQUAL(typeid(MJCommandDiscard).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandPick) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/pick", "");
	STRCMP_EQUAL(typeid(MJCommandPick).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandChow) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/chow", "2");
	STRCMP_EQUAL(typeid(MJCommandChow).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandPong) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/pong", "");
	STRCMP_EQUAL(typeid(MJCommandPong).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandKong) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/kong", "2");
	STRCMP_EQUAL(typeid(MJCommandKong).name(), typeid(*cmd).name());
}

TEST(HTMLCommandParser, MJCommandWin) {
	Settings settings;
	UserPerspective game( settings);
	mock().expectOneCall("getGameByID").onObject(&server).withParameter(
			"gameID", 3).andReturnValue(&game);
	cmd = parser->parse("/3/win", "");
	STRCMP_EQUAL(typeid(MJCommandWin).name(), typeid(*cmd).name());
}


