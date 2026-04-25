
#include "../include/board.h"
#include <gtest/gtest.h>

TEST(BoardTests, BasicMoves) {
        std::array<tile_place_t, 7> play;
        play[0] = std::make_pair(Tile::A, get_pos(0, 4));
        play[1] = std::make_pair(Tile::C, get_pos(1, 4));
        play[2] = std::make_pair(Tile::A, get_pos(2, 4));
        play[3] = std::make_pair(Tile::D, get_pos(3, 4));
        play[4] = std::make_pair(Tile::E, get_pos(4, 4));
        play[5] = std::make_pair(Tile::M, get_pos(5, 4));
        play[6] = std::make_pair(Tile::Y, get_pos(6, 4));

        Board b = Board("wordlists/NWL2023-modified.txt");
        EXPECT_TRUE(b.make_play(play));
}
