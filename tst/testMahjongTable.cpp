#include <queue>
#include "CppUTestExt/MockSupport.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Wall.h"
#include "mj_table.h"
#include "mocks.h"
#include "CppUTest/TestHarness.h"
#include "AIPerspective.h"
#include "UserPerspective.h"


TEST_GROUP(MahjongTable) {
    Wall * wall_ = createWall();
    Settings settings;
	MahjongTable * table_ = new MahjongTable(wall_, settings.GetGameLevel());
   // AIPerspective * aiPerspective = new AIPerspective();
	UserPerspective * userPerspective = new UserPerspective();
};


