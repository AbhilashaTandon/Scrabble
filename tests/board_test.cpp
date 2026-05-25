
#include "../include/board.h"
#include "../include/parse_cli_args.h"
#include "../include/parse_gcg.h"
#include <cassert>
#include <filesystem>
#include <gtest/gtest.h>
#include <utility>

TEST(BoardTests, CLI_args){
        ASSERT_TRUE(wordlist_file != "");
        ASSERT_TRUE(trie_file != "");
        ASSERT_TRUE(extensions_file != "");
}

TEST(BoardTests, HorizontalWord) {

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
        EXPECT_TRUE(b.make_play(play).size() > 0);

        play[0] = std::make_pair(Tile::A, get_pos(3, 7));
        play[1] = std::make_pair(Tile::C, get_pos(4, 7));
        play[2] = std::make_pair(Tile::A, get_pos(5, 7));
        play[3] = std::make_pair(Tile::D, get_pos(6, 7));
        play[4] = std::make_pair(Tile::E, get_pos(7, 7));
        play[5] = std::make_pair(Tile::M, get_pos(8, 7));
        play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

        b = Board(wordlist_file, trie_file, extensions_file);
        b.set_rack("KFJALSD", true);
        EXPECT_FALSE(b.make_play(play).size() > 0);
}

TEST(BoardTests, Gap) {
        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::E, get_pos(3, 7));
        play[1] = std::make_pair(Tile::B, get_pos(4, 7));
        play[2] = std::make_pair(Tile::B, get_pos(5, 7));
        play[3] = std::make_pair(NONE, get_pos(6, 7));
        play[4] = std::make_pair(Tile::M, get_pos(7, 7));
        play[5] = std::make_pair(Tile::A, get_pos(8, 7));
        play[6] = std::make_pair(Tile::N, get_pos(9, 7));

        Board b = Board(wordlist_file, trie_file, extensions_file);
        b.set_rack("EBBMAN", true);
        EXPECT_FALSE(b.make_play(play).size() > 0);
}

TEST(BoardTests, Overlap) {
        Board b = Board(wordlist_file, trie_file, extensions_file);
        std::array<tile_place_t, 7> play;

        play[0] = std::make_pair(Tile::A, get_pos(14, 4));
        play[1] = std::make_pair(Tile::C, get_pos(14, 4));
        play[2] = std::make_pair(Tile::A, get_pos(14, 4));
        play[3] = std::make_pair(Tile::D, get_pos(14, 4));
        play[4] = std::make_pair(Tile::E, get_pos(14, 4));
        play[5] = std::make_pair(Tile::M, get_pos(14, 4));
        play[6] = std::make_pair(Tile::Y, get_pos(14, 4));

        b.set_rack("ACADEMY", true);
        EXPECT_FALSE(b.make_play(play).size() > 0);
}

TEST(BoardTests, Vertical) {
        Board b = Board(wordlist_file, trie_file, extensions_file);
        std::array<tile_place_t, 7> play;

        play[0] = std::make_pair(Tile::A, get_pos(14, 4));
        play[1] = std::make_pair(Tile::C, get_pos(14, 4));
        play[2] = std::make_pair(Tile::A, get_pos(14, 5));
        play[3] = std::make_pair(Tile::D, get_pos(14, 6));
        play[4] = std::make_pair(Tile::E, get_pos(14, 7));
        play[5] = std::make_pair(Tile::M, get_pos(14, 8));
        play[6] = std::make_pair(Tile::Y, get_pos(14, 9));

        b.set_rack("ACADEMY", true);
        EXPECT_FALSE(b.make_play(play).size() > 0);
}

TEST(BoardTests, Separated) {
        Board b = Board(wordlist_file, trie_file, extensions_file);
        std::array<tile_place_t, 7> play;

        play[0] = std::make_pair(Tile::A, get_pos(0, 0));
        play[1] = std::make_pair(Tile::C, get_pos(2, 0));
        play[2] = std::make_pair(Tile::A, get_pos(4, 0));
        play[3] = std::make_pair(Tile::D, get_pos(6, 0));
        play[4] = std::make_pair(Tile::E, get_pos(8, 0));
        play[5] = std::make_pair(Tile::M, get_pos(10, 0));
        play[6] = std::make_pair(Tile::Y, get_pos(12, 0));

        b.set_rack("ACADEMY", true);
        EXPECT_FALSE(b.make_play(play).size() > 0);
}

TEST(BoardTests, CrissCross) {
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
        EXPECT_TRUE(b.make_play(play).size() > 0);

        play[0] = std::make_pair(Tile::B, get_pos(3, 8));
        play[1] = std::make_pair(Tile::B, get_pos(3, 9));
        play[2] = std::make_pair(Tile::E, get_pos(3, 10));
        play[3] = std::make_pair(Tile::Y, get_pos(3, 11));
        play[4] = std::make_pair(NONE, get_pos(0, 0));
        play[5] = std::make_pair(NONE, get_pos(0, 0));
        play[6] = std::make_pair(NONE, get_pos(0, 0));

        b.set_rack("BBEY", false);
        EXPECT_TRUE(b.make_play(play).size() > 0);
}

TEST(BoardTests, AddOneTile) {

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
        EXPECT_TRUE(b.make_play(play).size() > 0);

        play[0] = std::make_pair(Tile::T, get_pos(3, 8));
        play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
        play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
        play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
        play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
        play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
        play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

        b.set_rack("T", false);
        EXPECT_TRUE(b.make_play(play).size() > 0);
}

TEST(BoardTests, FirstMovePass) {

        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::NONE, get_pos(3, 7));
        play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
        play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
        play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
        play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
        play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
        play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

        Board b = Board(wordlist_file, trie_file, extensions_file);
        EXPECT_FALSE(b.make_play(play).size() > 0);
}

TEST(BoardTests, SecondMovePass) {

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
        EXPECT_TRUE(b.make_play(play).size() > 0);

        play[0] = std::make_pair(Tile::NONE, get_pos(3, 7));
        play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
        play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
        play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
        play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
        play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
        play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

        EXPECT_TRUE(b.make_play(play).size() > 0);
}

TEST(BoardTests, NewWords) {

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
        EXPECT_TRUE(b.make_play(play).size() > 0);

        play[0] = std::make_pair(Tile::T, get_pos(5, 8));
        play[1] = std::make_pair(Tile::O, get_pos(6, 8));
        play[2] = std::make_pair(Tile::R, get_pos(7, 8));
        play[3] = std::make_pair(Tile::I, get_pos(8, 8));
        play[4] = std::make_pair(Tile::E, get_pos(9, 8));
        play[5] = std::make_pair(Tile::S, get_pos(10, 8));
        play[6] = std::make_pair(Tile::NONE, get_pos(11, 8));

        std::vector<struct Word> new_words = {
            Word("TORIES", get_pos(5, 8), false),
            Word("AT", get_pos(5, 7), true),
            Word("DO", get_pos(6, 7), true),
            Word("ER", get_pos(7, 7), true),
            Word("MI", get_pos(8, 7), true),
            Word("YE", get_pos(9, 7), true),
        };

        b.set_rack("TORIES", false);
        std::vector<struct Word> formed_words = b.make_play(play);

        EXPECT_GT(formed_words.size(), 0);

        EXPECT_TRUE(formed_words == new_words);
}

TEST(BoardTests, NewWords2) {

        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::A, get_pos(3, 7));
        play[1] = std::make_pair(Tile::C, get_pos(4, 7));
        play[2] = std::make_pair(Tile::T, get_pos(5, 7));
        play[3] = std::make_pair(Tile::O, get_pos(6, 7));
        play[4] = std::make_pair(Tile::R, get_pos(7, 7));
        play[5] = std::make_pair(Tile::S, get_pos(8, 7));
        play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

        Board b = Board(wordlist_file, trie_file, extensions_file);

        b.set_rack("ACTORS", true);
        EXPECT_TRUE(b.make_play(play).size() > 0);

        play[0] = std::make_pair(Tile::E, get_pos(5, 6));
        play[1] = std::make_pair(Tile::T, get_pos(6, 6));
        play[2] = std::make_pair(Tile::A, get_pos(7, 6));
        play[3] = std::make_pair(Tile::NONE, get_pos(8, 8));
        play[4] = std::make_pair(Tile::NONE, get_pos(9, 8));
        play[5] = std::make_pair(Tile::NONE, get_pos(10, 8));
        play[6] = std::make_pair(Tile::NONE, get_pos(11, 8));

        std::vector<struct Word> new_words = {
            Word("ETA", get_pos(5, 6), false),
            Word("ET", get_pos(5, 6), true),
            Word("TO", get_pos(6, 6), true),
            Word("AR", get_pos(7, 6), true),
        };

        b.set_rack("ETA", false);
        std::vector<struct Word> formed_words = b.make_play(play);

        EXPECT_GT(formed_words.size(), 0);

        EXPECT_TRUE(formed_words == new_words);
}

TEST(BoardTests, StressTest) {
        for (const auto &entry : std::filesystem::directory_iterator(games_dir)) {
                GCGParser parser(entry.path());
                bool game_result = parser.validate_game(false);
                if (!game_result) {
                        std::cout << entry.path() << std::endl;
                        // parser.validate_game(true);
                }
                EXPECT_TRUE(game_result);
        }
}
