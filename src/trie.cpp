#include "../include/trie.h"
#include <benchmark/benchmark.h>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <queue>
#include <span>
#include <sstream>
#include <string>

void print(struct Node *node) {
        if (node->letter != NONE) {
                std::cout << char(node->letter + 64) << " ";
        }
        if (node->left != NULL) {
                print(node->left);
        }
        if (node->right != NULL) {
                print(node->right);
        }
}

Trie::Trie(std::string file_path) {
        this->root = {0, 0, 0, 0, NONE};
        wordlist = parse_trie_file(file_path);

        std::cout << "All words loaded" << "\n";
        std::queue<struct Node *> ancestors = std::queue<struct Node *>();
        ancestors.push(&this->root);

        while (!ancestors.empty()) {
                struct Node *current = ancestors.front();
                ancestors.pop();
                if (current->letter == NONE) {
                        assert(current->left == NULL);
                        assert(current->right == NULL);
                        continue;
                }
                // std::cout << ancestors.size() << " ";
                // std::cout << char(current->letter + 64) << '\n';
                if (current->left != NULL && current->left->letter != NONE)
                        ancestors.push(current->left);
                if (current->right != NULL && current->right->letter != NONE)
                        ancestors.push(current->right);
        }
}

std::span<std::string> Trie::get_words(std::vector<Tile> available) {
        struct Node *current = &this->root;
        while (true) {
                if (current->letter == NONE) {
                        return std::span(wordlist.data() +
                                             current->wordlist_idx + 1,
                                         current->num_words);
                }
                bool present = false;
                for (std::vector<Tile>::iterator i = available.begin();
                     i < available.end(); i++) {
                        if (*i == current->letter) {
                                present = true;
                                available.erase(i);
                                break;
                        }
                }
                std::cout << (present ? char(current->letter + 64)
                                      : char(current->letter + 96));
                if (present) {
                        if (current->left == NULL) {
                                return std::span(wordlist.data() +
                                                     current->wordlist_idx + 1,
                                                 current->num_words);
                        }
                        // std::cout << char(current->letter + 64);
                        current = current->left;
                        continue;
                }

                else {
                        if (current->right == NULL) {
                                return std::span(wordlist.data() +
                                                     current->wordlist_idx + 1,
                                                 current->num_words);
                        }
                        // std::cout << char(current->letter + 96);
                        current = current->right;
                        continue;
                }
        }
}

std::vector<std::string> Trie::parse_trie_file(std::string file_path) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string line;
        std::vector<std::string> wordlist = std::vector<std::string>();
        int num_nodes = 0;

        while (std::getline(file, line)) {
                // parse line by line
                std::vector<std::string> words = std::vector<std::string>();
                std::istringstream stream(line);
                std::string tree_path; // tells us what letters are present and
                                       // missing in words
                if (!(stream >> tree_path)) {
                        std::cerr << line << '\n';
                        continue;
                }

                std::string next_word;
                while ((stream >> next_word)) {
                        words.push_back(next_word);
                }

                struct Node *current = &this->root;
                for (char c : tree_path) {
                        // build tree
                        Tile t = isupper(c) ? Tile(c - 64) : Tile(c - 96);
                        if (current->letter == NONE) {
                                current->letter = t;
                        } else {
                                assert(t == current->letter);
                        }

                        if (isupper(c)) {
                                if (current->left == NULL) {
                                        struct Node *child = new struct Node(
                                            0, 0, NULL, NULL, NONE);
                                        current->left = child;
                                        num_nodes++;
                                }
                                current = current->left;
                        } else {
                                if (current->right == NULL) {
                                        struct Node *child = new struct Node(
                                            0, 0, NULL, NULL, NONE);
                                        current->right = child;
                                        num_nodes++;
                                }
                                current = current->right;
                        }
                }

                // std::cout << num_nodes << '\n';
                // print(&this->root);
                // std::cout << '\n';

                current->wordlist_idx = wordlist.size() - 1;
                current->num_words = words.size();
                wordlist.insert(wordlist.end(), words.begin(), words.end());
        }

        return wordlist;
}
