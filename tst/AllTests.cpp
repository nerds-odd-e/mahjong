#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestPlugin.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"
//#include "CppUTestExt/GTestConvertor.h"

int main(int ac, char** av) {
//	GTestConvertor convertor;
//	convertor.addAllGTestToTestRegistry();

	srand(time(NULL));
	MockSupportPlugin mockPlugin;
	TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);
	int res = CommandLineTestRunner::RunAllTests(ac, av);
	TestRegistry::getCurrentRegistry()->resetPlugins();
	return res;
}

