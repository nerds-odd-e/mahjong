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

class HTMLEnableWinEvent: public UIEvent {
public:
	virtual std::string toString();
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

class HTMLEnablePongEvent: public UIEvent {
public:
	std::string toString();
};

class HTMLEnableChewEvent: public UIEvent {
public:
	std::string toString();
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
	sprintf(tmp, "App.Pick(%d, %d);", distance_, tile_.getID());
	if (0 != distance_)
		strcat(tmp, "|");

	return tmp;
}

string HTMLDiscardEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "App.Throw(%d, %d);", tile_.getID(), distance_);
	if (0 == distance_)
		strcat(tmp, "|");

	return tmp;
}

string HTMLEnableWinEvent::toString() {
	return "App.LightButton('win');";
}

string HTMLWinEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "App.WinAck(%d, %d);", distance_, score_);
	return tmp;
}

string HTMLMessageEvent::toString() {
	char tmp[1024];
	sprintf(tmp, "alert(\"%s\");", message_);
	return tmp;
}

string HTMLEnablePongEvent::toString() {
	return "App.LightButton('pong');";
}

string HTMLEnableChewEvent::toString() {
	return "App.LightButton('chow');";
}

class TileArrayScriptGenerator {
public:
	const char * getTilesArrayString(UserView * view, char buffer[], int buffer_size);
private:
	void catTilesToString(char buffer[], const Tile * tiles, int n);
	void catmeldToString(char buffer[], const Meld * meld, int n);
	void catPlayerTilesToString(Hand * player, char buffer[], int buffer_size);
};

string HTMLDealEvent::toString() {
	const int buffer_size = 1024;
	char tmp[buffer_size];
	char buffer[buffer_size];
	TileArrayScriptGenerator().getTilesArrayString(view_, tmp, buffer_size);
	snprintf(buffer, buffer_size, "App.UpdateHolding(%s);", tmp);
	return buffer;
}

UIEvent * HTMLEventFactory::createPickEvent(Tile tile, int distance) {
	return new HTMLPickEvent(tile, distance);
}

UIEvent * HTMLEventFactory::createEnableWinEvent() {
	return new HTMLEnableWinEvent();
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

UIEvent * HTMLEventFactory::createEnablePongEvent() {
	return new HTMLEnablePongEvent();
}

UIEvent * HTMLEventFactory::createEnableChewEvent() {
	return new HTMLEnableChewEvent();
}

UIEvent * HTMLEventFactory::createDealEvent(UserView * view) {
	return new HTMLDealEvent(view);
}
