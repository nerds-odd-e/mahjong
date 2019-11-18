#include <queue>
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"
#include "HTMLUIEvent.h"
#include "Hand.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(HTMLUIEvent) {
	HTMLEventFactory factory;
	UIEvent *event;
	void teardown() {
		delete event;
	}
};

TEST(HTMLUIEvent, HTMLPickEvent) {
	event = factory.createPickEvent(1, 2);
	STRCMP_EQUAL("{\"action\":\"pick\", \"player\":2,\"tile\":1}",
			event->toString().c_str());
}

TEST(HTMLUIEvent, HTMLPickEvent_by_self) {
	event = factory.createPickEvent(1, 0);
	STRCMP_EQUAL("{\"action\":\"pick\", \"player\":0,\"tile\":1}", event->toString().c_str());
}

TEST(HTMLUIEvent, DiscardEvent) {
	event = factory.createDiscardEvent(1, 2);
	STRCMP_EQUAL("{\"action\":\"discard\", \"player\":2,\"tile\":1}", event->toString().c_str());
}

TEST(HTMLUIEvent, DiscardEvent_by_previous_player) {
	event = factory.createDiscardEvent(1, 1);
	STRCMP_EQUAL("{\"action\":\"discard\", \"player\":1,\"tile\":1}", event->toString().c_str());
}

TEST(HTMLUIEvent, EnableWinEvent) {
	event = factory.createEnableWinEvent();
	STRCMP_EQUAL("App.LightButton('win');", event->toString().c_str());
}

TEST(HTMLUIEvent, WinEvent) {
	event = factory.createWinEvent(3, 1);
	STRCMP_EQUAL("{\"action\":\"win\", \"player\":3,\"score\":1}", event->toString().c_str());
}

TEST(HTMLUIEvent, MessageEvent) {
	event = factory.createMessageEvent("hello");
	STRCMP_EQUAL("{\"action\":\"message\", \"content\":\"hello\"}", event->toString().c_str());
}

TEST(HTMLUIEvent, EnablePongEvent) {
	event = factory.createEnablePongEvent();
	STRCMP_EQUAL("App.LightButton('pong');", event->toString().c_str());
}

TEST(HTMLUIEvent, EnableChewEvent) {
	event = factory.createEnableChewEvent();
	STRCMP_EQUAL("App.LightButton('chow');", event->toString().c_str());
}

TEST(HTMLUIEvent, dealEvent) {
	Tile tiles1[] = { 1 };
	Tile tiles2[] = { 2, 3 };
	Hand playerData1, playerData2;
	playerData1.deal(tiles1, 1);
	playerData2.deal(tiles2, 2);
	MockUserView view;

	event = factory.createDealEvent(&view);

	STRCMP_EQUAL("{\"action\":\"deal\"}", event->toString().c_str());
}
