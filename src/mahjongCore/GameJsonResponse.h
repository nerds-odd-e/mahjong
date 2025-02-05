#ifndef HTMLMAHJONGGAMERESPONSE_H_
#define HTMLMAHJONGGAMERESPONSE_H_

#include <string>
#include "GameID.h"

class UserView;
class Hand;

class GameJsonResponse{
public:
	virtual ~GameJsonResponse(){}

	virtual void currentGameStatus(UserView * view);

	virtual void newGame(GameID gameID);

	virtual void bye();

	virtual void shutdown();

	virtual void gameDoesNotExist();

	virtual void popAction(UserView * view);

	const char * getString();

	void clear();

	void setContent(std::string content);

private:
	std::string content_;
};

#endif /* HTMLMAHJONGGAMERESPONSE_H_ */
