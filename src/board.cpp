#include "../include/board.h"
#include "../include/helper.h"
#include "../include/print.h"
#include "../include/wordlist.h"
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
#include <vector>

#define min(x, y) ((x) < (y)) ? (x) : (y)
#define max(x, y) ((x) > (y)) ? (x) : (y)

Board::Board(std::string wordlist_file_path, std::string trie_file_path,
             std::string ext_file_path)
    : wordlist(wordlist_file_path, trie_file_path) {

        for (int i = 0; i < 30; i++) {
                tilecount_t count = tile_freq[i];
                for (tilecount_t j = 0; j < count; j++) {
                        bag.push_back((Tile)i);
                }
        }

        for (int i = 0; i < 225; i++) {
                board[i] = NONE;
        }

        std::srand(std::time(0));

        std::vector<Tile> draw_a = draw_tiles(7);
        std::vector<Tile> draw_b = draw_tiles(7);

        for (int i = 0; i < 7; i++) {
                rack_a[i] = draw_a[i];
                rack_b[i] = draw_b[i];
        }

        extensions = read_file(ext_file_path);

        score_a = 0;
        score_b = 0;
        bonus_used = std::array<bool, 225>();
        move_count = 0;
}

bool Board::contains(std::string word) const { return wordlist.contains(word); }

std::set<struct Word>
Board::get_formed_words(std::array<tile_place_t, 7> play) {

        // add horizontal word
        std::set<struct Word> formed_words = std::set<struct Word>();
        for (tile_place_t tile : play) {
                position_t p = tile.second;
                coords_t coords = get_xy(p);
                int horiz_len = 0;
                int x_coord = coords.first;
                int y_coord = coords.second;

                if (tile.first == Tile::NONE) {
                        continue;
                }
                {
                        std::deque<Tile> horiz;

                        int x_word_start =
                            x_coord; // find first char of horizontal word
                        assert(board[get_pos(x_word_start, y_coord)] !=
                               Tile::NONE);
                        while (x_word_start >= 0 &&
                               board[get_pos(x_word_start, y_coord)] != NONE) {
                                horiz.push_front(
                                    board[get_pos(x_word_start, y_coord)]);
                                x_word_start--;
                                horiz_len++;
                                // std::cout << add_to_front << " " <<
                                // x_word_start <<
                                // '\n';
                        }

                        x_word_start++;

                        int x_word_end =
                            x_coord + 1; // find last char of horizontal word
                        while (x_word_end < 15 &&
                               board[get_pos(x_word_end, y_coord)] != NONE) {
                                horiz.push_back(
                                    board[get_pos(x_word_end, y_coord)]);
                                x_word_end++;
                                horiz_len++;
                                // std::cout << add_to_back << " " << x_word_end
                                // <<
                                // '\n';
                        }

                        x_word_end--;

                        if (horiz_len >= 2) {
                                // single tiles don't count as words
                                std::string horiz_str = "";
                                for (Tile t : horiz) {
                                        char c = char(t + '@');
                                        // std::cout << horiz.size() << ' ';
                                        assert(isupper(c));
                                        horiz_str += c;
                                }

                                struct Word new_word =
                                    Word(horiz_str,
                                         get_pos(x_word_start, y_coord), false);

                                formed_words.insert(new_word);
                        }
                }

                {
                        std::deque<Tile> vert;
                        int vert_len = 0;

                        int y_word_start =
                            y_coord; // find first char of vertical word
                        assert(board[get_pos(x_coord, y_word_start)] !=
                               Tile::NONE);
                        while (y_word_start >= 0 &&
                               board[get_pos(x_coord, y_word_start)] != NONE) {
                                vert.push_front(
                                    board[get_pos(x_coord, y_word_start)]);
                                y_word_start--;
                                vert_len++;
                        }

                        y_word_start++;

                        int y_word_end =
                            y_coord + 1; // find last char of vertical word
                        while (y_word_end < 15 &&
                               board[get_pos(x_coord, y_word_end)] != NONE) {
                                vert.push_back(
                                    board[get_pos(x_coord, y_word_end)]);
                                y_word_end++;
                                vert_len++;
                        }

                        y_word_end--;

                        if (vert_len >= 2) {
                                // single tiles don't count as words
                                std::string vert_str = "";
                                for (Tile t : vert) {
                                        char c = char(t + '@');
                                        // std::cout << vert.size() << ' ';
                                        assert(isupper(c));
                                        vert_str += c;
                                }

                                struct Word new_word =
                                    Word(vert_str,
                                         get_pos(x_coord, y_word_start), true);

                                formed_words.insert(new_word);
                        }
                }
        }
        return formed_words;
}

void Board::pass() { move_count++; }

void Board::bonus_or_penalty(int point_diff) {
        if (move_count % 2 == 0) {
                score_a += point_diff;
        } else {
                score_b += point_diff;
        }
}

int Board::get_score(bool player_a) { return player_a ? score_a : score_b; }

std::set<struct Word> Board::make_play(std::array<tile_place_t, 7> play) {
        // to be a valid scrabble move all letters must be in either one row or
        // column, and all words formed by these new letters must be valid

        bool is_pass = true;
        for (auto tile : play) {
                if (tile.first != NONE) {
                        is_pass = false;
                }
        }

        if (is_pass && move_count == 0) {
                return std::set<struct Word>();
                // can't pass on first move of game
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
                                  << char(play[i].first + '@') << " at position ("
                                  << int(coords.first) << "," << int(coords.second)
                                  << "), tile " << char(board[p] + '@')
                                  << " is already present.\n";
                        return std::set<struct Word>();
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
                                return std::set<struct Word>();
                        }
                }
        }

        bool vertical = min_x == max_x; // only takes up one x coord
        // we can have both min_x == max_x and min_y == max_y if the player
        // played one tile

        if (!vertical && (min_y != max_y)) {
                std::cerr << "Tiles not in one row or column" << '\n';
                return std::set<struct Word>();
        }

        for (int i = 0; i < 7; i++) { // add in tiles
                Tile t = play[i].first;
                if (t == NONE) {
                        continue;
                }
                position_t p = play[i].second;
                board[p] = t;
        }

        // check that all tiles are part of one word

        if (vertical) {
                for (int y = min_y; y <= max_y; y++) {
                        if (board[get_pos(min_x, y)] == NONE) {
                                std::cerr << "Gap in main vertical word at "
                                          << min_x << " " << y << " " << '\n';
                                return std::set<struct Word>();
                                // if gap in main word played
                        }
                }
        }

        else {
                for (int x = min_x; x <= max_x; x++) {
                        if (board[get_pos(x, min_y)] == NONE) {
                                std::cerr << "Gap in main horizontal word at "
                                          << x << " " << min_y << " " << '\n';
                                return std::set<struct Word>();
                                // if gap in main word played
                        }
                }
        }

        std::set<struct Word> new_words = get_formed_words(play);

        for (struct Word new_word : new_words) {
                if (contains(new_word.word)) {
                        continue;
                }
                std::cerr << int(new_word.word[0]) << '\n';
                std::cerr << "Invalid word " << new_word.word << '\n';
                for (int j = 0; j < 7; j++) { // remove tiles if invalid word
                        if (play[j].first == NONE) {
                                continue;
                        }
                        position_t p = play[j].second;
                        board[p] = Tile::NONE;
                }
                return std::set<struct Word>();
        }

        // TODO: add check that tiles played are the same as on rack, and
        // replace tiles on rack with random ones from bag.

        move_count++;
        return new_words;
}

std::vector<Tile> Board::draw_tiles(tilecount_t num_tiles) {
        std::vector<Tile> selection = std::vector<Tile>();
        for (tilecount_t i = 0; i < num_tiles; i++) {
                int index = std::rand() % bag.size();
                Tile t = bag[index];
                selection.push_back(t);
                bag.erase(bag.begin() + index);
        }
        return selection;
}

void Board::print() const {
        std::array<std::u32string, 32> board_string = board_template;
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

        // print rack for player A
        // std::cout << "^[[2J"; // clears screen

        for (int i = 0; i < 17; i++) {
                std::cout << " ";
        }
        for (int i = 0; i < 7; i++) {
                std::cout << converter.to_bytes(rack_tiles[rack_a[i]]);
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
        for (int i = 0; i < 7; i++) {
                std::cout << converter.to_bytes(rack_tiles[rack_b[i]]);
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
}

void Board::set_rack(std::string new_rack) {
        if (move_count % 2 == 0) {
                size_t i = 0;
                for (; i < new_rack.size(); i++) {
                        if (new_rack[i] == '?') {
                                rack_a[i] = Tile::BLANK;
                                continue;
                        }
                        rack_a[i] = Tile(new_rack[i] - '@');
                }
                for (; i < 7; i++) {
                        rack_a[i] = Tile::NONE;
                }
        } else {
                size_t i = 0;
                for (; i < new_rack.size(); i++) {
                        if (new_rack[i] == '?') {
                                rack_b[i] = Tile::BLANK;
                                continue;
                        }
                        rack_b[i] = Tile(new_rack[i] - '@');
                }
                for (; i < 7; i++) {
                        rack_b[i] = Tile::NONE;
                }
        }
}

uint16_t Board::add_score(struct Word w) {
        uint16_t score = 0;
        uint16_t multiplier = 1;

        coords_t coords = get_xy(w.start);
        position_t pos = w.start;

        for (int i = 0; i < 7; i++) {

                Square bonus = board_layout[pos];
                bool square_used = bonus_used[pos];

                assert(!(square_used && bonus == EMPTY));

                score += tile_scores[Tile(w.word[i] - 64)];
                // we always add score of letter

                if (!square_used) {
                        // if bonus is still fresh
                        switch (bonus) {
                        case DOUBLE_LETTER:
                                score += tile_scores[Tile(w.word[i] - 64)];
                                // add score once more to double
                                break;

                        case TRIPLE_LETTER:
                                score += tile_scores[Tile(w.word[i] - 64)] * 2;
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

                        bonus_used[pos] = true;
                        // mark the bonus as used since we used it
                }

                position_t pos = get_pos(coords.first + int(!w.is_vertical),
                                         coords.second + int(w.is_vertical));
                // wow this line is a mess
        }

        return score;
}

char Board::get_letter(uint8_t x, uint8_t y) const {
        Tile t = board[get_pos(x, y)];
        return char(t + 'A' - 1);
}
