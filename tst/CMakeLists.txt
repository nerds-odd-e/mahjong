set(Test_SRCS
    AllTests.cpp
    evaluatorStubs.cpp
    integrationTests.cpp
    mocks.cpp
    mocks.h
    simple_evaluator.cpp
    testAIPerspective.cpp
    testEvaluatorAdaptor.cpp
    testGameIDMap.cpp
    testHTMLCommandParser.cpp
    testHTMLMahjongGameServer.cpp
    testMahjongCommand.cpp
    testMahjongTable.cpp
    testUIEvent.cpp
    testUserPerspective.cpp
    testJsonGameResponse.cpp
    mahjongCore/testGame.cpp
    mahjongCore/testGameLevel.cpp
    mahjongCore/testHand.cpp
    mahjongCore/testSettings.cpp
    mahjongCore/testTile.cpp
    mahjongCore/testTileArray.cpp
    mahjongCore/testTileArrayIsAbleToChow.cpp
    mahjongCore/testWall.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/src/httpServer)
include_directories(${PROJECT_SOURCE_DIR}/src/htmlGame)
include_directories(${PROJECT_SOURCE_DIR}/src/mahjongCore)
include_directories(${PROJECT_SOURCE_DIR}/mahjong_evaluator/include)

add_executable(mahjong-test ${Test_SRCS})
target_link_libraries(mahjong-test CppUTest CppUTestExt htmlGame mahjongCore)

set(UNIT_TEST mahjong-test)
add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${UNIT_TEST}
)