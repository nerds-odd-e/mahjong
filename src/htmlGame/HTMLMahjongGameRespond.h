#ifndef HTMLMAHJONGGAMERESPOND_H_
#define HTMLMAHJONGGAMERESPOND_H_

#include <string>
#include "MahjongGameRespond.h"

class UserView;
class Hand;

class HTMLMahjongGameRespond : public MahjongGameRespond{
public:
	virtual ~HTMLMahjongGameRespond(){}

	void currentGameStatus(UserView * view);

	virtual void newGame(GameID gameID);

	virtual void bye();

	virtual void shutdown();

	virtual void gameDoesNotExist();

	virtual void updateUIEvent(UserView * view);

	const char * getString();

	void clear();

private:
	std::string content_;
};

#endif /* HTMLMAHJONGGAMERESPOND_H_ */
