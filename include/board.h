#ifndef BOARD_H
#define BOARD_H
#include "helper.h"
#include <array>
#include <cstdint>
#include <vector>

class Board {
      public:
        Board();
        bool make_play(std::array<tile_place_t, 7>);
        void print() const;

      private:
        std::vector<Tile> bag;
        Tile board[225];
        std::array<Tile, 7> rack_a;
        std::array<Tile, 7> rack_b;
        std::uint16_t move_count;
        std::vector<Tile> draw_tiles(tilecount_t num_tiles);
        bool check_valid_words(position_t p); // checks if horizontal and vertical words at p are valid
        
        // a and b are labels we will use to refer to the 2 players
        //
};
#endif
