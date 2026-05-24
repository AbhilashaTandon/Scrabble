#ifndef BOARD_H
#define BOARD_H
#include "extensions.h"
#include "helper.h"
#include "wordlist.h"
#include <array>
#include <cstdint>
#include <unordered_set>
#include <vector>

struct Word {
        std::string word;
        position_t start;
        bool is_vertical;

        Word(std::string w, position_t s, bool v)
            : word(w), start(s), is_vertical(v) {}
        bool operator<(const Word &other_word) const {
                return (word < other_word.word);
        }
        bool operator==(const Word &other_word) const {
                return (word == other_word.word) &&
                       (start == other_word.start) &&
                       (is_vertical == other_word.is_vertical);
        }
};

class Board {
      public:
        Board(std::string wordlist_file_path, std::string trie_file_path,
              std::string ext_file_path);

        std::set<struct Word> make_play(std::array<tile_place_t, 7>);
        void pass();
        bool exchange_letters(std::string letters_to_remove);

        // these cant be struct Words because its legal to play non-adjacent
        // tiles if there are existing tiles between them that form a word
        void print() const;
        bool contains(std::string word) const;
        void end_game();

        void bonus_or_penalty(int point_diff, bool is_player_a);

        score_t get_score(bool player_a);

        void set_rack(std::string new_rack, bool is_player_a);

        char get_letter(uint8_t x, uint8_t y) const;

      private:
        score_t score_a;
        score_t score_b;
        std::vector<Tile> bag;
        Tile board[225];
        std::unordered_multiset<Tile> rack_a;
        std::unordered_multiset<Tile> rack_b;
        std::uint16_t move_count;
        WordList wordlist;
        std::set<struct Word> get_formed_words(
            std::array<tile_place_t, 7> play); // gets new words formed by move

        extension_map extensions;

        std::unordered_multiset<Tile> draw_tiles(tilecount_t num_tiles);

        std::vector<uint32_t> horiz_move_letter_opts;
        std::vector<uint32_t> vert_move_letter_opts;
        // we can use extensions of words to find the letters that can be played
        // in each square

        std::array<bool, 225> bonus_used;
        // we mark this as true whenever a move uses a bonus square

        score_t add_score(struct Word w);

        std::unordered_multiset<Tile>
        remove_tiles_from_rack(std::string letters_to_remove);
};
#endif
