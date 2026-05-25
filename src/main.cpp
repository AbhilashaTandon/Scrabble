// #include "../include/board.h"
#include "../include/parse_cli_args.h"
#include "../include/parse_gcg.h"
#include <cassert>
// #include <filesystem>
// #include <iostream>

int main(int argc, char **argv) {


        if (argc == 5) {
                LookupFiles l =
                    LookupFiles(std::string(argv[1]), std::string(argv[2]),
                                std::string(argv[3]), std::string(argv[4]));
        }
        setlocale(LC_ALL, "en_US.UTF-8");
        // GCGParser parser("short_game_with_bad_moves.gcg");
        // parser.validate_game(true);

        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::A, get_pos(3, 7));
        play[1] = std::make_pair(Tile::C, get_pos(4, 7));
        play[2] = std::make_pair(Tile::A, get_pos(5, 7));
        play[3] = std::make_pair(Tile::D, get_pos(6, 7));
        play[4] = std::make_pair(Tile::E, get_pos(7, 7));
        play[5] = std::make_pair(Tile::M, get_pos(8, 7));
        play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

        Board b = Board(wordlist_file, trie_file, extensions_file);

        b.set_rack("ACADEMY", true);
        b.make_play(play).size();

        play[0] = std::make_pair(Tile::T, get_pos(5, 8));
        play[1] = std::make_pair(Tile::O, get_pos(6, 8));
        play[2] = std::make_pair(Tile::R, get_pos(7, 8));
        play[3] = std::make_pair(Tile::I, get_pos(8, 8));
        play[4] = std::make_pair(Tile::E, get_pos(9, 8));
        play[5] = std::make_pair(Tile::S, get_pos(10, 8));
        play[6] = std::make_pair(Tile::NONE, get_pos(11, 8));

        std::set<struct Word> new_words = {
            Word("TORIES", get_pos(5, 8), false),
            Word("AT", get_pos(5, 7), true),
            Word("DO", get_pos(6, 7), true),
            Word("ER", get_pos(7, 7), true),
            Word("MI", get_pos(8, 7), true),
            Word("YE", get_pos(9, 7), true),
        };

        b.set_rack("TORIES", false);
        std::set<struct Word> formed_words = b.make_play(play);

        std::cout << "\n";

        for(struct Word w : formed_words){
                coords_t coords = get_xy(w.start);
                std::cout << w.word << " " << int(coords.first) << " " << int(coords.second) << " " << int(w.is_vertical) << '\n';
        }

        // EXPECT_GT(formed_words.size(), 0);
        //
        // EXPECT_TRUE(formed_words == new_words);

        return 0;
}
