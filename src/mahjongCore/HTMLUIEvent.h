#ifndef HTMLUIEVENT_H_
#define HTMLUIEVENT_H_

#include "UIEvent.h"
#include <string>

class HTMLEventFactory : public UIEventFactory{
public:
	UIEvent * createPickEvent(Tile tile, int distance);
	UIEvent * createDiscardEvent(Tile tile, int distance);
	UIEvent * createEnableWinEvent();
	UIEvent * createWinEvent(int distance, int score);
	UIEvent * createMessageEvent(const char * message);
	UIEvent * createEnablePongEvent();
	UIEvent * createEnableChewEvent();
	UIEvent * createDealEvent(UserView * view);
};

#endif /* HTMLUIEVENT_H_ */
