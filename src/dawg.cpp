#include "../include/dawg.h"
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Dawg::Dawg(std::string file_path) : start(Tile::START), end(Tile::END) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string line;
        std::string word = "";

        std::set<DawgNode *> *reg = new std::set<DawgNode *>();
        while (std::getline(file, line)) {
                // std::cout << line << '\n';
                std::istringstream stream(line);
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }

                add_word(word, reg);
        }

        print(&this->start, "", false, false);
}

Dawg::Dawg(std::vector<std::string> wordlist)
    : start(Tile::START), end(Tile::END) {

        std::set<DawgNode *> *reg = new std::set<DawgNode *>();
        for (auto word : wordlist) {
                add_word(word, reg);
                print(&this->start, "", false, false);
        }
}

std::pair<size_t, DawgNode *> Dawg::common_prefix(std::string word) {
        size_t prefix_end = 0;
        DawgNode *current = &this->start;

        for (; prefix_end < word.size(); prefix_end++) {
                // find if next letter of word is in dawg

                bool next_letter_found = false;
                for (DawgNode *child : current->children) {
                        assert(isupper(word[prefix_end]));
                        if (child->t != Tile(word[prefix_end] - 64)) {
                                continue;
                        }

                        next_letter_found = true;
                        current = child;
                        // std::cout << word[prefix_end];

                        break;
                }

                if (!next_letter_found) {
                        return std::make_pair(prefix_end, current);
                }
        }

        // reached end of word, check if end token is in children
        for (DawgNode *child : current->children) {
                if (child->t == Tile::END) {
                        return std::make_pair(prefix_end, child);
                }
        }

        return std::make_pair(prefix_end, current);
}

// algorithm based on this paper
// https://aclanthology.org/J00-1002.pdf
// Incremental Construction of Minimal Acyclic Finite-State Automata
// with help from this stack overflow post
// https://stackoverflow.com/a/38154096

void Dawg::add_word(std::string word, std::set<DawgNode *> *reg) {

        auto [idx, node] = common_prefix(word);
        // std::cout << ":\t" << word << '\n';

        if (idx > word.size()) {
                return;
                // word already in dawg
        } else if (idx == word.size()) {
                this->end.add_parent(node);
                node->add_child(&this->end);
                return;
        }

        // idx++;
        for (; idx < word.size(); idx++) {
                DawgNode *d = new DawgNode(Tile(word[idx] - 64));
                d->add_parent(node);
                node->add_child(d);
                node = d;
        }

        node->add_child(&this->end);
        this->end.add_parent(node);
}

void Dawg::replace_or_register(DawgNode *state, std::set<DawgNode *> *reg) {}

bool Dawg::contains(std::string word) {

        auto [idx, node] = common_prefix(word);

        // std::cout << "\nfjdkfjkdjkd" << word << " " << word[idx] << " " << char(node->t + 64) << '\n';
        
        return (idx >= word.size() && node->t == Tile::END);
}

void Dawg::print(DawgNode *current, std::string indent, bool is_last,
                 bool backwards) {
        std::cout << indent;
        if (is_last) {
                std::cout << "└─";
                indent += "  ";
        } else {
                std::cout << "├─";
                indent += "| ";
        }

        std::cout << char(current->t + 64) << '\n';

        if (backwards) {
                for (size_t i = 0; i < current->parents.size(); i++) {
                        print(current->parents[i], indent,
                              i == current->parents.size() - 1, backwards);
                }
        } else {
                for (size_t i = 0; i < current->children.size(); i++) {
                        print(current->children[i], indent,
                              i == current->children.size() - 1, backwards);
                }
        }
}

bool Dawg::is_terminal(DawgNode *node) const {}
