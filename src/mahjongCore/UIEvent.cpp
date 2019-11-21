#include "mahjong_game.h"
#include "UIEvent.h"

using namespace std;

UIEventQueue::UIEventQueue() {
}

UIEventQueue::~UIEventQueue() {
}

UIEvent * UIEventQueue::popEvent() {
	if (eventQueue_.empty())
		return NULL;
	UIEvent *event = eventQueue_.front();
	eventQueue_.pop();
	return event;
}

void UIEventQueue::addEvent(UIEvent * event) {
	eventQueue_.push(event);
}

class PickEvent: public UIEvent {
public:
	PickEvent(Tile tile, int distance) :
			tile_(tile), distance_(distance) {
	}
	virtual ~PickEvent() {
	}
	virtual std::string toString();
private:
	Tile tile_;
	int distance_;
};

class DiscardEvent: public UIEvent {
public:
	DiscardEvent(Tile tile, int distance):
		tile_(tile), distance_(distance) {}
	std::string toString();
private:
	Tile tile_;
	int distance_;
};

class WinEvent: public UIEvent {
public:
	WinEvent(int distance, int score): distance_(distance), score_(score) {}
	std::string toString();
private:
	int distance_;
	int score_;
};

class MessageEvent: public UIEvent {
public:
	MessageEvent(const char * message) {message_ = message;}
	std::string toString();
private:
	const char * message_;
};

class UserView;
class UpdateAllEvent: public UIEvent {
public:
	std::string toString();
};

string PickEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"pick\", \"player\":%d,\"tile\":%d}", distance_, tile_.getID());
	return tmp;
}

string DiscardEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"discard\", \"player\":%d,\"tile\":%d}", distance_, tile_.getID());
	return tmp;
}

string WinEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"win\", \"player\":%d,\"score\":%d}", distance_, score_);
	return tmp;
}

string MessageEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"message\", \"content\":\"%s\"}", message_);
	return tmp;
}

string UpdateAllEvent::toString() {
	return "{\"action\":\"update_all\"}";
}

UIEvent * UIEventFactory::createPickEvent(Tile tile, int distance) {
	return new PickEvent(tile, distance);
}

UIEvent * UIEventFactory::createDiscardEvent(Tile tile, int distance) {
	return new DiscardEvent(tile, distance);
}

UIEvent * UIEventFactory::createWinEvent(int distance, int score) {
	return new WinEvent(distance, score);
}

UIEvent * UIEventFactory::createMessageEvent(const char * message) {
	return new MessageEvent(message);
}

UIEvent * UIEventFactory::createUpdateAllEvent() {
	return new UpdateAllEvent();
}