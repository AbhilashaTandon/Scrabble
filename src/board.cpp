#include "../include/board.h"
#include "../include/helper.h"
#include "../include/print.h"
#include "../include/wordlist.h"
#include <cassert>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

#define min(x, y) ((x) < (y)) ? (x) : (y)
#define max(x, y) ((x) > (y)) ? (x) : (y)

Board::Board(std::string wordlist_file_path) : wordlist(wordlist_file_path) {
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

bool Board::check_valid_words(position_t p) {
        // check horizontal word
        std::string horiz = "";
        coords_t coords = get_xy(p);

        int x_word_start = coords.first; // find first char of horizontal word
        while (x_word_start >= 0 && board[x_word_start] != NONE) {
                char add_to_front = board[x_word_start] + '@';
                horiz.insert(horiz.begin(), add_to_front);
                x_word_start--;
        };
        x_word_start++;

        int x_word_end = coords.first; // find last char of horizontal word
        while (x_word_end >= 0 && board[x_word_end] != NONE) {

                char add_to_back = board[x_word_start] + '@';
                horiz.insert(horiz.begin(), add_to_back);
                x_word_end++;
        };
        x_word_end--;

        std::cout << horiz;

        return true;
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
                coords_t coords = get_xy(p);
                min_x = min(min_x, coords.first);
                max_x = max(max_x, coords.first);
                min_y = min(min_y, coords.second);
                max_y = max(max_y, coords.second);
        }

        if ((min_x != max_x) && (min_y != max_y)) {
                return false;
                // all tiles must be in one row or column
        }

        for (int i = 0; i < 7; i++) {
                Tile t = play[i].first;
                position_t p = play[i].second;
                board[p] = t;
        }

        for (int i = 0; i < 7; i++) {
                if (!check_valid_words(play[i].second)) {
                        return false;
                }
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
