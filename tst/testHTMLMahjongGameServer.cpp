#include "MahjongGameServer.h"
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"
#include "CppUTest/TestHarness.h"

static void shutdown_callback() {
	mock().actualCall("shutdown_callback");
}

class MockMahjongCommand: public MahjongCommand {
public:
	virtual void execute(GameJsonResponse *respond) {
		mock().actualCall("execute").onObject(this).withParameter("respond",
				respond);
		delete respond;
	}
};

TEST_GROUP(MahjongGameServer) {
	MahjongGameServer *server;
	void setup() {
		server = new MahjongGameServer(shutdown_callback);
	}
	void teardown() {
		delete server;
	}
};

TEST(MahjongGameServer, callback_should_be_call_when_shutdown) {
	mock().expectOneCall("shutdown_callback");
	server->shutdown();
}

TEST(MahjongGameServer, execute_command) {
	MockMahjongCommand command;

	// mock().expectOneCall("execute").onObject(&command).ignoreOtherParameters();

	// server->executeGameCommand(&command);
}
