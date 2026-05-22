#include "../include/parse_gcg.h"
#include "../include/board.h"
#include <cassert>
#include <filesystem>
#include <iostream>

int main() {
        setlocale(LC_ALL, "en_US.UTF-8");
        const std::filesystem::path path = "../games";
        for (const auto &entry : std::filesystem::directory_iterator(path)) {
                std::cout << entry.path() << std::endl;
                GCGParser parser(entry.path());
                std::cout << parser.validate_game();
                std::cout << entry.path() << std::endl;
                return 0;
        }

        // std::array<tile_place_t, 7> play;
        // play[0] = std::make_pair(Tile::A, get_pos(3, 7));
        // play[1] = std::make_pair(Tile::C, get_pos(4, 7));
        // play[2] = std::make_pair(Tile::A, get_pos(5, 7));
        // play[3] = std::make_pair(Tile::D, get_pos(6, 7));
        // play[4] = std::make_pair(Tile::E, get_pos(7, 7));
        // play[5] = std::make_pair(Tile::M, get_pos(8, 7));
        // play[6] = std::make_pair(Tile::Y, get_pos(9, 7));
        //
        // Board b = Board("../wordlists/NWL2023-modified.txt",
        //                 "../wordlists/trie.txt", "../wordlists/extensions.txt");
        //
        // b.make_play(play).size();
        //
        // play[0] = std::make_pair(Tile::T, get_pos(5, 8));
        // play[1] = std::make_pair(Tile::O, get_pos(6, 8));
        // play[2] = std::make_pair(Tile::R, get_pos(7, 8));
        // play[3] = std::make_pair(Tile::I, get_pos(8, 8));
        // play[4] = std::make_pair(Tile::E, get_pos(9, 8));
        // play[5] = std::make_pair(Tile::S, get_pos(10, 8));
        // play[6] = std::make_pair(Tile::NONE, get_pos(11, 8));
        //
        // b.make_play(play);
        //
        // b.print();


        return 0;
}
