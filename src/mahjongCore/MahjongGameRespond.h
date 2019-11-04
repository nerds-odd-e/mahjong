#ifndef MAHJONGGAMERESPOND_H_
#define MAHJONGGAMERESPOND_H_

#include "HTMLMahjongGameServer.h"

class UserView;

class MahjongGameRespond{
public:
	virtual ~MahjongGameRespond(){}
	virtual void newGame(GameID gameID) = 0;
	virtual void bye() = 0;
	virtual void shutdown() = 0;
	virtual void currentGameStatus(UserView * view) = 0;
	virtual void updateUIEvent(UserView * view) = 0;
	virtual void gameDoesNotExist() = 0;
};
#endif /* MAHJONGGAMERESPOND_H_ */
