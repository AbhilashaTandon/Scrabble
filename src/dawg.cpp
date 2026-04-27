#include "../include/dawg.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

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

                std::set<DawgNode *> *reg = new std::set<DawgNode *>();
                add_word(word, reg);
                // print(&start, "", false);
        }
        print(&end, "", false);

        // for (DawgNode *d : this->end.parents) {
        //         std::cout << char(d->t + 64);
        // }
}

// algorithm based on this paper
// https://aclanthology.org/J00-1002.pdf
// Incremental Construction of Minimal Acyclic Finite-State Automata

void Dawg::add_word(std::string word, std::set<DawgNode *> *reg) {
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
                if (current->children.size() > 1) {
                        // std::cout << "replace or register" << '\n';
                        replace_or_register(current, reg);
                }
                if (current->children.size() == 1 &&
                    current->children[0]->t != END) {
                        replace_or_register(current, reg);
                }
                // std::cout << "make new node" << '\n';
                next = new DawgNode(Tile(c - 64));
                current->children.push_back(next);
                next->parents.push_back(current);
                current = next;
        }

        current->children.push_back(&end);
        end.parents.push_back(current);

        assert(this->start.children.size() != 0);
        replace_or_register(&this->start, reg);

        // current->children.push_back(&this->end);
        // end.parents.push_back(current);
}

void Dawg::replace_or_register(DawgNode *state, std::set<DawgNode *> *reg) {
        assert(state != NULL);
        assert(state->children.size() != 0);
        DawgNode *last_child = state->children.back();
        if (last_child->children.size() > 1) {
                replace_or_register(last_child, reg);
        }
        if (last_child->children.size() == 1 &&
            last_child->children[0]->t != END) {
                replace_or_register(last_child, reg);
        }
        for (DawgNode *q : *reg) {
                if (q->equivalent(last_child)) {
                        for (DawgNode *child : last_child->children) {
                                std::vector<DawgNode *> parents =
                                    child->parents;
                                parents.erase(std::remove(parents.begin(),
                                                          parents.end(),
                                                          last_child),
                                              parents.end());
                                parents.push_back(q);
                        }
                        for (DawgNode *parent : last_child->parents) {
                                std::vector<DawgNode *> children =
                                    parent->children;
                                children.erase(std::remove(children.begin(),
                                                           children.end(),
                                                           last_child),
                                               children.end());
                                children.push_back(q);
                                q->parents.push_back(parent);
                        }
                        return;
                }
        }
        reg->insert(last_child);
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

void Dawg::print(DawgNode *current, std::string indent, bool is_last) {
        std::cout << indent;
        if (is_last) {
                std::cout << "└─";
                indent += "  ";
        } else {
                std::cout << "├─";
                indent += "| ";
        }
        std::cout << char(current->t + 64) << '\n';

        for (size_t i = 0; i < current->parents.size(); i++) {
                print(current->parents[i], indent,
                      i == current->parents.size() - 1);
        }
}
