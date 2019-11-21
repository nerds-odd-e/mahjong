#include <queue>
#include "CppUTestExt/MockSupport.h"
#include "mocks.h"
#include "UIEvent.h"
#include "Hand.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(UIEvent) {
	UIEventFactory factory;
	UIEvent *event;
	void teardown() {
		delete event;
	}
};

TEST(UIEvent, HTMLPickEvent) {
	event = factory.createPickEvent(1, 2);
	STRCMP_EQUAL("{\"action\":\"pick\", \"player\":2,\"tile\":1}",
			event->toString().c_str());
}

TEST(UIEvent, HTMLPickEvent_by_self) {
	event = factory.createPickEvent(1, 0);
	STRCMP_EQUAL("{\"action\":\"pick\", \"player\":0,\"tile\":1}", event->toString().c_str());
}

TEST(UIEvent, DiscardEvent) {
	event = factory.createDiscardEvent(1, 2);
	STRCMP_EQUAL("{\"action\":\"discard\", \"player\":2,\"tile\":1}", event->toString().c_str());
}

TEST(UIEvent, DiscardEvent_by_previous_player) {
	event = factory.createDiscardEvent(1, 1);
	STRCMP_EQUAL("{\"action\":\"discard\", \"player\":1,\"tile\":1}", event->toString().c_str());
}

TEST(UIEvent, WinEvent) {
	event = factory.createWinEvent(3, 1);
	STRCMP_EQUAL("{\"action\":\"win\", \"player\":3,\"score\":1}", event->toString().c_str());
}

TEST(UIEvent, MessageEvent) {
	event = factory.createMessageEvent("hello");
	STRCMP_EQUAL("{\"action\":\"message\", \"content\":\"hello\"}", event->toString().c_str());
}

TEST(UIEvent, dealEvent) {
	Tile tiles1[] = { 1 };
	Tile tiles2[] = { 2, 3 };
	Hand playerData1, playerData2;
	playerData1.deal(tiles1, 1);
	playerData2.deal(tiles2, 2);

	event = factory.createUpdateAllEvent();

	STRCMP_EQUAL("{\"action\":\"update_all\"}", event->toString().c_str());
}
