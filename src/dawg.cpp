#include "../include/dawg.h"
#include <cassert>
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

bool find_in_vector(std::vector<DawgNode *> &vec, DawgNode *item) {
        auto itr = std::find(vec.begin(), vec.end(), item);
        return itr != vec.end();
}

bool remove_from_vector(std::vector<DawgNode *> &vec, DawgNode *item) {
        auto itr = std::find(vec.begin(), vec.end(), item);
        bool found = itr != vec.end();
        vec.erase(itr);
        return found;
}

Dawg::Dawg(std::string wordlist_file) : wordlist_file(wordlist_file){
        assert(wordlist_file != "");
        start = new DawgNode('<');
        end = new DawgNode('>');
        num_nodes = 2;
        build_dawg();
}

bool Dawg::has_children(DawgNode *d) const {
        if (d->children.size() == 0) {
                return false;
        }
        if (d->children.size() > 1) {
                return true;
        }
        return !d->children.contains(end->c);
}

void Dawg::build_dawg() {
        reg.clear();
        std::fstream file =
            std::fstream(wordlist_file.c_str(), std::ios_base::in);
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream stream(line);
                std::string word;
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }
                insert_word(word);
                assert(start->parents.size() == 0);
                assert(end->children.size() == 0);
        }
        assert(has_children(start));
        replace_or_register(start);
}

std::pair<DawgNode *, size_t> Dawg::find_common_prefix(std::string word) const {
        DawgNode *current = start;
        for (size_t i = 0; i < word.size(); i++) {
                // std::cout << "\t" << word[i] << " " << i << "\n";
                auto itr = current->children.find(word[i]);
                if (itr == current->children.end()) {
                        return std::make_pair(current, i);
                }
                current = itr->second;
        }

        if (!current->children.contains(end->c)) {
                return std::make_pair(current, word.size());
        }

        return std::make_pair(end, word.size() + 1);
}

bool Dawg::contains(std::string word) const {
        auto [last_state, idx] = find_common_prefix(word);
        return last_state == end;
}

void Dawg::add_suffix(DawgNode *last_state, std::string word, size_t index) {
        if (last_state == end) {
                return;
        }
        assert(last_state != nullptr);
        DawgNode *current = last_state;

        for (size_t i = index; i < word.size(); i++) {
                assert(current != end);
                assert(end->c == '>');
                DawgNode *new_node = new DawgNode(word[i]);
                num_nodes++;
                assert(end->c == '>');
                assert(new_node != end);
                assert(!current->children.contains(word[i]));
                current->children[word[i]] = new_node;
                new_node->parents.push_back(current);
                // std::cout << "\tJust added: " << current-> c << " " <<
                // new_node->c << " " << i << '\n';
                current = new_node;
                assert(!current->children.contains(end->c));
        }

        assert(current->c == word[word.size() - 1]);

        assert(!current->children.contains(end->c));
        current->children[end->c] = end;

        // std::cout << current->c << '\n';
        end->parents.push_back(current);
}

void Dawg::insert_word(std::string word) {
        auto [last_state, idx] = find_common_prefix(word);
        if (last_state == end) {
                return;
        }
        if (has_children(last_state)) {
                replace_or_register(last_state);
        }
        add_suffix(last_state, word, idx);
}

void Dawg::replace_or_register(DawgNode *d) {
        assert(d != nullptr);
        assert(d != end);
        assert(has_children(d));
        DawgNode *last_child = nullptr;
        char last_letter = 0;
        for (char letter = 'Z'; letter >= 'A'; letter--) {
                if (d->children.contains(letter)) {
                        last_child = d->children.at(letter);
                        last_letter = letter;
                        break;
                }
        }

        assert(last_child != nullptr);
        assert(last_letter == last_child->c);

        if (has_children(last_child)) {
                replace_or_register(last_child);
        }

        auto itr = reg.find(last_child);

        if (itr != reg.end()) {
                DawgNode *saved = *itr;
                assert(saved != nullptr);
                assert(*saved == *last_child);

                d->children[last_letter] = saved;

                assert(saved != end);

                saved->parents.push_back(d);
                // replace last child with saved

                for (char letter = 'A'; letter <= 'Z'; letter++) {
                        if (!last_child->children.contains(letter)) {
                                continue;
                        }

                        DawgNode *child = last_child->children.at(letter);

                        assert(find_in_vector(child->parents, saved));
                        assert(find_in_vector(child->parents, last_child));
                        remove_from_vector(child->parents, last_child);
                }

                for (DawgNode *parent : last_child->parents) {
                        assert(parent->children.contains(last_child->c));
                        assert(parent->children[last_child->c] = last_child);
                        parent->children[last_child->c] = saved;
                }

                assert(last_child != end);
                num_nodes--;
                delete last_child;
                return;
        }

        reg.insert(last_child);
}

void Dawg::print(DawgNode *current, std::string indent, bool is_last,
                 bool backwards) const {
        assert(current != nullptr);
        std::cout << indent;
        if (is_last) {
                std::cout << "└─";
                indent += "  ";
        } else {
                std::cout << "├─";
                indent += "| ";
        }
        if (current == start && backwards) {
                std::cout << "<\n";
                return;
        } else if (current == end && !backwards) {
                std::cout << ">\n";
                return;
        }

        std::cout << current->c << '\n';

        if (backwards) {

                size_t num_parents = current->parents.size();
                size_t i = 0;

                for (DawgNode *d : current->parents) {
                        print(d, indent, i == num_parents - 1, backwards);
                        i++;
                }
        } else {
                size_t num_children = current->children.size();
                size_t i = 0;

                for (char letter = 'A'; letter <= 'Z'; letter++) {
                        if (!current->children.contains(letter)) {
                                continue;
                        }

                        print(current->children.at(letter), indent,
                              i == num_children - 1, backwards);
                        i++;
                }
        }
}

void Dawg::print() const {
        print(start, "", false, false);
        print(end, "", false, true);
}

std::vector<std::string>
Dawg::get_words_from_tiles(std::unordered_multimap<Tile, bool> &rack,
                           DawgNode *node, std::string word_path,
                           std::vector<std::string> &words,  int max_depth) const {

        if (node->children.contains(end->c)) {
                words.push_back(word_path);
        }


        if(word_path.size() == max_depth){
                return words;
        }

        if (rack.empty()) {
                return words;
        }

        for (auto rack_itr = rack.begin(); rack_itr != rack.end(); rack_itr++) {

                if (rack_itr->second) {
                        // if we've used it already
                        continue;
                }

                if (rack_itr->first == Tile::BLANK) {
                        // blank can be any letter

                        for (auto itr = node->children.begin();
                             itr != node->children.end(); itr++) {
                                (*rack_itr).second = true;
                                // mark tile as used
                                std::vector<std::string> new_words =
                                    get_words_from_tiles(
                                        rack, itr->second,
                                        word_path +
                                            char(itr->first +
                                                 32), // make it lowercase to
                                                      // distinguish blanks
                                        words,  max_depth);
                                (*rack_itr).second = false;
                        }


                }

                char c = char(rack_itr->first + 64);
                if (!node->children.contains(c)) {
                        // if no words exist with word path prefix and the given
                        // tile
                        continue;
                }

                (*rack_itr).second = true;
                // mark tile as used
                std::vector<std::string> new_words = get_words_from_tiles(
                    rack, node->children.at(c), word_path + c, words,  max_depth);
                (*rack_itr).second = false;
        }

        return words;
}

std::vector<std::string>
Dawg::get_words_from_tiles(std::unordered_multiset<Tile> &rack, int max_depth) const {
        std::vector<std::string> words{};
        std::unordered_multimap<Tile, bool> used_tiles{};
        // we use a map here to keep track of what tiles we've used so we don't
        // have to modify the rack parameter
        for (Tile t : rack) {
                used_tiles.insert(std::pair(t, false));
        }
        return get_words_from_tiles(used_tiles, start, "", words, max_depth);
}
