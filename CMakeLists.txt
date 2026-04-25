cmake_minimum_required(VERSION 3.28)

project(scrabble)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(
SOURCES
        src/board.cpp
        src/helper.cpp
        src/wordlist.cpp
        include/board.h
        include/bot.h
        include/helper.h
        include/print.h
        include/wordlist.h
)

add_executable(scrabble
        ${SOURCES}
        src/main.cpp
)


target_include_directories(scrabble PUBLIC include/)

enable_testing()

add_executable(
  scrabble_test
  tests/helper.cpp
  tests/board.cpp
  tests/test_gtest.cpp
  ${SOURCES}
)

target_include_directories(scrabble_test PUBLIC include/)

find_package(GTest REQUIRED)

target_link_libraries(
  scrabble_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(scrabble_test)
