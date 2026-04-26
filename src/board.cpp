#include "../include/board.h"
#include "../include/helper.h"
#include "../include/print.h"
#include "../include/wordlist.h"
#include <cassert>
#include <codecvt>
#include <cstdio>
#include <ctime>
#include <deque>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#define min(x, y) ((x) < (y)) ? (x) : (y)
#define max(x, y) ((x) > (y)) ? (x) : (y)

Board::Board(std::string wordlist_file_path, std::string trie_file_path)
    : wordlist(wordlist_file_path, trie_file_path) {

        for (int i = 0; i < 28; i++) {
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
}

bool Board::contains(std::string word) const { return wordlist.contains(word); }

std::vector<struct Word *>
Board::get_formed_words(std::array<tile_place_t, 7> play) {

        // add horizontal word
        std::vector<struct Word *> formed_words = std::vector<struct Word *>();
        for (tile_place_t tile : play) {
                position_t p = tile.second;
                coords_t coords = get_xy(p);
                int horiz_len = 0;
                int x_coord = coords.first;
                int y_coord = coords.second;

                {
                        std::deque<char> horiz;

                        int x_word_start =
                            x_coord; // find first char of horizontal word
                        while (x_word_start >= 0 &&
                               board[get_pos(x_word_start, y_coord)] != NONE) {
                                char add_to_front =
                                    char(
                                        board[get_pos(x_word_start, y_coord)]) +
                                    '@';
                                horiz.push_front(add_to_front);
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
                                char add_to_back =
                                    char(board[get_pos(x_word_end, y_coord)]) +
                                    '@';
                                horiz.push_back(add_to_back);
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
                                for (char c : horiz) {
                                        horiz_str += c;
                                }

                                struct Word *new_word =
                                    new Word(horiz_str, x_word_start, false);

                                formed_words.push_back(new_word);
                        }
                }

                {
                        std::deque<char> vert;
                        int vert_len = 0;

                        int y_word_start =
                            y_coord; // find first char of vertical word
                        while (y_word_start >= 0 &&
                               board[get_pos(x_coord, y_word_start)] != NONE) {
                                char add_to_front =
                                    char(
                                        board[get_pos(x_coord, y_word_start)]) +
                                    '@';
                                vert.push_front(add_to_front);
                                y_word_start--;
                                vert_len++;
                        }

                        y_word_start++;

                        int y_word_end =
                            y_coord + 1; // find last char of vertical word
                        while (y_word_end < 15 &&
                               board[get_pos(x_coord, y_word_end)] != NONE) {
                                char add_to_back =
                                    char(board[get_pos(x_coord, y_word_end)]) +
                                    '@';
                                vert.push_back(add_to_back);
                                y_word_end++;
                                vert_len++;
                        }

                        y_word_end--;

                        if (vert_len >= 2) {
                                // single tiles don't count as words
                                std::string vert_str = "";
                                for (char c : vert) {
                                        vert_str += c;
                                }
                                struct Word *new_word =
                                    new Word(vert_str, y_word_start, true);

                                formed_words.push_back(new_word);
                        }
                }
        }
        return formed_words;
}

bool Board::make_play(std::array<tile_place_t, 7> play) {
        // to be a valid scrabble move all letters must be in either one row or
        // column, and all words formed by these new letters must be valid

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
                        std::cerr << "Error: cannot place tile, tile is "
                                     "already present."
                                  << '\n';
                        return false;
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
                                return false;
                        }
                }
        }

        bool vertical = min_x == max_x; // only takes up one x coord
        // we can have both min_x == max_x and min_y == max_y if the player
        // played one tile

        if (!vertical && (min_y != max_y)) {
                std::cerr << "Tiles not in one row or column" << '\n';
                return false;
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
                                return false;
                                // if gap in main word played
                        }
                }
        }

        else {
                for (int x = min_x; x <= max_x; x++) {
                        if (board[get_pos(x, min_y)] == NONE) {
                                std::cerr << "Gap in main horizontal word at "
                                          << x << " " << min_y << " " << '\n';
                                return false;
                                // if gap in main word played
                        }
                }
        }

        for (struct Word *new_word : get_formed_words(play)) {
                if (contains(new_word->word)) {
                        continue;
                }
                for (int j = 0; j < 7; j++) { // remove tiles if invalid word
                        if (play[j].first == NONE) {
                                continue;
                        }
                        position_t p = play[j].second;
                        board[p] = Tile::NONE;
                }
                return false;
        }

        return true;
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
        std::array<std::u32string, 31> board_string = board_template;
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

        // print rack for player A
        std::cout << "^[[2J"; // clears screen

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
                int str_y = 2 * coords.second + 1;
                // coordinates of position of tile in board_string
                int str_x = 4 * coords.first + 1;

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
