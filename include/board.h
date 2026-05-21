#ifndef BOARD_H
#define BOARD_H
#include "helper.h"
#include "wordlist.h"
#include <array>
#include <cstdint>
#include <vector>

struct Word{
        std::string word;
        position_t start;
        bool is_vertical;
};

class Board {
      public:
        Board(std::string wordlist_file_path, std::string trie_file_path);
        bool make_play(std::array<tile_place_t, 7>);
        void print() const;
        bool contains(std::string word) const;

      private:
        std::vector<Tile> bag;
        Tile board[225];
        std::array<Tile, 7> rack_a;
        std::array<Tile, 7> rack_b;
        std::uint16_t move_count;
        WordList wordlist;

        std::vector<Tile> draw_tiles(tilecount_t num_tiles);
        // bool check_valid_words(position_t p); // checks if horizontal and vertical words at p are valid
        std::vector<struct Word*> get_formed_words(std::array<tile_place_t, 7> play); //gets new words formed by move at p

        
        // a and b are labels we will use to refer to the 2 players
        //
};
#endif
