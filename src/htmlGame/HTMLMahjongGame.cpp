#include "HTMLMahjongGame.h"
#include "HTMLMahjongGameServer.h"
#include "HTMLMahjongGameResponse.h"
#include <string.h>
HTMLMahjongGame::HTMLMahjongGame(MahjongGameServer *server) :
		server_(server) {

}

void HTMLMahjongGame::responseToString(
		MahjongGameResponse *respond,
		char * buffer, int buffer_size) {
	strncpy(buffer, ((HTMLMahjongGameResponse *)respond)->getString(), buffer_size);
}

void HTMLMahjongGame::callback(const char * command, const char *parameters,
		char * buffer, int buffer_size) {
	MahjongGameResponse * respond =
			server_->executeGameCommand(command, parameters);
	responseToString(respond, buffer, buffer_size);
	delete respond;
}
