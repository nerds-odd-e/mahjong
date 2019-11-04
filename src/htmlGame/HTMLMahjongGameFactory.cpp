#include "HTMLMahjongGameFactory.h"
#include "HTMLMahjongGameResponse.h"

MahjongGameResponse * HTMLMahjongGameFactory::createMahjongGameRespond(){
	return new HTMLMahjongGameResponse();
}
