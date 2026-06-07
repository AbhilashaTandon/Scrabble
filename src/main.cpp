#include "../include/dawg.h"
#include "../include/parse_gcg.h"
#include "../include/wordlist.h"
#include <cassert>
#include <filesystem>
#include <gtest/gtest.h>

int main() {
        Dawg d = Dawg(WORDLIST_FILE);
        // d.print();
        // d.print();

        std::unordered_multiset<Tile> rack = {
            Tile::A, Tile::B, Tile::BLANK, Tile::E, Tile::BLANK, Tile::R, Tile::A};

        for (auto ext : d.get_extensions(rack, "MAN", 2, 2)) {
                std::cout << ext << '\n';
        }

        // GCGParser parser(WORDLIST_FILE, GCG_FILE_DIR);
        //
        // for (const auto &entry :
        //      std::filesystem::directory_iterator(GCG_FILE_DIR)) {
        //         parser.reset(std::string(GCG_FILE_DIR) + "/" +
        //                      entry.path().string());
        //         bool game_result = parser.validate_game(false);
        //         if (!game_result) {
        //                 std::cout << entry.path() << std::endl;
        //                 // parser.validate_game(true);
        //         }
        //         assert(game_result);
        // }

        // d.print();
        // setlocale(LC_ALL, "en_US.UTF-8");
        // for (const auto &entry :
        // std::filesystem::directory_iterator(games_dir)) {
        //         GCGParser parser(entry.path());
        //         bool game_result = parser.validate_game(false);
        //         if (!game_result) {
        //                 std::cout << entry.path() << std::endl;
        //                 // parser.validate_game(true);
        //         }
        //         assert(game_result);
        // }

        return 0;
}
