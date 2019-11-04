#ifndef HTMLMAHJONGGAMERESPONSE_H_
#define HTMLMAHJONGGAMERESPONSE_H_

#include <string>
#include "MahjongGameResponse.h"

class UserView;
class Hand;

class HTMLMahjongGameResponse : public MahjongGameResponse{
public:
	virtual ~HTMLMahjongGameResponse(){}

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

#endif /* HTMLMAHJONGGAMERESPONSE_H_ */
