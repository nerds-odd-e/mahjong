set(Test_SRCS
    AllTests.cpp
    test_evaluator.cpp
    test_terry_evaluator.cpp
)

include_directories($ENV{CPPUTEST_HOME_INCLUDE})
include_directories(${PROJECT_SOURCE_DIR}/mahjong_evaluator/src)

add_library(CppUTest STATIC IMPORTED)
set_property(TARGET CppUTest PROPERTY
        IMPORTED_LOCATION /usr/local/lib/libCppUTest.a)

add_library(CppUTestExt STATIC IMPORTED)
set_property(TARGET CppUTestExt PROPERTY
        IMPORTED_LOCATION /usr/local/lib/libCppUTestExt.a)

add_executable(mahjong-evaluator-test ${Test_SRCS})
target_link_libraries(mahjong-evaluator-test CppUTest CppUTestExt mahjong_evaluator)

set(UNIT_TEST mahjong-evaluator-test)
add_custom_command(
     TARGET ${UNIT_TEST}
     COMMENT "Run tests"
     POST_BUILD 
     COMMAND ${UNIT_TEST}
)