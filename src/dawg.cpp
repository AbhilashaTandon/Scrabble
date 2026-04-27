#include "../include/dawg.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>

DawgNode::DawgNode(Tile t) {
        parents = std::vector<DawgNode *>();
        children = std::vector<DawgNode *>();
        this->t = t;
}

bool DawgNode::equivalent(DawgNode *other) {
        if (children.size() != other->children.size()) {
                return false;
        }
        for (size_t i = 0; i < children.size(); i++) {
                if (&children[i] != &other->children[i]) {
                        return false;
                }
        }
        return true;
}

Dawg::Dawg(std::string file_path) : start(Tile::START), end(Tile::END) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string line;

        while (std::getline(file, line)) {
                std::string word = "";
                std::istringstream stream(line);
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }

                add_word(word);
                print(&end, "", false, false);
                print(&start, "", false, true);
                std::cout << "-------------------------------------------------"
                             "-----------------------------"
                          << "\n\n\n";
        }

        compress();
}

void Dawg::add_word(std::string word) {
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
                        // std::cout << "existing node found" << '\n';
                        current = next;
                        continue;
                }
                next = new DawgNode(Tile(c - 64));
                current->children.push_back(next);
                next->parents.push_back(current);
                current = next;
        }

        current->children.push_back(&end);
        end.parents.push_back(current);

        assert(this->start.children.size() != 0);
}

bool Dawg::contains(std::string word) {
        DawgNode *current = &this->start;
        for (char c : word) {
                // std::cout << c << ": ";
                assert(isupper(c));
                DawgNode *next = NULL;
                for (DawgNode *node : current->children) {
                        // std::cout << char(node->t + 64) << " ";
                        if (node->t != Tile(c - 64)) {
                                continue;
                        }
                        next = node;
                        break;
                }
                // std::cout << '\n';
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
                 bool forwards) {
        std::cout << indent;
        if (is_last) {
                std::cout << "└─";
                indent += "  ";
        } else {
                std::cout << "├─";
                indent += "| ";
        }
        std::cout << char(current->t + 64) << '\n';

        if (forwards) {
                for (size_t i = 0; i < current->children.size(); i++) {
                        print(current->children[i], indent,
                              i == current->children.size() - 1, forwards);
                }
        } else {
                for (size_t i = 0; i < current->parents.size(); i++) {
                        print(current->parents[i], indent,
                              i == current->parents.size() - 1, forwards);
                }
        }
}

void Dawg::compress() { compress_recurse(&this->end); }

void Dawg::compress_recurse(DawgNode *d) {
        if (d->parents.size() == 0) {
                return;
        }
        std::unordered_map<Tile, DawgNode *> preceding_tiles =
            std::unordered_map<Tile, DawgNode *>();

        for (DawgNode *parent : d->parents) {
                std::cout << char(parent->t + 64) << " ";
                if (parent->t == START) {
                        // there's only one start node so we don't need to merge
                        continue;
                }
                auto lookup = preceding_tiles.find(parent->t);

                if (lookup == preceding_tiles.end()) {
                        // add first node to map, and then replace later nodes
                        // with it
                        preceding_tiles.insert({parent->t, parent});
                        continue;
                }

                DawgNode *replacement = lookup->second;
                // assert(!replacement->equivalent(parent));
                for (DawgNode *parent_of_parent : parent->parents) {
                        replacement->parents.push_back(parent_of_parent);
                        // std::cout << parent_of_parent->t << " " << parent->t
                        // << '\n'; auto index =
                        // std::find(parent_of_parent->children.begin(),
                        // parent_of_parent->children.end(), parent);
                        // assert(index != parent_of_parent->children.end());
                        // parent_of_parent->children.erase(index);
                        // parent_of_parent->children.push_back(replacement);
                        // update parents of this node to point to the one we
                        // saved before
                }
                delete parent;
        }

        d->parents.clear();
        std::cout << " | ";

        for (auto node : preceding_tiles) {
                std::cout << char(node.first + 64) << " ";
                d->parents.push_back(node.second);
        }
        std::cout << '\n';

        for (auto node : preceding_tiles) {
                compress_recurse(node.second);
        }
}
