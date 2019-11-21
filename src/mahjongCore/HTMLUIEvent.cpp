#include "mahjong_game.h"
#include "HTMLUIEvent.h"
#include "string.h"
#include "stdio.h"

using namespace std;

class HTMLPickEvent: public UIEvent {
public:
	HTMLPickEvent(Tile tile, int distance) :
			tile_(tile), distance_(distance) {
	}
	virtual ~HTMLPickEvent() {
	}
	virtual std::string toString();
private:
	Tile tile_;
	int distance_;
};

class HTMLDiscardEvent: public UIEvent {
public:
	HTMLDiscardEvent(Tile tile, int distance):
		tile_(tile), distance_(distance) {}
	std::string toString();
private:
	Tile tile_;
	int distance_;
};

class HTMLWinEvent: public UIEvent {
public:
	HTMLWinEvent(int distance, int score): distance_(distance), score_(score) {}
	std::string toString();
private:
	int distance_;
	int score_;
};

class HTMLMessageEvent: public UIEvent {
public:
	HTMLMessageEvent(const char * message) {message_ = message;}
	std::string toString();
private:
	const char * message_;
};

class UserView;
class HTMLDealEvent: public UIEvent {
public:
	HTMLDealEvent(UserView * view):view_(view){}
	std::string toString();
private:
	UserView * view_;
};

string HTMLPickEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"pick\", \"player\":%d,\"tile\":%d}", distance_, tile_.getID());
	return tmp;
}

string HTMLDiscardEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"discard\", \"player\":%d,\"tile\":%d}", distance_, tile_.getID());
	return tmp;
}

string HTMLWinEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"win\", \"player\":%d,\"score\":%d}", distance_, score_);
	return tmp;
}

string HTMLMessageEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "{\"action\":\"message\", \"content\":\"%s\"}", message_);
	return tmp;
}

string HTMLDealEvent::toString() {
	return "{\"action\":\"deal\"}";
}

UIEvent * HTMLEventFactory::createPickEvent(Tile tile, int distance) {
	return new HTMLPickEvent(tile, distance);
}

UIEvent * HTMLEventFactory::createDiscardEvent(Tile tile, int distance) {
	return new HTMLDiscardEvent(tile, distance);
}

UIEvent * HTMLEventFactory::createWinEvent(int distance, int score) {
	return new HTMLWinEvent(distance, score);
}

UIEvent * HTMLEventFactory::createMessageEvent(const char * message) {
	return new HTMLMessageEvent(message);
}

UIEvent * HTMLEventFactory::createDealEvent(UserView * view) {
	return new HTMLDealEvent(view);
}
