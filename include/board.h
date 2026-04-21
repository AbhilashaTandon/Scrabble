#ifndef BOARD_H
#define BOARD_H
#include "helper.h"
#include <set>
#include <array>

class Board {
public:
        bool make_play(std::array<tile_place_t, 7>, bool side);
private:
        std::set<Tile> bag;
        Square board[225];
        std::array<Tile, 7> rack_a;
        std::array<Tile, 7> rack_b;
        
};
#endif
