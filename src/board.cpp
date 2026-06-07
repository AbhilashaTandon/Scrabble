#include "../include/board.h"
#include "../include/helper.h"
#include "../include/print.h"
#include "../include/wordlist.h"
#include "../include/board.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <codecvt>
#include <cstddef>
#include <cstdio>
#include <ctime>
#include <deque>
#include <iostream>
#include <locale>
#include <string>
#include <unordered_set>
#include <vector>

#define min(x, y) ((x) < (y)) ? (x) : (y)
#define max(x, y) ((x) > (y)) ? (x) : (y)

Board::Board() : wordlist(WORDLIST_FILE) {

        for (int i = 0; i < 30; i++) {
                tilecount_t count = tile_freq[i];
                for (tilecount_t j = 0; j < count; j++) {
                        bag.push_back((Tile)i);
                }
        }

        for (int i = 0; i < 225; i++) {
                board[i] = NONE;
                bonus_used[i] = false;
        }

        std::srand(std::time(0));

        rack_a = draw_tiles(7);
        rack_b = draw_tiles(7);

        score_a = 0;
        score_b = 0;
        move_count = 0;
}

Board::Board(const std::string &wordlist_file)
    : wordlist(wordlist_file), wordlist_file(wordlist_file) {

        for (int i = 0; i < 30; i++) {
                tilecount_t count = tile_freq[i];
                for (tilecount_t j = 0; j < count; j++) {
                        bag.push_back((Tile)i);
                }
        }

        for (int i = 0; i < 225; i++) {
                board[i] = NONE;
                bonus_used[i] = false;
        }

        std::srand(std::time(0));

        rack_a = draw_tiles(7);
        rack_b = draw_tiles(7);

        score_a = 0;
        score_b = 0;
        move_count = 0;
}

void Board::reset() {
        score_a = 0;
        score_b = 0;
        move_count = 0;

        bag.clear();
        rack_a.clear();
        rack_b.clear();
        std::fill(bonus_used.begin(), bonus_used.end(), 0);
        std::fill(board.begin(), board.end(), Tile::NONE);
}

bool Board::contains(const std::string &word) const {
        std::string upper = word;
        std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
        return wordlist.contains(upper);
}

void Board::end_game() {}

struct Word Board::get_new_word(const tile_place_t &tile,
                                bool is_vertical) const {
        position_t p = tile.second;
        coords_t coords = get_xy(p);
        int x_coord = coords.first;
        int y_coord = coords.second;

        std::deque<Tile> word;

        int word_start = is_vertical ? y_coord : x_coord;

        Tile t = tile.first;

        // find start of word

        while (word_start >= 0 && t != NONE) {
                word.push_front(t);
                word_start--;
                t = is_vertical ? board[get_pos(x_coord, word_start)]
                                : board[get_pos(word_start, y_coord)];
        }

        word_start++;

        // find end of word

        int word_end = (is_vertical ? y_coord : x_coord) + 1;

        t = is_vertical ? board[get_pos(x_coord, word_end)]
                        : board[get_pos(word_end, y_coord)];

        while (word_end < 15 && t != NONE) {
                word.push_back(t);
                word_end++;
                t = is_vertical ? board[get_pos(x_coord, word_end)]

                                : board[get_pos(word_end, y_coord)];
        }

        word_end--;

        if (word.size() >= 2) {
                // single tiles don't count as words
                std::string main_str = "";
                for (Tile t : word) {
                        char c = char(t + '@');
                        main_str += c;
                }

                struct Word new_word =
                    Word(main_str,
                         is_vertical ? get_pos(x_coord, word_start)
                                     : get_pos(word_start, y_coord),
                         is_vertical);

                return new_word;
        }

        return Word("", 0, 0);
}

std::vector<struct Word> Board::get_formed_words(const move_t &play,
                                                 bool is_vertical) const {

        std::vector<struct Word> formed_words = std::vector<struct Word>();

        int first_tile = 0;

        while (first_tile < 7 && play[first_tile].first == NONE) {
                first_tile++;
        }

        struct Word main_word = get_new_word(play[first_tile], is_vertical);

        if (main_word.word.size() >= 2) {
                formed_words.push_back(main_word);
        }

        struct Word a = Word("", 0, 0);
        struct Word b = Word("", 0, 1);
        // assert(a != b);

        // extra words

        for (tile_place_t tile : play) {
                if (tile.first == NONE) {
                        continue;
                }

                struct Word extra_word = get_new_word(tile, !is_vertical);

                if (extra_word.word.size() >= 2) {
                        formed_words.push_back(extra_word);
                }
        }

        return formed_words;
}

void Board::pass() { move_count++; }

void Board::bonus_or_penalty(int point_diff, bool is_player_a) {
        if (is_player_a) {
                score_a += point_diff;
        } else {
                score_b += point_diff;
        }
}

score_t Board::get_score(bool player_a) const {
        return player_a ? score_a : score_b;
}

std::vector<struct Word> Board::make_play(const move_t &play) {
        // to be a valid scrabble move all letters must be in either one row or
        // column, and all words formed by these new letters must be valid

        bool is_pass = true;
        for (auto tile : play) {
                if (tile.first != NONE) {
                        is_pass = false;
                }
        }

        int num_tiles_played = 0;

        if (is_pass && move_count == 0) {
                std::cerr << "Error: cannot pass on first move of game.\n";
                return std::vector<struct Word>();
        } else if (is_pass && move_count > 0) {
                pass();
                return {Word("", PASS, false)};
        }

        int min_x = 15;
        int max_x = -1;
        int min_y = 15;
        int max_y = -1;

        for (int i = 0; i < 7; i++) {
                position_t p = play[i].second;
                if (play[i].first == NONE) {
                        continue;
                }
                if (board[p] != NONE) {
                        coords_t coords = get_xy(p);
                        print();
                        std::cerr << "Error: cannot place tile "
                                  << char(play[i].first + '@')
                                  << " at position (" << int(coords.first)
                                  << "," << int(coords.second) << "), tile "
                                  << char(board[p] + '@')
                                  << " is already present.\n";
                        return std::vector<struct Word>();
                }
                coords_t coords = get_xy(p);
                min_x = min(min_x, coords.first);
                max_x = max(max_x, coords.first);
                min_y = min(min_y, coords.second);
                max_y = max(max_y, coords.second);
                for (int j = 0; j < i; j++) {
                        if (play[j].first == NONE) {
                                continue;
                        }
                        if (p == play[j].second) {
                                std::cerr << "Overlapping tiles" << '\n';
                                return std::vector<struct Word>();
                        }
                }
        }

        bool vertical = min_x == max_x; // only takes up one x coord
        // we can have both min_x == max_x and min_y == max_y if the player
        // played one tile

        if (!vertical && (min_y != max_y)) {
                std::cerr << "Tiles not in one row or column" << '\n';
                return std::vector<struct Word>();
        }

        for (int i = 0; i < 7; i++) { // add in tiles
                Tile t = play[i].first;
                if (t == NONE) {
                        continue;
                }
                position_t p = play[i].second;
                board[p] = t;
                num_tiles_played++;
        }

        // check that all tiles are part of one word

        if (vertical) {
                for (int y = min_y; y <= max_y; y++) {
                        if (board[get_pos(min_x, y)] != NONE) {
                                continue;
                        }

                        std::cerr << "Gap in main vertical word at " << min_x
                                  << " " << y << " " << '\n';
                        for (int j = 0; j < 7;
                             j++) { // remove tiles if invalid play
                                if (play[j].first == NONE) {
                                        continue;
                                }
                                position_t p = play[j].second;
                                board[p] = Tile::NONE;
                        }
                        return std::vector<struct Word>();
                        // if gap in main word played
                }
        }

        else {
                for (int x = min_x; x <= max_x; x++) {
                        if (board[get_pos(x, min_y)] != NONE) {
                                continue;
                        }

                        std::cerr << "Gap in main horizontal word at " << x
                                  << " " << min_y << " " << '\n';
                        for (int j = 0; j < 7;
                             j++) { // remove tiles if invalid play
                                if (play[j].first == NONE) {
                                        continue;
                                }
                                position_t p = play[j].second;
                                board[p] = Tile::NONE;
                        }
                        return std::vector<struct Word>();
                        // if gap in main word played
                }
        }

        std::vector<struct Word> new_words = get_formed_words(play, vertical);

        for (struct Word new_word : new_words) {
                if (contains(new_word.word)) {
                        continue;
                }

                std::cerr << int(new_word.word[0]) << '\n';
                std::cerr << "Invalid word " << new_word.word << '\n';
                // for (int j = 0; j < 7; j++) { // remove tiles if invalid word
                //         if (play[j].first == NONE) {
                //                 continue;
                //         }
                //         position_t p = play[j].second;
                //         board[p] = Tile::NONE;
                // }
                // temporarily disable invalid word detection for testing
                // return std::vector<struct Word>();
        }

        std::string letters_played = "";

        for (int i = 0; i < 7; i++) {
                if (play[i].first == Tile::NONE) {
                        continue;
                }
                letters_played += char(play[i].first + '@');
        }

        if (!remove_tiles_from_rack(letters_played)) {
                // player used tile not found in rack
                for (int j = 0; j < 7; j++) { // remove tiles if invalid play
                        if (play[j].first == NONE) {
                                continue;
                        }
                        position_t p = play[j].second;
                        board[p] = Tile::NONE;
                }
                return std::vector<struct Word>();
        }

        update_score(new_words, play, num_tiles_played);

        move_count++;
        return new_words;
}

void Board::update_score(std::vector<Word> &new_words, const move_t &play,
                         int num_tiles_played) {
        for (struct Word new_word : new_words) {
                score_t score = add_score(new_word);
                if (move_count % 2 == 0) {
                        score_a += score;
                } else {
                        score_b += score;
                }
        }

        if (new_words.size() == 0) {
                for (int j = 0; j < 7; j++) { // remove tiles if invalid play
                        if (play[j].first == NONE) {
                                continue;
                        }
                        position_t p = play[j].second;
                        board[p] = Tile::NONE;
                }
        }

        if (num_tiles_played == 7) {
                bonus_or_penalty(50, move_count % 2 == 0);
                // bingo
        }

        // unset bonuses

        for (int i = 0; i < 7; i++) {
                position_t pos = play[i].second;
                if (play[i].first == NONE) {
                        continue;
                }
                bonus_used[pos] = true;
        }
}
std::unordered_multiset<Tile> Board::draw_tiles(tilecount_t num_tiles) {
        std::unordered_multiset<Tile> selection =
            std::unordered_multiset<Tile>();
        for (tilecount_t i = 0; i < num_tiles; i++) {
                if (bag.size() == 0) {
                        return selection;
                }
                int index = std::rand() % bag.size();
                Tile t = bag[index];
                selection.insert(t);
                bag.erase(bag.begin() + index);
        }
        return selection;
}

void Board::print() const {
        std::array<std::u32string, 32> board_string = board_template;
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

        // print rack for player A
        std::cout << '\n';
        for (int i = 0; i < 23; i++) {
                std::cout << " ";
        }

        std::cout << score_a << '\n';

        for (int i = 0; i < 17; i++) {
                std::cout << " ";
        }
        for (Tile t : rack_a) {
                std::cout << converter.to_bytes(rack_tiles[t]);
                std::cout << " ";
        }

        std::cout << '\n';

        for (int i = 0; i < 17; i++) {
                std::cout << " ";
        }
        for (int i = 0; i < 28; i++) {
                std::cout << "─";
        }

        std::cout << "\n\n";

        // print board contents

        for (int i = 0; i < 225; i++) {
                if (board[i] == Tile::NONE) {
                        continue;
                }

                coords_t coords = get_xy(i);
                int str_y = 2 * coords.second + 2;
                // coordinates of position of tile in board_string
                int str_x = 4 * coords.first + 4;

                board_string[str_y].replace(str_x, 3, rack_tiles[board[i]]);
        }

        for (auto s : board_string) {
                std::cout << converter.to_bytes(s);
                std::cout << '\n';
        }

        std::cout << '\n';

        // print rack for player B

        for (int i = 0; i < 17; i++) {
                std::cout << " ";
        }
        for (Tile t : rack_b) {
                std::cout << converter.to_bytes(rack_tiles[t]);
                std::cout << " ";
        }

        std::cout << '\n';

        for (int i = 0; i < 17; i++) {
                std::cout << " ";
        }
        for (int i = 0; i < 28; i++) {
                std::cout << "─";
        }

        std::cout << '\n';
        for (int i = 0; i < 23; i++) {
                std::cout << " ";
        }

        std::cout << score_b << '\n';

        std::cout << "\n\n";
}

void Board::set_rack(const std::string &new_rack, bool is_player_a) {
        if (is_player_a) {
                rack_a = std::unordered_multiset<Tile>();
                size_t i = 0;
                for (; i < new_rack.size(); i++) {
                        if (new_rack[i] == '?') {
                                rack_a.insert(Tile::BLANK);
                                continue;
                        }
                        rack_a.insert(make_tile(new_rack[i]));
                }
        } else {
                rack_b = std::unordered_multiset<Tile>();
                size_t i = 0;
                for (; i < new_rack.size(); i++) {
                        if (new_rack[i] == '?') {
                                rack_b.insert(Tile::BLANK);
                                continue;
                        }
                        rack_b.insert(make_tile(new_rack[i]));
                }
        }
}

score_t Board::add_score(const struct Word &w) {
        score_t score = 0;
        score_t multiplier = 1;

        position_t pos = w.start;

        for (char c : w.word) {
                Square bonus = board_layout[pos];
                bool square_used = bonus_used[pos];

                score += tile_scores[make_tile(c)];
                // we always add score of letter

                if (!square_used) {
                        // if bonus is still fresh
                        switch (bonus) {
                        case DOUBLE_LETTER:
                                score += tile_scores[make_tile(c)];
                                // add score once more to double
                                break;

                        case TRIPLE_LETTER:
                                score += tile_scores[make_tile(c)] * 2;
                                // add twice more to triple
                                break;

                        // multipliers stack
                        case DOUBLE_WORD:
                                multiplier *= 2;
                                break;
                        case TRIPLE_WORD:
                                multiplier *= 3;
                                break;

                        default:
                                break;
                        }
                }
                pos += w.is_vertical ? 15 : 1;
        }

        return score * multiplier;
}

char Board::get_letter(uint8_t x, uint8_t y) const {
        Tile t = board[get_pos(x, y)];
        return char(t + 'A' - 1);
}

bool Board::remove_tiles_from_rack(const std::string &letters_to_remove) {
        std::unordered_multiset<Tile> rack_letters =
            std::unordered_multiset<Tile>();

        std::unordered_multiset<Tile> current_players_rack =
            move_count % 2 == 0 ? rack_a : rack_b;

        for (Tile t : current_players_rack) {
                rack_letters.insert(t);
        }

        assert(rack_letters.size() == current_players_rack.size());

        for (char c : letters_to_remove) {
                Tile t = make_tile(c);
                if (rack_letters.contains(t)) {
                        const auto it = rack_letters.find(t);
                        assert(it != rack_letters.end());
                        rack_letters.erase(it);
                } else {

                        const auto it = rack_letters.find(Tile::BLANK);
                        if (it != rack_letters.end()) {
                                rack_letters.erase(it);
                                continue;
                        }
                        std::cerr << "Play contains tiles (" << c
                                  << ") not found on "
                                     "player's rack: ";
                        for (Tile x : current_players_rack) {
                                std::cerr << char(x + '@');
                        }
                        std::cerr << ".\n";
                        return false;
                }
        }

        rack_letters.merge(draw_tiles(7 - rack_letters.size()));

        if (move_count % 2 == 0) {
                rack_a = rack_letters;
        } else {
                rack_b = rack_letters;
        }

        return true;
}

bool Board::exchange_letters(const std::string &letters_to_remove) {
        if (remove_tiles_from_rack(letters_to_remove)) {
                move_count++;
                return true;
        }
        return false;
}
