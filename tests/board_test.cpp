
#include "../deps/doctest.h"
#include "../include/board.h"
#include "../include/parse_gcg.h"
#include "../include/wordlist.h"
#include <cassert>
#include <filesystem>
#include <utility>

Board b = Board(WORDLIST_FILE);

TEST_CASE("BoardTests") {

        SUBCASE("Horizontal play") {
                b.reset();
                move_t play;
                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::A, get_pos(5, 7));
                play[3] = std::make_pair(Tile::D, get_pos(6, 7));
                play[4] = std::make_pair(Tile::E, get_pos(7, 7));
                play[5] = std::make_pair(Tile::M, get_pos(8, 7));
                play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

                b.reset();
                b.set_rack("ACADEMY", true);
                CHECK(b.make_play(play).size() > 0);

                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::A, get_pos(5, 7));
                play[3] = std::make_pair(Tile::D, get_pos(6, 7));
                play[4] = std::make_pair(Tile::E, get_pos(7, 7));
                play[5] = std::make_pair(Tile::M, get_pos(8, 7));
                play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

                b.reset();
                b.set_rack("KFJALSD", true);
                CHECK_FALSE(b.make_play(play).size() > 0);
        }

        SUBCASE("Gap") {
                b.reset();
                move_t play;
                play[0] = std::make_pair(Tile::E, get_pos(3, 7));
                play[1] = std::make_pair(Tile::B, get_pos(4, 7));
                play[2] = std::make_pair(Tile::B, get_pos(5, 7));
                play[3] = std::make_pair(NONE, get_pos(6, 7));
                play[4] = std::make_pair(Tile::M, get_pos(7, 7));
                play[5] = std::make_pair(Tile::A, get_pos(8, 7));
                play[6] = std::make_pair(Tile::N, get_pos(9, 7));

                b.reset();
                b.set_rack("EBBMAN", true);
                CHECK_FALSE(b.make_play(play).size() > 0);
        }

        SUBCASE("Overlap") {
                b.reset();
                move_t play;

                play[0] = std::make_pair(Tile::A, get_pos(14, 4));
                play[1] = std::make_pair(Tile::C, get_pos(14, 4));
                play[2] = std::make_pair(Tile::A, get_pos(14, 4));
                play[3] = std::make_pair(Tile::D, get_pos(14, 4));
                play[4] = std::make_pair(Tile::E, get_pos(14, 4));
                play[5] = std::make_pair(Tile::M, get_pos(14, 4));
                play[6] = std::make_pair(Tile::Y, get_pos(14, 4));

                b.set_rack("ACADEMY", true);
                CHECK_FALSE(b.make_play(play).size() > 0);
        }

        SUBCASE("Vertical") {
                b.reset();
                move_t play;

                play[0] = std::make_pair(Tile::A, get_pos(14, 4));
                play[1] = std::make_pair(Tile::C, get_pos(14, 4));
                play[2] = std::make_pair(Tile::A, get_pos(14, 5));
                play[3] = std::make_pair(Tile::D, get_pos(14, 6));
                play[4] = std::make_pair(Tile::E, get_pos(14, 7));
                play[5] = std::make_pair(Tile::M, get_pos(14, 8));
                play[6] = std::make_pair(Tile::Y, get_pos(14, 9));

                b.set_rack("ACADEMY", true);
                CHECK_FALSE(b.make_play(play).size() > 0);
        }

        SUBCASE("Separated") {
                b.reset();
                move_t play;

                play[0] = std::make_pair(Tile::A, get_pos(0, 0));
                play[1] = std::make_pair(Tile::C, get_pos(2, 0));
                play[2] = std::make_pair(Tile::A, get_pos(4, 0));
                play[3] = std::make_pair(Tile::D, get_pos(6, 0));
                play[4] = std::make_pair(Tile::E, get_pos(8, 0));
                play[5] = std::make_pair(Tile::M, get_pos(10, 0));
                play[6] = std::make_pair(Tile::Y, get_pos(12, 0));

                b.set_rack("ACADEMY", true);
                CHECK_FALSE(b.make_play(play).size() > 0);
        }

        SUBCASE("CrissCross") {
                b.reset();
                move_t play;
                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::A, get_pos(5, 7));
                play[3] = std::make_pair(Tile::D, get_pos(6, 7));
                play[4] = std::make_pair(Tile::E, get_pos(7, 7));
                play[5] = std::make_pair(Tile::M, get_pos(8, 7));
                play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

                b.reset();
                b.set_rack("ACADEMY", true);
                CHECK(b.make_play(play).size() > 0);

                play[0] = std::make_pair(Tile::B, get_pos(3, 8));
                play[1] = std::make_pair(Tile::B, get_pos(3, 9));
                play[2] = std::make_pair(Tile::E, get_pos(3, 10));
                play[3] = std::make_pair(Tile::Y, get_pos(3, 11));
                play[4] = std::make_pair(NONE, get_pos(0, 0));
                play[5] = std::make_pair(NONE, get_pos(0, 0));
                play[6] = std::make_pair(NONE, get_pos(0, 0));

                b.set_rack("BBEY", false);
                CHECK(b.make_play(play).size() > 0);
        }

        SUBCASE("AddOneTile") {
                b.reset();

                move_t play;
                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::A, get_pos(5, 7));
                play[3] = std::make_pair(Tile::D, get_pos(6, 7));
                play[4] = std::make_pair(Tile::E, get_pos(7, 7));
                play[5] = std::make_pair(Tile::M, get_pos(8, 7));
                play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

                b.reset();
                b.set_rack("ACADEMY", true);
                CHECK(b.make_play(play).size() > 0);

                play[0] = std::make_pair(Tile::T, get_pos(3, 8));
                play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
                play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
                play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
                play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
                play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
                play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

                b.set_rack("T", false);
                CHECK(b.make_play(play).size() > 0);
        }

        SUBCASE("FirstMovePass") {
                b.reset();

                move_t play;
                play[0] = std::make_pair(Tile::NONE, get_pos(3, 7));
                play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
                play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
                play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
                play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
                play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
                play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

                b.reset();
                CHECK_FALSE(b.make_play(play).size() > 0);
        }

        SUBCASE("SecondMovePass") {
                b.reset();

                move_t play;
                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::A, get_pos(5, 7));
                play[3] = std::make_pair(Tile::D, get_pos(6, 7));
                play[4] = std::make_pair(Tile::E, get_pos(7, 7));
                play[5] = std::make_pair(Tile::M, get_pos(8, 7));
                play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

                b.reset();
                b.set_rack("ACADEMY", true);
                CHECK(b.make_play(play).size() > 0);

                play[0] = std::make_pair(Tile::NONE, get_pos(3, 7));
                play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
                play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
                play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
                play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
                play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
                play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

                CHECK(b.make_play(play).size() > 0);
        }

        SUBCASE("NewWords") {
                b.reset();

                move_t play;
                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::A, get_pos(5, 7));
                play[3] = std::make_pair(Tile::D, get_pos(6, 7));
                play[4] = std::make_pair(Tile::E, get_pos(7, 7));
                play[5] = std::make_pair(Tile::M, get_pos(8, 7));
                play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

                b.reset();

                b.set_rack("ACADEMY", true);
                CHECK(b.make_play(play).size() > 0);

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

                CHECK_GT(formed_words.size(), 0);

                CHECK(formed_words == new_words);
        }

        SUBCASE("NewWords2") {
                b.reset();

                move_t play;
                play[0] = std::make_pair(Tile::A, get_pos(3, 7));
                play[1] = std::make_pair(Tile::C, get_pos(4, 7));
                play[2] = std::make_pair(Tile::T, get_pos(5, 7));
                play[3] = std::make_pair(Tile::O, get_pos(6, 7));
                play[4] = std::make_pair(Tile::R, get_pos(7, 7));
                play[5] = std::make_pair(Tile::S, get_pos(8, 7));
                play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

                b.reset();

                b.set_rack("ACTORS", true);
                CHECK(b.make_play(play).size() > 0);

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

                CHECK_GT(formed_words.size(), 0);

                CHECK(formed_words == new_words);
        }
}

TEST_CASE("StressTest") {
        GCGParser parser(WORDLIST_FILE, GCG_FILE_DIR);
        for (const auto &entry :
             std::filesystem::directory_iterator(GCG_FILE_DIR)) {
                parser.reset(std::string(GCG_FILE_DIR) + entry.path().string());
                bool game_result = parser.validate_game(false);
                if (!game_result) {
                        INFO((entry.path().string() + "\n"));
                        // parser.validate_game(true);
                }
                CHECK(game_result);
        }
}
