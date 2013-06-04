#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLCommandParser.h"
#include "MahjongCommand.h"
#include "MahjongGameFactory.h"
#include "mocks.h"

static void shutdown_callback() {
	mock().actualCall("shutdown_callback");
}

class MockHTMLCommandParser: public HTMLCommandParser {
public:
	MockHTMLCommandParser() :
			HTMLCommandParser(NULL) {

	}
	MahjongCommand * parse(const char * command, const char *parameters) {
		return (MahjongCommand *) mock().actualCall("parse").onObject(this).withParameter(
				"command", command).withParameter("parameters", parameters).returnValue().getObjectPointer();
	}
};

class MockMahjongCommand: MahjongCommand {
public:
	virtual void execute(MahjongGameRespond *respond) {
		mock().actualCall("execute").onObject(this).withParameter("respond",
				respond);
	}
};

struct MahjongGameFactorForMocks : public MahjongGameFactory {
	MahjongGameRespond * createMahjongGameRespond() {
		return &respond;
	}
	MockHTMLMahjongGameRespond respond;
};

TEST_GROUP(MahjongGameServer) {
	MahjongGameServer *server;
	MockHTMLCommandParser *parser;
	MahjongGameFactorForMocks factory;
	void setup() {
		parser = new MockHTMLCommandParser;
		server = new MahjongGameServer(&factory, shutdown_callback, parser);
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
	MockMahjongCommand *command = new MockMahjongCommand;
	MockHTMLMahjongGameRespond respond;

	mock().expectOneCall("parse").onObject(parser).withParameter("command",
			"command").withParameter("parameters", "parameters").andReturnValue(
			(void*) command);
	mock().expectOneCall("execute").onObject(command).withParameter("respond",
			&factory.respond);

	server->executeGameCommand("command", "parameters");
}
