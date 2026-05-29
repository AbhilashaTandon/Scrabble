#include "../include/bot.h"
#include "../include/dawg.h"
#include "../include/parse_cli_args.h"
#include "../include/parse_gcg.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

int main(int argc, char **argv) {

        if (argc == 5) {
                LookupFiles l =
                    LookupFiles(std::string(argv[1]), std::string(argv[2]),
                                std::string(argv[3]), std::string(argv[4]));
        }

        Dawg d = Dawg();
        std::unordered_multiset<Tile> rack{Tile::A, Tile::C, Tile::Q, Tile::R, Tile::S, Tile::BLANK, Tile::U};
        for(std::string word : d.get_words_from_tiles(rack, 4)){
                std::cout << word << ' ';
        }

        rack = {Tile::E, Tile::X, Tile::S, Tile::I, Tile::O, Tile::BLANK, Tile::U};
        for(std::string word : d.get_words_from_tiles(rack, 4)){
                std::cout << word << ' ';
        }

        return 0;
}
