cmake_minimum_required(VERSION 3.28)

project(scrabble)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL http/github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -O0")
# set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3")
#
# add_compile_options(-Wall -Wextra -Wpedantic ${CXX_FLAGS})

set(
SOURCES
        src/board.cpp
        src/helper.cpp
        src/wordlist.cpp
        src/trie.cpp
        include/board.h
        include/trie.h
        include/bot.h
        include/helper.h
        include/print.h
        include/wordlist.h
)

add_executable(scrabble_debug
        ${SOURCES}
        src/main.cpp
)

target_include_directories(scrabble_debug PUBLIC include/)
target_compile_options(scrabble_debug PUBLIC -Wall -Wextra -Wpedantic -g -O0)

add_executable(scrabble
        ${SOURCES}
        src/main.cpp
)

target_include_directories(scrabble PUBLIC include/)
target_compile_options(scrabble PUBLIC -Wall -Wextra -Wpedantic -O3)

enable_testing()

add_executable(
  scrabble_test
  tests/helper_test.cpp
  tests/board_test.cpp
  tests/test_gtest.cpp
  tests/wordlist_test.cpp
  ${SOURCES}
)

target_include_directories(scrabble_test PUBLIC include/)

target_compile_options(scrabble_test PUBLIC -Wall -Wextra -Wpedantic -g -O0)


find_package(GTest REQUIRED)

target_link_libraries(
  scrabble_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(scrabble_test)
