#include "HTMLMahjongGame.h"
#include "MahjongGameServer.h"
#include "GameJsonResponse.h"
#include "HTMLCommandParser.h"
#include <string.h>
HTMLMahjongGame::HTMLMahjongGame(MahjongGameServer *server) :
		server_(server) {

}

void HTMLMahjongGame::responseToString(
		GameJsonResponse *respond,
		char * buffer, int buffer_size) {
	strncpy(buffer, ((GameJsonResponse *)respond)->getString(), buffer_size);
}

void HTMLMahjongGame::callback(const char * command, const char *parameters,
		char * buffer, int buffer_size) {
	MahjongCommand * mjCommand = HTMLCommandParser(server_).parse(command, parameters);
	GameJsonResponse * respond = server_->executeGameCommand(mjCommand);
	responseToString(respond, buffer, buffer_size);
	delete mjCommand;
	delete respond;
}
