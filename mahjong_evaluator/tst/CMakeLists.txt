set(Test_SRCS
    AllTests.cpp
    test_evaluator.cpp
    test_terry_evaluator.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/mahjong_evaluator/src)

add_executable(mahjong-evaluator-test ${Test_SRCS})
target_link_libraries(mahjong-evaluator-test CppUTest CppUTestExt mahjong_evaluator)

set(UNIT_TEST mahjong-evaluator-test)
add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${UNIT_TEST}
)