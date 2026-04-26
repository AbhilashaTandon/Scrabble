
#include "../include/board.h"
#include <gtest/gtest.h>
#include <utility>

TEST(BoardTests, HorizontalWord) {
        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::A, get_pos(3, 7));
        play[1] = std::make_pair(Tile::C, get_pos(4, 7));
        play[2] = std::make_pair(Tile::A, get_pos(5, 7));
        play[3] = std::make_pair(Tile::D, get_pos(6, 7));
        play[4] = std::make_pair(Tile::E, get_pos(7, 7));
        play[5] = std::make_pair(Tile::M, get_pos(8, 7));
        play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

        Board b = Board("../wordlists/NWL2023-modified.txt");
        EXPECT_TRUE(b.make_play(play));
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

        Board b = Board("../wordlists/NWL2023-modified.txt");
        EXPECT_FALSE(b.make_play(play));
}


TEST(BoardTests, Overlap){
        Board b = Board("../wordlists/NWL2023-modified.txt");
        std::array<tile_place_t, 7> play;

        play[0] = std::make_pair(Tile::A, get_pos(14, 4));
        play[1] = std::make_pair(Tile::C, get_pos(14, 4));
        play[2] = std::make_pair(Tile::A, get_pos(14, 4));
        play[3] = std::make_pair(Tile::D, get_pos(14, 4));
        play[4] = std::make_pair(Tile::E, get_pos(14, 4));
        play[5] = std::make_pair(Tile::M, get_pos(14, 4));
        play[6] = std::make_pair(Tile::Y, get_pos(14, 4));

        EXPECT_FALSE(b.make_play(play));
}

TEST(BoardTests, Vertical){
        Board b = Board("../wordlists/NWL2023-modified.txt");
        std::array<tile_place_t, 7> play;

        play[0] = std::make_pair(Tile::A, get_pos(14, 4));
        play[1] = std::make_pair(Tile::C, get_pos(14, 4));
        play[2] = std::make_pair(Tile::A, get_pos(14, 5));
        play[3] = std::make_pair(Tile::D, get_pos(14, 6));
        play[4] = std::make_pair(Tile::E, get_pos(14, 7));
        play[5] = std::make_pair(Tile::M, get_pos(14, 8));
        play[6] = std::make_pair(Tile::Y, get_pos(14, 9));

        EXPECT_FALSE(b.make_play(play));
}

TEST(BoardTests, Separated){
        Board b = Board("../wordlists/NWL2023-modified.txt");
        std::array<tile_place_t, 7> play;

        play[0] = std::make_pair(Tile::A, get_pos(0, 0));
        play[1] = std::make_pair(Tile::C, get_pos(2, 0));
        play[2] = std::make_pair(Tile::A, get_pos(4, 0));
        play[3] = std::make_pair(Tile::D, get_pos(6, 0));
        play[4] = std::make_pair(Tile::E, get_pos(8, 0));
        play[5] = std::make_pair(Tile::M, get_pos(10, 0));
        play[6] = std::make_pair(Tile::Y, get_pos(12, 0));

        EXPECT_FALSE(b.make_play(play));
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

        Board b = Board("../wordlists/NWL2023-modified.txt");
        EXPECT_TRUE(b.make_play(play));
        
        play[0] = std::make_pair(Tile::B, get_pos(3, 8));
        play[1] = std::make_pair(Tile::B, get_pos(3, 9));
        play[2] = std::make_pair(Tile::E, get_pos(3, 10));
        play[3] = std::make_pair(Tile::Y, get_pos(3, 11));
        play[4] = std::make_pair(NONE, get_pos(0, 0));
        play[5] = std::make_pair(NONE, get_pos(0, 0));
        play[6] = std::make_pair(NONE, get_pos(0, 0));

        EXPECT_TRUE(b.make_play(play));

}

TEST(BoardTests, AddOneTile){

        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::A, get_pos(3, 7));
        play[1] = std::make_pair(Tile::C, get_pos(4, 7));
        play[2] = std::make_pair(Tile::A, get_pos(5, 7));
        play[3] = std::make_pair(Tile::D, get_pos(6, 7));
        play[4] = std::make_pair(Tile::E, get_pos(7, 7));
        play[5] = std::make_pair(Tile::M, get_pos(8, 7));
        play[6] = std::make_pair(Tile::Y, get_pos(9, 7));

        Board b = Board("../wordlists/NWL2023-modified.txt");
        EXPECT_TRUE(b.make_play(play));

        play[0] = std::make_pair(Tile::T, get_pos(3, 8));
        play[1] = std::make_pair(Tile::NONE, get_pos(4, 7));
        play[2] = std::make_pair(Tile::NONE, get_pos(5, 7));
        play[3] = std::make_pair(Tile::NONE, get_pos(6, 7));
        play[4] = std::make_pair(Tile::NONE, get_pos(7, 7));
        play[5] = std::make_pair(Tile::NONE, get_pos(8, 7));
        play[6] = std::make_pair(Tile::NONE, get_pos(9, 7));

        EXPECT_TRUE(b.make_play(play));
}

