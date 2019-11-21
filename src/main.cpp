#include <stdlib.h>
#include <time.h>
#include "httpd.h"
#include "MahjongGameServer.h"
#include "HTMLMahjongGame.h"
#include "string.h"

int main(void)
{
	srand(time(NULL));
	MahjongGameServer server(set_shutdown_flag);
	HTMLMahjongGame game(&server);
	return server_main(&game);
}
