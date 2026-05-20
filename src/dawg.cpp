
#include "../include/dawg.h"
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

Dawg::Dawg(std::string file_path) : start(Tile::START), end(Tile::END) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string line;

        std::set<DawgNode *> *reg = new std::set<DawgNode *>();
        while (std::getline(file, line)) {
                std::cout << line << '\n';
                std::string word = "";
                std::istringstream stream(line);
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }

                add_word(word, reg);
                print(&start, "start", false, false);
                std::cout << '\n';
                print(&end, "end", false, true);
                std::cout << "--------------------------------" << '\n';
        }
        replace_or_register(&this->start, reg);
}
Dawg::Dawg(std::vector<std::string> wordlist)
    : start(Tile::START), end(Tile::END) {

        std::set<DawgNode *> *reg = new std::set<DawgNode *>();
        for (auto word : wordlist) {

                add_word(word, reg);
        }
        replace_or_register(&this->start, reg);
        print(&start, "start", false, false);
        print(&end, "end", false, true);
        assert(start.parents.size() == 0);
        assert(end.children.size() == 0);
}

std::pair<size_t, DawgNode *> Dawg::common_substring(std::string word) {
        DawgNode *current = &this->start;
        size_t idx = 0;

        for (; idx < word.size(); idx++) {
                assert(isupper(word[idx]));
                Tile t = Tile(word[idx] - 64);
                DawgNode *next = NULL;
                for (DawgNode *child : current->children) {
                        // find if node has a child with next letter
                        if (idx == word.size() - 1 && child->t == END) {
                                // reached end of word
                                return std::make_pair(idx, current);
                        }
                        if (child->t == t) {
                                // if next letter is a descendant, go to that
                                // node
                                next = child;
                                break;
                        }
                }
                if (next == NULL) {
                        // end of common substring
                        break;
                }
                current = next;
        }

        return std::make_pair(idx, current);
}

// algorithm based on this paper
// https://aclanthology.org/J00-1002.pdf
// Incremental Construction of Minimal Acyclic Finite-State Automata
// with help from this stack overflow post
// https://stackoverflow.com/a/38154096

void Dawg::add_word(std::string word, std::set<DawgNode *> *reg) {

        // find common substring prefix
        
        auto [idx, current] = common_substring(word);

        if (idx == word.size() - 1) {
                // this must be a case where the end state of the word doesn't
                // go to end, so we need to add it as a child
                current->add_child(&this->end);
                return;
        }

        DawgNode *longest_prefix_end_state = current;
        // variable rename for clarity
        if (!is_terminal(longest_prefix_end_state)) {
                replace_or_register(longest_prefix_end_state, reg);
        }

        // add in suffix
        for (; idx < word.size(); idx++) {
                DawgNode *new_node = new DawgNode(Tile(word[idx] - 64));
                current->add_child(new_node);
                new_node->add_parent(current);
                current = new_node;
                assert(current->t == Tile(word[idx] - 64));
        }
        assert(current->t == Tile(word[word.size() - 1] - 64));
        current->add_child(&this->end);
        this->end.add_parent(current);
}

void Dawg::replace_or_register(DawgNode *state, std::set<DawgNode *> *reg) {
        std::vector<DawgNode *> *children = &state->children;
        DawgNode *last_child = children->back();

        std::cout << last_child->t;
        assert(last_child != state);
        if (!is_terminal(last_child)) {
                replace_or_register(last_child, reg);
        }
        DawgNode *equivalent_node = NULL;
        for (auto node : *reg) {
                if (node->equivalent(last_child)) {
                        equivalent_node = node;
                        break;
                }
        }
        std::cout << '\n';
        if (equivalent_node != NULL) {
                for (auto parent : last_child->parents) {
                        parent->remove_child(last_child);
                        parent->add_child(equivalent_node);
                        equivalent_node->add_parent(parent);
                }
                for (auto child : last_child->children) {
                        child->remove_parent(last_child);
                        child->add_parent(equivalent_node);
                        assert(equivalent_node->has_child(child));
                }

                delete last_child;
        } else {
                reg->insert(last_child);
        }
}

bool Dawg::contains(std::string word) {
        DawgNode *current = &this->start;
        for (char c : word) {
                assert(isupper(c));
                DawgNode *next = NULL;
                for (DawgNode *node : current->children) {
                        if (node->t != Tile(c - 64)) {
                                continue;
                        }
                        next = node;
                        break;
                }
                if (next != NULL) {
                        // found node for next char

                        current = next;
                        continue;
                } else {
                        return false;
                }
        }

        for (DawgNode *node : current->children) {
                if (node->t == Tile::END) {
                        return true;
                }
        }
        return false;
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

bool Dawg::is_terminal(DawgNode *node) const {
        if (node->children.size() == 0) {
                return true;
        }
        if (node->children.size() > 1) {
                return false;
        }

        return node->children[0] == &this->end;
}
