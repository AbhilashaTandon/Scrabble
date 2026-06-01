cmake_minimum_required(VERSION 3.28)

project(scrabble)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
SOURCES
        include/board.h
        include/bot.h
        include/dawg.h
        include/helper.h
        include/parse_gcg.h
        include/print.h
        src/board.cpp
        src/bot.cpp
        src/dawg.cpp
        src/helper.cpp
        src/parse_gcg.cpp
)

add_executable(scrabble_debug
        ${SOURCES}
        src/main.cpp
)

target_include_directories(scrabble_debug PUBLIC include/)
target_compile_options(scrabble_debug PUBLIC -Wall -Wextra -Wpedantic -g -O0 -ggdb -fno-omit-frame-pointer -gcolumn-info)

add_executable(scrabble
        ${SOURCES}
        src/main.cpp
)

target_include_directories(scrabble PUBLIC include/)
target_compile_options(scrabble PUBLIC -Wall -Wextra -Wpedantic -O3)

enable_testing()



add_executable(
  scrabble_test
  src/test.cpp
  tests/helper_test.cpp
  tests/board_test.cpp
  tests/wordlist_test.cpp
  deps/doctest.h
  ${SOURCES}
)

target_include_directories(scrabble_test PUBLIC include/)

target_compile_options(scrabble_test PUBLIC -Wall -Wextra -Wpedantic -g -O0)

# Make test executable
target_compile_features(scrabble_test PRIVATE cxx_std_17) # or later version

find_package(benchmark REQUIRED)

target_link_libraries(
  scrabble_test
)

target_link_libraries(scrabble_test benchmark::benchmark)
target_link_libraries(scrabble_debug benchmark::benchmark)

