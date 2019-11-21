#include <queue>
#include "CppUTestExt/MockSupport.h"
#include "MahjongCommand.h"
#include "MahjongGameServer.h"
#include "GameJsonResponse.h"
#include "mocks.h"
#include "CppUTest/TestHarness.h"

const int buffer_size = 1000;
const GameID NEW_ID = 100;
const GameID GAME_ID = 101;

TEST_GROUP(MJCommand) {
	char buffer[buffer_size];
	MockHTMLMahjongGameServer server;
	MockHTMLMahjongGameResponse respond;
	MockGame game;
	MockUserView view;
};

TEST(MJCommand, start_new){
	mock().expectOneCall("startNewGame").onObject(&server).andReturnValue(NEW_ID);
	mock().expectOneCall("newGame").onObject(&respond).withParameter("gameID", NEW_ID);
	MJCommandNewPlayerJoin cmd(&server);
	cmd.execute(&respond);
}

TEST(MJCommand, bye){
	mock().expectOneCall("killGame").onObject(&server).withParameter("gameID", GAME_ID);
	mock().expectOneCall("bye").onObject(&respond);
	MJCommandQuitGame cmd(&server, GAME_ID);
	cmd.execute(&respond);
}

TEST(MJCommand, shutdown){
	mock().expectOneCall("shutdown").onObject(&server);
	mock().expectOneCall("shutdown").onObject(&respond);
	MJCommandShutdownServer cmd(&server);
	cmd.execute(&respond);
}

TEST(MJCommand, start_game){
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);

	MJCommandStartNewGame cmd(&game);
	cmd.execute(&respond);
}

TEST(MJCommand, game_does_not_exsit){
	mock().expectOneCall("gameDoesNotExist").onObject(&respond);
	MJCommandDoesNotExist cmd;
	cmd.execute(&respond);
}

TEST(MJCommand, pick){
	MockGame game;
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);
	MJCommandPick cmd(&game);
	cmd.execute(&respond);
}

TEST(MJCommand, discard){
	MockGame game;
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);
	MJCommandDiscard cmd(&game, 1);
	cmd.execute(&respond);
}

TEST(MJCommand, chow){
	MockGame game;
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);
	MJCommandChow cmd(&game, 1);
	cmd.execute(&respond);
}

TEST(MJCommand, pong){
	MockGame game;
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);
	MJCommandPong cmd(&game);
	cmd.execute(&respond);
}

TEST(MJCommand, kong){
	MockGame game;
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);
	MJCommandKong cmd(&game, 1);
	cmd.execute(&respond);
}

TEST(MJCommand, win){
	MockGame game;
	mock().expectOneCall("nextMove").onObject(&game).ignoreOtherParameters();
	mock().expectOneCall("getUserView").onObject(&game).andReturnValue((void*)&view);
	mock().expectOneCall("popAction").onObject(&respond).withParameter("view", &view);
	MJCommandWin cmd(&game);
	cmd.execute(&respond);
}

