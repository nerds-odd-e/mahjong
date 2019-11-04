#ifndef HTMLMAHJONGGAMEFACTORY_H_
#define HTMLMAHJONGGAMEFACTORY_H_

#include "MahjongGameFactory.h"
struct HTMLMahjongGameFactory : public MahjongGameFactory{
	MahjongGameResponse * createMahjongGameRespond();
};

#endif /* HTMLMAHJONGGAMEFACTORY_H_ */
