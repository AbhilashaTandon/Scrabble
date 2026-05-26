#include "../include/parse_gcg.h"
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

GCGParser::GCGParser(std::string file_path)
    : b(trie_file, extensions_file), file_path(file_path) {
        player1 = "player1";
        player2 = "player2";
}

void GCGParser::reset(std::string file_path) {
        b.reset();
        this->file_path = file_path;
        player1 = "player1";
        player2 = "player2";
}

bool GCGParser::validate_game(bool verbose) {

        std::fstream file = std::fstream((games_dir + "/" + file_path).c_str(),
                                         std::ios_base::in);
        // read in file

        std::string line;
        std::string first_word;

        while (std::getline(file, line)) {
                // parse line by line
                std::istringstream stream(line);
                // missing in words
                if (!(stream >> first_word)) {
                        std::cerr << line << '\n';
                        continue;
                }

                // add in players' names
                if (first_word == "#player1") {
                        if (!(stream >> this->player1)) {
                                std::cerr << line << '\n';
                                return false;
                        }
                        continue;
                }

                if (first_word == "#player2") {
                        if (!(stream >> this->player2)) {
                                std::cerr << line << '\n';
                                return false;
                        }
                        continue;
                }

                if (first_word[0] == '#') {
                        continue;
                        // ignore other comments
                }

                if (first_word[0] == '>') {
                        // parse actual moves now
                        if (!parse_move(line, verbose)) {
                                return false;
                        }
                        if (verbose) {
                                b.print();
                        }
                }
        }

        if (verbose) {
                b.print();
        }

        return true;
}

bool GCGParser::parse_move(std::string line, bool verbose) {
        std::istringstream stream(line);

        bool is_player_1 = false;

        std::string player_name;
        std::string rack;
        std::string position;
        std::string word_played;
        int point_difference;
        int updated_score;

        stream >> player_name;

        player_name = player_name.substr(1, player_name.size() - 2);
        if (player_name == player1) {
                is_player_1 = true;
        } else if (player_name == player2) {
                is_player_1 = false;
        } else {
                std::cerr << "Invalid event: no player named: " << player_name
                          << '\n';
                return false;
        }

        // deal with special cases

        stream >> rack;

        if (rack[0] == '(') {
                // giving points for opponent's remaining tiles at end of game
                stream >> point_difference;
                stream >> updated_score;

                // i will deal with this later
                return true;
        }

        b.set_rack(rack, is_player_1);

        stream >> position;

        if (position == "(challenge)") {
                std::cout << "Previous word challenged!\n";
                stream >> point_difference;
                stream >> updated_score;

                b.bonus_or_penalty(point_difference, is_player_1);

                return b.get_score(is_player_1) == updated_score;
        } else if (position == "(time)") {
                std::cout << "Time limit exceeded!\n";
                stream >> point_difference;
                stream >> updated_score;

                b.bonus_or_penalty(point_difference, is_player_1);

                return b.get_score(is_player_1) == updated_score;
        } else if (position[0] == '(') {
                // removing points for tiles left at end of game
                stream >> point_difference;
                stream >> updated_score;

                return true;
        } else if (position == "-") {
                // pass
                b.pass();
                return true;

        } else if (position == "--") {
                std::cout << "Withdrawal of challenged phoney!\n";
                // Withdrawal of challenged phoney
                stream >> point_difference;
                stream >> updated_score;

                b.bonus_or_penalty(point_difference, is_player_1);

                return b.get_score(is_player_1) == updated_score;
        } else if (position[0] == '-') {
                // tile exchange
                return b.exchange_letters(position.substr(1));
        }

        // parse position

        if (position.size() < 2 || position.size() > 3) {
                std::cerr << "Error: " << position
                          << " is not a valid position format\n";
                return false;
        }

        bool is_vertical = !isdigit(position[0]);
        // number is y, letter is x
        // if number first, horizontal move, else vertical move
        char x_coord_str = 0;
        std::string y_coord_str = "";
        if (is_vertical) {
                x_coord_str = position[0];
                y_coord_str = (position.substr(1));
        } else {
                if (position.size() == 2) {
                        x_coord_str = position[1];
                        y_coord_str = position.substr(0, 1);
                } else if (position.size() == 3) {
                        x_coord_str = position[2];
                        y_coord_str = position.substr(0, 2);
                } else {
                        std::cerr << "Error: " << position
                                  << " is not a valid position format\n";
                        return false;
                }
        }

        int x_start = 0;
        int y_start = 0;

        if (isupper(x_coord_str)) {
                x_start = x_coord_str - 'A';
        } else if (islower(x_coord_str)) {
                x_start = x_coord_str - 'a';
        } else {
                std::cerr << "Error: " << position
                          << " is not a valid position format\n";
                return false;
        }

        if (y_coord_str.size() < 1 || y_coord_str.size() > 2) {
                return false;
        }

        y_start = std::stoi(y_coord_str) - 1;
        // TODO:: check for error here because this will panic if y_coord_str is
        // not a number

        stream >> word_played;
        stream >> point_difference;
        stream >> updated_score;

        if (verbose) {
                std::cout << (is_player_1 ? player1 : player2) << "\t" << rack
                          << '\t' << x_start << "," << y_start << " "
                          << word_played << " " << point_difference << " "
                          << updated_score << '\n';
                std::cout << line << '\n';
        }

        std::array<tile_place_t, 7> play;
        int x_coord = x_start;
        int y_coord = y_start;
        int letter_idx = 0;
        for (char c : word_played) {
                char current = b.get_letter(x_coord, y_coord);
                if (current == c || c == '.' ||
                    (islower(c) && (current + 32 == c))) {
                        if (is_vertical) {
                                y_coord++;
                        } else {
                                x_coord++;
                        }
                        continue;
                } else if (current != '@') {
                        std::cerr << "Error: cannot place tile " << c
                                  << " at position(" << int(x_coord) << ","
                                  << int(y_coord) << "), tile " << current
                                  << " is already present\n";
                        return false;
                }
                if (isupper(c) || islower(c)) {
                        play[letter_idx] = std::make_pair(
                            make_tile(c), get_pos(x_coord, y_coord));
                        letter_idx++;
                } else if (c != '.') {
                        std::cerr << c << ": not a valid character\n";
                        assert(false);
                }

                if (is_vertical) {
                        y_coord++;
                } else {
                        x_coord++;
                }
        }

        bool result = b.make_play(play).size() > 0;

        bool correct_score = b.get_score(is_player_1) == updated_score;

        if (!correct_score) {
                std::cout << b.get_score(is_player_1) << " != " << updated_score
                          << '\n';
        }

        if (!(result && correct_score) && verbose) {
                b.print();
                std::cerr << "Error\n";
                std::cout << line << '\n';
        }

        return result && correct_score;
}
