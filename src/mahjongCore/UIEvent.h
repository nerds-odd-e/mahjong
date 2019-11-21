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
	virtual UIEvent * createPickEvent(Tile tile, int distance);
	virtual UIEvent * createDiscardEvent(Tile tile, int distance);
	virtual UIEvent * createWinEvent(int distance, int score);
	virtual UIEvent * createMessageEvent(const char * message);
	virtual UIEvent * createUpdateAllEvent();
};



#endif /* UIEVENTQUEUE_H_ */
