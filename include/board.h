#ifndef BOARD_H
#define BOARD_H
#include "dawg.h"
#include "helper.h"
#include "word.h"
#include <array>
#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>

class Board {
      public:
        Board();
        Board(const std::string &wordlist_file);

        std::vector<struct Word> make_play(const move_t &);
        void pass();
        bool exchange_letters(const std::string &letters_to_remove);

        // these cant be struct Words because its legal to play non-adjacent
        // tiles if there are existing tiles between them that form a word
        void print() const;
        bool contains(const std::string &word) const;
        void end_game();

        void bonus_or_penalty(int point_diff, bool is_player_a);

        score_t get_score(bool player_a) const;

        void set_rack(const std::string &new_rack, bool is_player_a);

        char get_letter(uint8_t x, uint8_t y) const;

        struct Word get_new_word(const tile_place_t &tile,
                                 bool is_vertical) const;

        void reset();

      private:
        score_t score_a;
        score_t score_b;
        std::vector<Tile> bag;
        std::array<Tile, 225> board;
        std::unordered_multiset<Tile> rack_a;
        std::unordered_multiset<Tile> rack_b;
        std::uint16_t move_count;
        Dawg wordlist;
        std::vector<struct Word> get_formed_words(
            const move_t &play,
            bool is_vertical) const; // gets new words formed by move
        std::string wordlist_file;

        std::unordered_multiset<Tile> draw_tiles(tilecount_t num_tiles);

        // std::vector<std::shared_ptr<struct Word>> words_on_board{};
        // std::array<std::shared_ptr<struct Word>, 225> pos_to_horiz_word_map;
        // std::array<std::shared_ptr<struct Word>, 225> pos_to_vert_word_map;

        std::vector<uint32_t> horiz_move_letter_opts;
        std::vector<uint32_t> vert_move_letter_opts;
        // we can use extensions of words to find the letters that can be played
        // in each square

        std::array<bool, 225> bonus_used;
        // we mark this as true whenever a move uses a bonus square

        score_t add_score(const struct Word &w);

        void update_score(std::vector<Word> &new_words, const move_t &play,
                          int num_tiles_played);

        bool remove_tiles_from_rack(const std::string &letters_to_remove);
};

#endif
