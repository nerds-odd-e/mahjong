#ifndef UIEVENTQUEUE_H_
#define UIEVENTQUEUE_H_

#include <queue>
#include <string>

class UIEvent{
public:
	virtual ~UIEvent() {}
	virtual std::string toString()= 0;
} ;

class UIEventQueue {
public:
	UIEventQueue();
	virtual ~UIEventQueue();
	UIEvent * popEvent();
	void addEvent(UIEvent * event);

private:
	std::queue<UIEvent*> eventQueue_;
};

class UserView;
class UIEventFactory{
public:
	virtual ~UIEventFactory() {};
	virtual UIEvent * createPickEvent(Tile tile, int distance) = 0;
	virtual UIEvent * createDiscardEvent(Tile tile, int distance) = 0;
	virtual UIEvent * createWinEvent(int distance, int score) = 0;
	virtual UIEvent * createMessageEvent(const char * message) = 0;
	virtual UIEvent * createDealEvent(UserView * view) = 0;
};


#endif /* UIEVENTQUEUE_H_ */
